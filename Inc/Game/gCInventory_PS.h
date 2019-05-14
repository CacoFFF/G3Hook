#pragma once

#include "gCInventoryStack.h"

class G3GAMEAPI gCInventory_PS : public eCEntityPropertySet
{
public:
	bool UpdateVisibility();

	int GetStackCount() const;
	gEUseType GetStackUseType( int Slot) const;
	gCInventoryStack* GetStack( int Slot);
	const gCInventoryStack* GetStack( int Slot) const;

	static bool IsSkinnedSlot( gESlot);
};
