#pragma once

class eCEntity;

class G3GAMEAPI gCScriptProcessingUnit
{
public:
	eCEntity* GetSelfEntity();
	eCEntity* GetOtherEntity();
	eCEntity* GetTargetEntity();

	static bool sAIGotoInstr( void*, gCScriptProcessingUnit*, bool);
	static bool sAIPlayAniInstr( void*, gCScriptProcessingUnit*, bool);
};
