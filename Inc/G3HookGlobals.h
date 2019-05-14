#pragma once


#include "Script/Entity.h"
#include "Game/gCScriptProcessingUnit.h"

namespace ModuleBase
{
	extern uint8* Script_Game;
	extern uint8* Script;
	extern uint8* Game;
	extern uint8* Engine;
	extern uint8* SharedBase;
};

namespace Util
{
	int Rand( int Num);

	void EncodeJump( uint8* At, uint8* To);
	void EncodeCall( uint8* At, uint8* To);
	void ModifyPointer( uint8* At, uint8* To);
	template<typename T> void ModifyData( uint8* At, T Data);
};

class DLLEXPORT G3HookUtils
{
public:
	static eCSceneAdmin* GetSceneAdmin();

	static Entity SPU_GetSelf( gCScriptProcessingUnit& SPU, Entity* InSelfEntity);
	static Entity SPU_GetOther( gCScriptProcessingUnit& SPU, Entity* InOtherEntity);
	static int GetKillXPMultiplier();
	static int GetQuestXPMultiplier();
	static float RangedAttackDistance( Entity& Entity);
	static int NPC_Max_Dex( Entity& Entity);
	static int NPC_Max_Str( Entity& Entity);
	static int NPC_Max_Int( Entity& Entity);
	static int GetDexReq( PSItem& Item);
	static int GetStrReq( PSItem& Item);
	static int GetIntReq( PSItem& Item);
	static int EquipBestOnSlot( Entity& Other, gESlot Slot, gEUseType RestrictType=gEUseType_None, int MaxDex=999, int MaxStr=999, int MaxInt=999);
	static int EquipBestHelmet( Entity& Other);
	static Template UpgradeWeaponry( Entity& TemplateBest, int MinScore, int MaxScore, int MaxDex=999, int MaxStr=999, int MaxInt=999);
	static int WeaponScore( Entity& WeaponEntity, uint32 PreferredQuality);
	static int WeaponScore( gCItem_PS* Item, gCDamage_PS* Damage, gCInteraction_PS* Interaction, uint32 PreferredQuality);
	static void PartySneak();

	static void EnumerateWeaponTemplates();

	static Entity& None()
	{ return *(Entity*)(ModuleBase::Script + 0x66D08); }

	static bCCriticalSectionWin32& TemplateCriticalSection()
	{ return *(bCCriticalSectionWin32*)(ModuleBase::Engine + 0x60B494); }
};

class G3HookGlobal : public G3HookUtils
{
public:
	typedef int (__stdcall *F_ScriptProc_EEI)( gCScriptProcessingUnit&, Entity*, Entity*, int);
	static F_ScriptProc_EEI NextLevelXP;
	static F_ScriptProc_EEI AttitudeTo;
	static F_ScriptProc_EEI AssessHit;
	static F_ScriptProc_EEI IsGateGuard;
	static F_ScriptProc_EEI RefreshWeaponry;
	static F_ScriptProc_EEI SetAttackReason;
	typedef bool (__stdcall *F_UseTypesE)( gEUseType RightHand, gEUseType LeftHand, Entity Entity);
	static F_UseTypesE IsUseTypes;
	typedef int (__stdcall *F_CanKnockDown)( Entity);
	static F_CanKnockDown CanKnockDown;

	//Own utils

	//Hooks
	static int ManaRegenTimer( Entity InEntity);
	static int KillXP( gCScriptProcessingUnit&, Entity*, Entity*, int);
	static int AssessHit_Proxy( gCScriptProcessingUnit&, Entity*, Entity*, int);
	static int ItemTradePrice( gCScriptProcessingUnit& SPU, Entity* Buyer, Entity* Seller, int SellingSlot);
	static int EquipWeaponry_Hook( gCScriptProcessingUnit& SPU, Entity* E1, Entity* E2, int);
	static int RefreshWeaponry_Proxy( gCScriptProcessingUnit& SPU, Entity* E1, Entity* E2, int);
	static int FAI_Ranged( gCScriptProcessingUnit& SPU, Entity* InShooter, Entity* InTarget, int);

	static int RefreshWeaponry_Rev( gCScriptProcessingUnit& SPU, Entity* E1, Entity* E2, int);

	
};

class G3HookPSInventory : public PSInventory
{
public:
	int AssureItems_Middleman( const Template&, uint32 Quality, int Quantity);
};

class G3HookEntity : protected Entity
{
public:
	void StartTransform_Hook( Entity&, float Seconds, bool);
	void EndTransform_Hook();
};

