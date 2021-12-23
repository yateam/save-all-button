// Copyright Superyateam. All Rights Reserved.

#include "SaveAllButton.h"

#include "FileHelpers.h"
#include "SaveAllButtonStyle.h"
#include "SaveAllButtonCommands.h"
#include "ToolMenus.h"

static const FName SaveAllButtonTabName("SaveAllButton");

#define LOCTEXT_NAMESPACE "FSaveAllButtonModule"

void FSaveAllButtonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSaveAllButtonStyle::Initialize();
	FSaveAllButtonStyle::ReloadTextures();

	FSaveAllButtonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSaveAllButtonCommands::Get().SaveAllAction,
		FExecuteAction::CreateRaw(this, &FSaveAllButtonModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSaveAllButtonModule::RegisterMenus));
}

void FSaveAllButtonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSaveAllButtonStyle::Shutdown();

	FSaveAllButtonCommands::Unregister();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void FSaveAllButtonModule::PluginButtonClicked()
{
	constexpr bool bPromptUserToSave = true;
	constexpr bool bSaveMapPackages = true;
	constexpr bool bSaveContentPackages = true;
	constexpr bool bFastSave = false;
	constexpr bool bNotifyNoPackagesSaved = false;
	constexpr bool bCanBeDeclined = false;
	FEditorFileUtils::SaveDirtyPackages( bPromptUserToSave, bSaveMapPackages, bSaveContentPackages, bFastSave, bNotifyNoPackagesSaved, bCanBeDeclined );
}

void FSaveAllButtonModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.ModesToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("File");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSaveAllButtonCommands::Get().SaveAllAction));

				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSaveAllButtonModule, SaveAllButton)