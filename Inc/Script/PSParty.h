#pragma once

#include "Game/gCParty_PS.h"

class G3SCRIPTAPI PSParty
{
	PS_BASE(PSParty,gCParty_PS)
	
	Entity GetPartyLeader() const;
	bTValArray<eCEntity*> GetMembers(bool) const;

	bool Add( Entity);
	bool Remove( Entity);
};
