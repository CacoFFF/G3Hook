#pragma once

#include "Game/gCDamage_PS.h"

class G3SCRIPTAPI PSDamage
{
	PS_BASE(PSDamage,gCDamage_PS);

	PS_PROPERTY(DamageType,gEDamageType);
	PS_PROPERTY(DamageAmount,int32);
	PS_PROPERTY(DamageManaMultiplier,float);
	PS_PROPERTY(DamageHitMultiplier,float);
	PS_PROPERTY(ManaUsed,int);
};

