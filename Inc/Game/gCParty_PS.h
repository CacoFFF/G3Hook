#pragma once

class G3GAMEAPI gCParty_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(PartyLeaderEntity,eCEntityProxy);
	PS_EPROPERTY(PartyMemberType,bTPropertyContainer<gEPartyMemberType>);
	PS_EPROPERTY(Waiting,bool);
	bTObjArray<eCEntityProxy> Members; //3C
};
