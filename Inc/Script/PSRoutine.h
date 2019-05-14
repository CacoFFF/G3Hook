#pragma once

#include "Game/gCScriptRoutine_PS.h"

class G3API PSRoutine
{
	PS_BASE(PSRoutine,gCScriptRoutine_PS)

	void ContinueRoutine();
	void SetTask( bCString TaskName);
};
