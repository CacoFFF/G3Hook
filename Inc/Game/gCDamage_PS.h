#pragma once

class G3GAMEAPI gCDamage_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(DamageType,bTPropertyContainer<gEDamageType>);
	PS_EPROPERTY(DamageAmount,int32);
	PS_EPROPERTY(DamageManaMultiplier,float);
	PS_EPROPERTY(DamageHitMultiplier,float);
	PS_EPROPERTY(ManaUsed,int);
};
