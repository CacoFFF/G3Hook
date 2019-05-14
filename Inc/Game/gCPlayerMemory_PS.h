#pragma once

// Superclass
#include "Engine/eCEntityPropertySet.h"

class G3API gCPlayerMemory_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(HideTips,bool);
	PS_EPROPERTY(PlayerKnows,bTObjArray<bCString>);
	PS_EPROPERTY(PoliticalFame,bTValArray<int32>);
	PS_EPROPERTY(PoliticalSuspectComment,bTValArray<int32>);
	PS_EPROPERTY(PoliticalPlayerCount,bTValArray<int32>);
	PS_EPROPERTY(PoliticalPlayerCrime,bTValArray<bool>);
	PS_EPROPERTY(XP,int32);
	PS_EPROPERTY(LPAttribs,int32);
	PS_EPROPERTY(LPPerks,int32);
	PS_EPROPERTY(LastWeaponConfig,bTPropertyContainer<gEWeaponConfig>);
	PS_EPROPERTY(LastSpell,bCPropertyID);
	PS_EPROPERTY(SecondsTransformRemain,float);
	PS_EPROPERTY(SecondsMistRemain,float);
	PS_EPROPERTY(BookOfFlood,int32);
	PS_EPROPERTY(BookOfRhobar,int32);
	PS_EPROPERTY(BookOfZuben,int32);
	PS_EPROPERTY(DuskToDawnStartHour,int32);
	PS_EPROPERTY(Chapter,int32);
	PS_EPROPERTY(TutorialFlags,uint32);
	PS_EPROPERTY(TalkedToDiego,bool);
	PS_EPROPERTY(TalkedToGorn,bool);
	PS_EPROPERTY(TalkedToMilten,bool);
	PS_EPROPERTY(TalkedToLester,bool);
	PS_EPROPERTY(IsConsumingItem,bool);

	int GetValue( const bCString&) const;
	int GetMaximum( const bCString&) const;
//	const bTObjMap<bCString,gCAttribute*>& GetAttributes() const; // 0xA8
};


//static int TestPM = sizeof( gCPlayerMemory_PS);
