// Copyright Superyateam. All Rights Reserved.

#include "SaveAllButtonStyle.h"
#include "SaveAllButton.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FSaveAllButtonStyle::StyleInstance = nullptr;

void FSaveAllButtonStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FSaveAllButtonStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FSaveAllButtonStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SaveAllButtonStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FSaveAllButtonStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("SaveAllButtonStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("SaveAllButton")->GetBaseDir() / TEXT("Resources"));

	Style->Set("SaveAllButton.SaveAllAction", new IMAGE_BRUSH_SVG(TEXT("SaveAllIcon"), Icon20x20));
	return Style;
}

void FSaveAllButtonStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FSaveAllButtonStyle::Get()
{
	return *StyleInstance;
}
