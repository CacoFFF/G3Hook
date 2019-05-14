#pragma once

#include "gCScriptProcessingUnit.h"

class G3GAMEAPI gCScriptRoutine_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(Routine,bCString); //TODO: IT'S ACTUALLY bCScriptString
	PS_EPROPERTY(CurrentTask,bCString);
	PS_EPROPERTY(TaskTime,float);
	PS_EPROPERTY(TaskPosition,int32);
	PS_EPROPERTY(StateTime,float);
	PS_EPROPERTY(StatePosition,int32);
	PS_EPROPERTY(CommandTime,float);
	PS_EPROPERTY(LastTask,bCString);
	PS_EPROPERTY(CurrentState,bCString);
	PS_EPROPERTY(CurrentBreakBlock,int32);
	PS_EPROPERTY(AniState,bTPropertyContainer<gEAniState>);
	PS_EPROPERTY(Action,bTPropertyContainer<gEAction>);
	PS_EPROPERTY(AmbientAction,bTPropertyContainer<gEAmbientAction>);
	PS_EPROPERTY(AIMode,bTPropertyContainer<gEAIMode>);
	PS_EPROPERTY(HitDirection,bTPropertyContainer<gEHitDirection>);
	PS_EPROPERTY(SPU,gCScriptProcessingUnit); //THIS IS A LARGE CLASS!!
	//byte ptr [esi+1F0h], 0
};

//int TestSR = sizeof(gCScriptRoutine_PS);

