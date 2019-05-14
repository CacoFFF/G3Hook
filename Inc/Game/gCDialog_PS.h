#pragma once

class G3GAMEAPI gCDialog_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(TalkedToPlayer,bool);
	PS_EPROPERTY(EndDialogTimestamp,float);
	PS_EPROPERTY(TradeEnabled,bool);
	PS_EPROPERTY(TradeCategory,bTPropertyContainer<gETradeCategory>);
	PS_EPROPERTY(TeachEnabled,bool);
	PS_EPROPERTY(PartyEnabled,bool);
	PS_EPROPERTY(MobEnabled,bool);
	PS_EPROPERTY(SlaveryEnabled,bool);
	PS_EPROPERTY(PickedPocket,bool);
	eCEntityProxy TalkingTo;

	int AddTalkedToBy( eCEntity*);
	eCEntity* GetTalkingTo() const;
};


inline eCEntity* gCDialog_PS::GetTalkingTo() const
{
	return (eCEntity*)TalkingTo.GetEntity();
}
