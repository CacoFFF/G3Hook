#pragma once

#include "Game/gCItem_PS.h"

class G3SCRIPTAPI PSItem
{
	PS_BASE(PSItem,gCItem_PS);

	void ModifyQuality( uint32, uint32);
	void SetAmount( uint32);

	uint32 GetAmount() const;
	gEItemCategory GetCategory() const;
	int GetGoldValue() const;
	uint32 GetQuality() const;
	Entity GetSkill() const;
	Entity GetSpell() const;
	bool IsDropped() const;
	bool IsEquipped() const;
	bool IsFullBody() const;
	bool IsMissionItem() const;
	bool IsRobe() const;
};
