#pragma once

#include "Game/gCInteraction_PS.h"

class G3SCRIPTAPI PSInteraction
{
	PS_BASE(PSInteraction,gCInteraction_PS);

	PS_PROPERTY(FocusPriority,gEFocusPriority);
	PS_PROPERTY(Owner,eCEntityProxy);
	PS_PROPERTY(User,eCEntityProxy);
	PS_PROPERTY(UseType,gEUseType);
	PS_PROPERTY(UseFunc,bCString);
	PS_PROPERTY(AnchorPoint,eCEntityProxy);
	PS_PROPERTY(FocusNameType,gEFocusNameType);
	PS_PROPERTY(FocusNameBone,bCString);
	PS_PROPERTY(FocusViewOffset,bCVector);
	PS_PROPERTY(FocusWorldOffset,bCVector);
	PS_PROPERTY(UsedByPlayer,bool);
	PS_PROPERTY(EnterROIScript,bCString);
	PS_PROPERTY(ExitROIScript,bCString);
	PS_PROPERTY(Spell,eCTemplateEntityProxy);
};
