// Copyright Superyateam. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SaveAllButtonStyle.h"

class FSaveAllButtonCommands : public TCommands<FSaveAllButtonCommands>
{
public:

	FSaveAllButtonCommands()
		: TCommands<FSaveAllButtonCommands>(TEXT("SaveAllButton"), NSLOCTEXT("Contexts", "SaveAllButton", "SaveAllButton Plugin"), NAME_None, FSaveAllButtonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > SaveAllAction;
};
