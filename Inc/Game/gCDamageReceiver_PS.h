#pragma once

class G3GAMEAPI gCDamageReceiver_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(HitPoints,int32);
	PS_EPROPERTY(HitPointsMax,int32);
	PS_EPROPERTY(StaminaPoints,int32);
	PS_EPROPERTY(StaminaPointsMax,int32);
	PS_EPROPERTY(ManaPoints,int32);
	PS_EPROPERTY(ManaPointsMax,int32);
	PS_EPROPERTY(DamageType,bTPropertyContainer<gEDamageType>);
	PS_EPROPERTY(DamageAmount,int32);
	PS_EPROPERTY(LastInflictor,eCEntityProxy);
};

