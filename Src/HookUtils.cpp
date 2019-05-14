

#include <math.h>
#include "DLL_All.h"

#include "Script/GUI2.h"

//***********************************************
//Trampolines
__declspec(naked) eCSceneAdmin* G3HookUtils::GetSceneAdmin()
{
	__asm
	{
		mov eax, [ModuleBase::Script]
		add eax, 0x8060
		jmp eax
	};
}


//***********************************************
//ScriptProcessingUnit
Entity G3HookUtils::SPU_GetSelf( gCScriptProcessingUnit& SPU, Entity* InSelfEntity)
{
	Entity SelfEntity;
	if ( InSelfEntity ) SelfEntity = *InSelfEntity;
	else                SelfEntity.AttachTo( SPU.GetSelfEntity() );
	return SelfEntity;
}
Entity G3HookUtils::SPU_GetOther( gCScriptProcessingUnit& SPU, Entity* InOtherEntity)
{
	Entity OtherEntity;
	if ( InOtherEntity ) OtherEntity = *InOtherEntity;
	else                 OtherEntity.AttachTo( SPU.GetOtherEntity() );
	return OtherEntity;
}

//***********************************************
// Player Utils
int G3HookUtils::GetKillXPMultiplier()
{
	int Mult = ((int*)&eCApplication::GetInstance().GetEngineSetup())[0x7C];
	if ( Mult > 0 )
		return Clamp( Mult, 0, 200);
	return 100;
}

int G3HookUtils::GetQuestXPMultiplier()
{
	static const uint8 B_UpdatePack[] = { 0xBA, 0x00, 0x7E, 0x42, 0x00 };
	if ( !memcmp( ModuleBase::Script_Game + 0x4E351, B_UpdatePack, 5) ) //UpdatePack addon: Quest XP multiplier
	{
		int UpdatePack_Multiplier = *(int*)0x427E00;
		if ( UpdatePack_Multiplier > 0 )
			return Clamp( UpdatePack_Multiplier, 0, 200);
	}
	return 100;
}

//***********************************************
// NPC Utils
float G3HookUtils::RangedAttackDistance( Entity& Entity)
{
	float Result = 1700.0f;
	if ( Entity.NPC.IsValid() )
	{
		if ( Entity.NPC->Class == gEClass_Ranger )
			Result += 300.0f;
		Result += (float)(Entity.NPC->Level * 10);
	}
	return Result;
}

int G3HookUtils::NPC_Max_Dex( Entity& Entity)
{
	int Level = Entity.NPC.PS->Level;
	int LevelMax = Entity.NPC.PS->LevelMax;
	int Modifier = 0;
	if ( Entity.NPC.PS->PoliticalAlignment == gEPoliticalAlignment_Ass 
		|| Entity.NPC.PS->PoliticalAlignment == gEPoliticalAlignment_Mid
		|| Entity.NPC.PS->PoliticalAlignment == gEPoliticalAlignment_Nom )
		Modifier = 20;
	switch ( Entity.NPC.PS->Class )
	{
	case gEClass_Mage:   return  70 + Modifier + (Level + LevelMax);
	case gEClass_Ranger: return 100 + Modifier + (Level*2 + LevelMax) * 3 / 2;
	default:             return  80 + Modifier + (Level + LevelMax) * 3 / 2;
	}
}

int G3HookUtils::NPC_Max_Str( Entity& Entity)
{
	int Level = Entity.NPC.PS->Level;
	int LevelMax = Entity.NPC.PS->LevelMax;
	int Modifier = 0;
	if ( Entity.NPC.PS->PoliticalAlignment == gEPoliticalAlignment_Ass 
		|| Entity.NPC.PS->PoliticalAlignment == gEPoliticalAlignment_Mid
		|| Entity.NPC.PS->PoliticalAlignment == gEPoliticalAlignment_Nom )
		Modifier = -20;
	switch ( Entity.NPC.PS->Class )
	{
	case gEClass_Mage:    return  70 + Modifier + (Level + LevelMax);
	case gEClass_Paladin:
	case gEClass_Warrior: return 100 + Modifier + (Level + LevelMax*2) * 3 / 2;
	default:              return  80 + Modifier + (Level + LevelMax) * 3 / 2;
	}
}

int G3HookUtils::NPC_Max_Int( Entity& Entity)
{
	int Level = Entity.NPC.PS->Level;
	int LevelMax = Entity.NPC.PS->LevelMax;
	switch ( Entity.NPC.PS->Class )
	{
	case gEClass_Mage:    return  50 + (Level + LevelMax) * 2;
	case gEClass_Paladin: return  10 + (Level + LevelMax) * 2;
	default:              return  10 + (Level + LevelMax) * 3 / 2;
	}
}

int G3HookUtils::GetDexReq( PSItem& Item)
{
	if ( Item.IsValid() )
	{
		ReqAttrib* Requirements = (ReqAttrib*)&Item->ReqAttrib1Tag;
		for ( int i=0 ; i<4 ; i++ )
			if ( Requirements[i].Tag == "DEX" )
				return Requirements[i].Value;
	}
	return 0;
}
int G3HookUtils::GetStrReq( PSItem& Item)
{
	if ( Item.IsValid() )
	{
		ReqAttrib* Requirements = (ReqAttrib*)&Item->ReqAttrib1Tag;
		for ( int i=0 ; i<4 ; i++ )
			if ( Requirements[i].Tag == "STR" )
				return Requirements[i].Value;
	}
	return 0;
}
int G3HookUtils::GetIntReq( PSItem& Item)
{
	if ( Item.IsValid() )
	{
		ReqAttrib* Requirements = (ReqAttrib*)&Item->ReqAttrib1Tag;
		for ( int i=0 ; i<4 ; i++ )
			if ( Requirements[i].Tag == "INT" )
				return Requirements[i].Value;
	}
	return 0;
}



//***********************************************
// Weapon equipper
int G3HookUtils::EquipBestOnSlot( Entity& Other, gESlot Slot, gEUseType RestrictType, int MaxDex, int MaxStr, int MaxInt)
{
	if ( !Other.Inventory.IsValid() )
		return -1;

	int SelectedStack = -1;
	int32 BestScore = WeaponScore( Other.Inventory.GetItemFromSlot( Slot), gEQuality_Ice|gEQuality_Fire);

	for ( int i=Other.Inventory.GetStackCount()-1 ; i>=0 ; i-- )
	{
		bool bEquip = false;
		gEUseType UseType = Other.Inventory.GetUseType(i);
		if ( RestrictType != gEUseType_None )
			bEquip = (UseType == RestrictType);
		else if ( Slot == gESlot_BackRight )
			bEquip = (UseType == gEUseType_1H) || (UseType == gEUseType_2H) || (UseType == gEUseType_Axe) || (UseType == gEUseType_Staff);

		// Do not equip weapons the player can buy
		gCInventoryStack* Stack = Other.Inventory->GetStack(i);
		if ( bEquip && Stack && (Stack->Type == gEStackType_Merchandise) && !(Stack->GetQuality() & (gEQuality_Worn|gEQuality_Sharp)) )
			bEquip = false;
		if ( bEquip && Other.Inventory.FindStackIndex(gESlot_BackRight) == i )
			bEquip = false;

		if ( bEquip )
		{
			Entity TemplateItem = Other.Inventory.GetTemplateItem(i);
			int32 OtherScore = WeaponScore( TemplateItem, gEQuality_Ice|gEQuality_Fire);
			if ( OtherScore > BestScore 
			&& GetDexReq(TemplateItem.Item) <= MaxDex
			&& GetStrReq(TemplateItem.Item) <= MaxStr
			&& GetIntReq(TemplateItem.Item) <= MaxInt )
			{
				SelectedStack = i;
				BestScore = OtherScore;
			}
		}
	}
	if ( SelectedStack >= 0 )
	{
		if ( Other.Inventory.GetAmount( SelectedStack) > 1 )
			SelectedStack = Other.Inventory.SplitStack( SelectedStack, 1);
		gCInventoryStack* Stack = Other.Inventory->GetStack( SelectedStack);
		if ( Stack && Stack->Type == gEStackType_Merchandise && (Stack->GetQuality() & gEQuality_Worn) )
			Stack->Type = gEStackType_Normal;
		Other.Inventory.EquipStackToSlot( SelectedStack, Slot);
	}
	return SelectedStack;
}



int G3HookUtils::EquipBestHelmet( Entity& Other)
{
	if ( !Other.Inventory.IsValid() )
		return -1;

	int SelectedStack = -1;
	Entity CurrentHelmet = Other.Inventory.GetItemFromSlot( gESlot_Helmet);
	int BestPrice = CurrentHelmet.Item.GetGoldValue();
	
	for ( int i=Other.Inventory.GetStackCount()-1 ; i>=0 ; i-- )
		if ( Other.Inventory.GetUseType(i) == gEUseType_Helmet && !Other.Inventory.IsStackMerchandise(i) )
		{
			Entity TemplateItem = Other.Inventory.GetTemplateItem(i);
			int Price = TemplateItem.Item.GetGoldValue();
			if ( Price > BestPrice )
			{
				Price = BestPrice;
				SelectedStack = i;
			}
		}
	if ( SelectedStack >= 0 )
	{
		if ( Other.Inventory.GetAmount( SelectedStack) > 1 )
			SelectedStack = Other.Inventory.SplitStack( SelectedStack, 1);
		Other.Inventory.EquipStackToSlot( SelectedStack, gESlot_Helmet);
	}
	return SelectedStack;
}





//***********************************************
// Weapon template enumerator
void G3HookUtils::EnumerateWeaponTemplates()
{
	eCSceneAdmin* SceneAdmin = GetSceneAdmin();
	if ( !SceneAdmin )
		return;

	typedef bTValMap<bCPropertyID,eCTemplateEntity*> Map;
	typedef Map::bSNode Node;

	Map& TemplateMap = *(Map*)((uint8*)SceneAdmin + 0x34);
	TemplateCriticalSection().Acquire();

	int ItemsFound = 0;
	for ( int i=0 ; i<TemplateMap.NodeList.Num ; i++ )
		for ( Node* Link=TemplateMap.NodeList[i] ; Link ; Link=Link->Next )
		{
			if ( !Link->Value->IsDeleted() && Link->Value->IsValid() && Link->Value->GetName().Contains("It_",0) )
			{
				gCItem_PS* Item = (gCItem_PS*)Link->Value->GetPropertySet( eEPropertySetType_Item);
				gCDamage_PS* Damage = (gCDamage_PS*)Link->Value->GetPropertySet( eEPropertySetType_Damage);
				if ( Item && Damage )
					ItemsFound++;
			}
		}

	((GUI2*)nullptr)->PrintGameMessage( bCUnicodeString(ItemsFound)
		+ bCUnicodeString(" + ") 
		+ bCUnicodeString(TemplateMap.NodeCount), (gEGameMessageType)2); //White

	TemplateCriticalSection().Release();
}

Template G3HookUtils::UpgradeWeaponry( Entity& TemplateBest, int MinScore, int MaxScore, int MaxDex, int MaxStr, int MaxInt)
{
	eCSceneAdmin* SceneAdmin = GetSceneAdmin();
	if ( !SceneAdmin || !TemplateBest.Interaction->IsValid() || !TemplateBest.Item->IsValid() || !TemplateBest.Damage->IsValid() )
		return Template();

	if ( WeaponScore( TemplateBest, TemplateBest.Item->Quality) == MaxScore )
		return TemplateBest.GetTemplate();

	typedef bTValMap<bCPropertyID,eCTemplateEntity*> Map;
	typedef Map::bSNode Node;

	Map& TemplateMap = *(Map*)((uint8*)SceneAdmin + 0x34);
	TemplateCriticalSection().Acquire();

	Node* BestNode = nullptr;
	int BestScore = 0;
	for ( int i=0 ; i<TemplateMap.NodeList.Num ; i++ )
		for ( Node* Link=TemplateMap.NodeList[i] ; Link ; Link=Link->Next )
		{
			if ( !Link->Value->IsDeleted() && Link->Value->IsValid() && Link->Value->GetName().Contains("It_",0) )
			{
				auto* Item        = GetPropertySet<gCItem_PS>( Link->Value);
				auto* Damage      = GetPropertySet<gCDamage_PS>( Link->Value);
				auto* Interaction = GetPropertySet<gCInteraction_PS>( Link->Value);
				int Score = WeaponScore( Item, Damage, Interaction, TemplateBest.Item->Quality);
				if ( (Score > BestScore) && !Item->MissionItem 
				&& (Score >= MinScore) && (Score <= MaxScore)
				&& Interaction->UseType == TemplateBest.Interaction->UseType
				&& MaxDex >= GetDexReq( *(PSItem*)&Item)
				&& MaxStr >= GetStrReq( *(PSItem*)&Item)
				&& MaxInt >= GetIntReq( *(PSItem*)&Item) )
				{
					BestNode = Link;
					BestScore = Score;
				}
			}
		}

	Template Result;
	if ( BestNode )
		Result = BestNode->Key;

	TemplateCriticalSection().Release();
	return Result;
}

int G3HookUtils::WeaponScore( Entity& WeaponEntity, uint32 PreferredQuality)
{
	return WeaponScore( WeaponEntity.Item.PS, WeaponEntity.Damage.PS, WeaponEntity.Interaction.PS, PreferredQuality);
}


int G3HookUtils::WeaponScore( gCItem_PS* Item, gCDamage_PS* Damage, gCInteraction_PS* Interaction, uint32 PreferredQuality)
{
	int Score = 0;
	if ( Item && Damage && Interaction )
	{
		Score = Damage->DamageAmount;
		if ( Interaction->UseType == gEUseType_Staff )
		{
			Score /= 2;
			Score += GetIntReq( *(PSItem*)&Item);
		}
		uint32 CombinedQuality = Item->Quality & PreferredQuality;
		if ( CombinedQuality & gEQuality_Blessed )
			Score += 20;
		if ( CombinedQuality & gEQuality_Poison )
			Score += 10;
		if ( CombinedQuality & gEQuality_Ice )
			Score += 5;
		if ( CombinedQuality & gEQuality_Fire )
			Score += 5;
	}
	else if ( Item && Interaction && (Interaction->UseType == gEUseType_Shield) )
	{
		Score = ((int)sqrt(Item->GoldValue) + GetStrReq( *(PSItem*)&Item)) / 3;
	}
	return Score;
}



void G3HookUtils::PartySneak()
{
/*	Entity PlayerEntity = Entity::GetPlayer();
	bTValArray<eCEntity*> Members = Leader.Party.GetMembers(0);
	*/
}
