#pragma once

#include "Game/gCFocus_PS.h"

class G3SCRIPTAPI PSFocus
{
	PS_BASE(PSFocus,gCFocus_PS);

	Entity GetFocusEntity() const;
};