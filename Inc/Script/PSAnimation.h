#pragma once

#include "Engine/eCVisualAnimation_PS.h"

class G3SCRIPTAPI PSAnimation
{
	PS_BASE(PSAnimation,eCVisualAnimation_PS);

	bCString GetResourceName() const;
};
