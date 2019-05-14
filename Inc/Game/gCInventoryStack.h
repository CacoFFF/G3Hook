#pragma once

//Superclass
#include "gCInventorySlot.h"

class G3GAMEAPI gCInventoryStack : public gCInventorySlot
{
public:
	PS_EPROPERTY(Amount,int);           // 0x3C
	PS_EPROPERTY(Quality,int);          // 0x40
	PS_EPROPERTY(QuickSlot,int);        // 0x44
	PS_EPROPERTY(SortIndex,int);        // 0x48
	PS_EPROPERTY(Type,bTPropertyContainer<gEStackType>);
	PS_EPROPERTY(Learned,bool);         // 0x54
	PS_EPROPERTY(ActivationCount,int);  // 0x58
	PS_EPROPERTY(TransactionCount,int); // 0x5C
};
