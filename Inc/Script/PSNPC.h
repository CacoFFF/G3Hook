#pragma once

#include "Game/gCNPC_PS.h"

class G3API PSNpc
{
	PS_BASE(PSNpc,gCNPC_PS)

	void SetCurrentTarget( const Entity& NewTarget);

	void EnableStatusEffects( int StatusBits, bool); //TODO: Find out what parameter 2 does

	bool IsTransformed() const; //WARN: Use status effects in the future!
};

