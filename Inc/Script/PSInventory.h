#pragma once

#include "Engine/Template.h"

#include "Game/gCInventory_PS.h"

class G3API PSInventory
{
public:
	PS_BASE(PSInventory,gCInventory_PS)

	bool IsSkillActive( const Template&) const;
	int FindStackIndex( gESlot) const;
	int FindStackIndex( const Template&, int, bool) const; //Seen it passed with -1, false //returns -1 if not found
	Entity GetItemFromSlot( gESlot Slot) const;
	void MergeStacks();
	int GetStackCount() const;

	int AssureItems( const Template&, uint32 Quality, int Amount);
	void PurgeItems( const Template&, int);

	gEUseType GetUseType( int StackIndex) const;
	Template GetTemplate( int StackIndex) const;
	Entity GetTemplateItem( int StackIndex) const;
	uint32 GetQuality( int StackIndex) const;
	bCString GetName( int StackIndex); //DID THEY FORGET THE CONST QUALIFIER HERE?
	int GetAmount( int StackIndex) const;
	gEItemCategory GetCategory( int StackIndex) const;
	bool IsStackMerchandise( int StackIndex);

	int SplitStack( int StackIndex, int Amount);
	bool EquipStack( int StackIndex);
	bool EquipStackToSlot( int StackIndex, gESlot Slot);
	bool UnEquipStack( int StackIndex);
	bool DeleteStack( int StackIndex);

	Entity GetTreasureSet1() const;
	Entity GetTreasureSet2() const;
	Entity GetTreasureSet3() const;
	Entity GetTreasureSet4() const;
	Entity GetTreasureSet5() const;
	bool IsGeneratedPlunder() const;

	bool PrintMissingRequirements( int, bool) const;
	void SetGeneratedPlunder( bool);
};

/*
ActivateSkill(Template const &)                    0000000010007000 1267   
ApplyQuality(int,ulong,int)                        0000000010007BD0 1293   
ArrangeStacks(void)                                0000000010006F90 1294   
AssignStackToQuickSlot(int,int)                    0000000010006880 1295   
AssureAll(void)                                    0000000010006E60 1296   
AssureItems(Template const &,ulong,int)            0000000010006D20 1297   
AssureItemsEx(Template const &,ulong,int,int,bool) 0000000010006E00 1298   
AttachTo(eCEntity *)                               0000000010006400 1338   
AttachTo(eCEntityPropertySet *)                    0000000010002E60 1339   
ConsumeItems(int,int)                              0000000010006AF0 1401   
CopyFrom(PSInventory const &)                      0000000010002E80 1423   
CreateItems(Template const &,ulong,int)            0000000010006CE0 1449   
DeactivateSkill(Template const &)                  0000000010007050 1451   
DeleteItems(int,int)                               0000000010006B10 1453   
DeleteStack(int)                                   0000000010006B60 1454   
DropItemFromSlot(gESlot)                           00000000100067C0 1456   
DropItemsFromSlot(gESlot,int)                      00000000100067F0 1457   
DropStack(int,bCMatrix const &)                    0000000010006780 1458   
EquipStack(int)                                    0000000010006A00 1482   
EquipStackToSlot(int,gESlot)                       00000000100069E0 1483   
ExecuteItem(int)                                   0000000010006B80 1484   
FindStackIndex(Template const &,int,bool)          0000000010006C20 1491   
FindStackIndex(gESlot)                             0000000010006C00 1492   
FindStackIndexByQuickSlot(int)                     0000000010006CA0 1493   
GeneratePlunderInvFromTreasureSets(void)           00000000100076D0 1497   
GenerateTradeInvFromTreasureSets(void)             00000000100076E0 1498   
GetAmount(int)                                     00000000100064B0 1510   
GetCategory(int)                                   00000000100066F0 1527   
GetDefaultItemFromSlot(gESlot)                     0000000010006990 1551   
GetEquipSlot(gEUseType)                            00000000100068B0 1567   
GetEquipSlotAlt(gEUseType)                         00000000100068F0 1568   
GetGeneratedStackCount(void)                       0000000010007970 1577   
GetItemAmount(Template const &)                    0000000010006650 1597   
GetItemAmount(gEUseType)                           00000000100065D0 1598   
GetItemFromSlot(gESlot)                            0000000010006950 1599   
GetLargestStackForTransfer(Template const &,int)   0000000010007E00 1601   
GetName(int)                                       0000000010006540 1628   
GetQuality(int)                                    0000000010007BA0 1658   
GetSkillActivationCount(Template const &)          0000000010007190 1676   
GetSlotFromStack(int)                              0000000010006930 1679   
GetStackCount(void)                                0000000010006BF0 1686   
GetTemplate(int)                                   0000000010006710 1697   
GetTemplateItem(int)                               0000000010006FB0 1698   
GetTreasureSet1(void)                              0000000010007740 1707   
GetTreasureSet2(void)                              00000000100077A0 1708   
GetTreasureSet3(void)                              0000000010007800 1709   
GetTreasureSet4(void)                              0000000010007860 1710   
GetTreasureSet5(void)                              00000000100078D0 1711   
GetUseType(int)                                    00000000100066D0 1716   
HasItems(Template const &,int)                     0000000010006460 1741   
HasItems(gEUseType,int)                            0000000010006440 1742   
HasLearnedSkill(Template const &)                  0000000010007140 1743   
HasLearnedSpell(Template const &)                  0000000010007230 1744   
HoldLeftStack(int)                                 0000000010006A60 1748   
HoldRightStack(int)                                0000000010006A80 1749   
HoldStacks(int,int)                                0000000010006A40 1750   
InsertStack(Entity const &)                        0000000010006760 1752   
IsGenerated(int)                                   0000000010007940 1784   
IsGeneratedPlunder(void)                           0000000010007700 1785   
IsGeneratedTrade(void)                             0000000010007730 1786   
IsPermanent(int)                                   0000000010006480 1807   
IsStackMerchandise(int)                            0000000010007DD0 1824   
IsValid(void)                                      0000000010001330 1857   
MergeStacks(void)                                  0000000010006F90 1886   
PrintMissingRequirements(int,bool)                 0000000010007280 1923   
PurgeItems(Template const &,int)                   0000000010007EB0 1929   
RefreshTradeInvFromTreasureSets(void)              00000000100076F0 1932   
SetAmount(int,ulong)                               0000000010006CC0 1948   
SetGeneratedPlunder(bool)                          0000000010007710 1971   
SetQuality(int,ulong,ulong)                        0000000010007C70 2013   
SortStacks(void)                                   0000000010006FA0 2050   
SplitStack(int,int)                                0000000010006F50 2052   
StackTradingGold(void)                             0000000010007D00 2053   
SwapSlots(gESlot,gESlot)                           0000000010006820 2102   
Synthesize(Entity const &,int)                     00000000100079D0 2103   
TeachSkill(Template const &)                       00000000100070A0 2104   
TeachSpell(Template const &)                       00000000100071E0 2105   
TransferAllTo(Entity &)                            0000000010007F80 2110   
TransferAmountTo(int,int,Entity &)                 00000000100064D0 2111   
UnEquipStack(int)                                  0000000010006A20 2124   
UpdateVisibility(void)                             0000000010006BE0 2130   
UseStack(int)                                      0000000010006AA0 2131   
*/