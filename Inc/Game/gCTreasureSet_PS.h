#pragma once

class gCInventory_PS;

class G3GAMEAPI gCTreasureSet_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(TreasureDistribution,bTPropertyContainer<gETreasureDistribution>);
	PS_EPROPERTY(MinTransferStacks,uint32);
	PS_EPROPERTY(MaxTransferStacks,uint32);

	bool GeneratePlunderInventory( gCInventory_PS*);
	bool GenerateTradeInventory( gCInventory_PS*);
	bool RefreshTradeInventory( gCInventory_PS*);
};
