// Copyright Superyateam. All Rights Reserved.

#include "SaveAllButtonCommands.h"

#define LOCTEXT_NAMESPACE "FSaveAllButtonModule"

void FSaveAllButtonCommands::RegisterCommands()
{
	UI_COMMAND(SaveAllAction, "Save All Modified Assets", "Save all modified assets", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
