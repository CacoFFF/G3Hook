
#include "DLL_All.h"
#include "Game/gCScriptAdmin.h"
#include "Engine/eCLocString.h"

#include "Script/GUI2.h"
#include "Script/EffectSystem.h"



static bool UnknownEngineBool()
{
	return ((char*)&eCApplication::GetInstance().GetEngineSetup())[0x1EA] != 0;
}



//********************************************************************************************
// Mana Regeneration.
// This function is called every second and returns the amount of mana the hero should recover
// Changes:
// - Hero can regenerate mana during transformation (dragon, for example)
// - Fixes regeneration being rounded down to integer.
// ** So if you have 250 mana, you won't be stuck with recovering just 2 mana per second.
// ** But instead recover 2-3 every second.
static int ManaRegenAcc = 0;
static int MasterMageActive = 0;
int G3HookGlobal::ManaRegenTimer( Entity InEntity)
{
	int Result = 0;
	Entity PlayerEntity = Entity::GetPlayer();

	if ( InEntity == PlayerEntity )
	{
		// Remember if PC_Hero has mana regeneration skill (gets lost during transformation)
		if ( !InEntity.NPC.IsTransformed() )
			MasterMageActive = InEntity.Inventory.IsSkillActive( Template("Perk_MasterMage"));

		if ( MasterMageActive )
		{
			// Only consider up to 500 mana points
			int Acc = 500;
			if ( UnknownEngineBool() ) //TODO: What's this?
				Acc = Min( Acc, InEntity.PlayerMemory.GetManaPointsMax() );

			// Fixes integer rounding when dividing by 100
			ManaRegenAcc += Acc;
			Result = Min( 5, ManaRegenAcc / 100);
			ManaRegenAcc = ManaRegenAcc % 100;
		}
//		EnumerateWeaponTemplates();
	}
	return Result;
}





static bool SameSquad( const Entity& A, const Entity& B)
{
	if ( !A.NPC.IsValid() || !B.NPC.IsValid() )
		return false;

	Entity Leader_A = A.Party.GetPartyLeader();
	Entity Leader_B = B.Party.GetPartyLeader();

	//NPC to NPC
	if ( A == Leader_B || B == Leader_A || (Leader_A.Instance && (Leader_A == Leader_B)) )
		return true;

	//Consider player memory (should cover transformed player)
	if ( (Leader_A.PlayerMemory.IsValid() && B.PlayerMemory.IsValid())
		|| (Leader_B.PlayerMemory.IsValid() && A.PlayerMemory.IsValid()) )
		return true;

	return false;
}
static int HardcodedXP( gESpecies Species)
{
	switch (Species)
	{
	case gESpecies_Lizard:
	case gESpecies_Fish:
	case gESpecies_Meatbug:
	case gESpecies_Vulture:
	case gESpecies_Rabbit:
	case gESpecies_Chicken:
	case gESpecies_Molerat:
	case gESpecies_Snake:
	case gESpecies_Spider:
	case gESpecies_Turtle:
	case gESpecies_Bird:
	case gESpecies_Ray:
	case gESpecies_Scorpion:
	case gESpecies_Seagull:
	case gESpecies_Walrus:
	case gESpecies_Whale:
	case gESpecies_Eagle:
		return 10;
	case gESpecies_Pig:
	case gESpecies_Cow:
		return 20;
	default:
		return 0;
	}
}
static void NPC_LevelUp( gCScriptProcessingUnit& SPU, const Entity& Killer, const Entity& Victim, int XP)
{
	if ( !Killer.Party.IsValid() )
		return;

	Entity Leader = Killer.Party.GetPartyLeader();
	if ( !Leader.Instance )
		Leader = Killer;
	if ( !Leader.Party.IsValid() )
		return;

	if ( Victim.NPC.IsValid() )
		XP += Max( (int)Victim.NPC->Level+1, 3) * G3HookUtils::GetKillXPMultiplier() / 10;

	bTValArray<eCEntity*> Members = Leader.Party.GetMembers(0);
	Entity PartyMember = Leader;
	for ( int i=-1 ; i<Members.Num ; i++ )
	{
		if ( i>=0 )
			PartyMember = Entity( Members.Data[i] );

		if ( !PartyMember.NPC.IsValid() || PartyMember.PlayerMemory.IsValid() ) //Non-players only
			continue;

		//Try increase base Level
		int Factor = 1 + (int)(PartyMember == Killer);
		int BaseXP = 0;
		int NextXP = (*G3HookGlobal::NextLevelXP)(SPU,&PartyMember,&PartyMember,0);
		if ( PartyMember.NPC.PS->Level > 0 )
		{
			PartyMember.NPC.PS->Level--;
			BaseXP = (*G3HookGlobal::NextLevelXP)(SPU,&PartyMember,&PartyMember,0);
			PartyMember.NPC.PS->Level++;
		}
		if ( Util::Rand( NextXP - BaseXP) <= XP * Factor)
		{
			Factor *= (1+PartyMember.NPC.PS->LevelMax); //When level up, increase LevelMax chance of increasing as well
			PartyMember.NPC.PS->Level++;
		}

		uint32 RealLevel = PartyMember.NPC.PS->Level;
		PartyMember.NPC.PS->Level = PartyMember.NPC.PS->LevelMax;
		BaseXP = 0;
		NextXP = (*G3HookGlobal::NextLevelXP)(SPU,&PartyMember,&PartyMember,0);
		if ( PartyMember.NPC.PS->Level-- > 0 )
			BaseXP = (*G3HookGlobal::NextLevelXP)(SPU,&PartyMember,&PartyMember,0);
		PartyMember.NPC.PS->Level = RealLevel;
		if ( Util::Rand( NextXP - BaseXP) <= XP * Factor)
		{
			PartyMember.NPC.PS->LevelMax++;
			if ( PartyMember.DamageReceiver.IsValid() )
			{
				PartyMember.DamageReceiver.PS->HitPoints += 10;
				PartyMember.DamageReceiver.PS->HitPointsMax += 10;
			}
		}
	}
}
int G3HookGlobal::KillXP( gCScriptProcessingUnit& SPU, Entity* E1, Entity* E2, int InXP)
{
	if ( !UnknownEngineBool() )
		return 0;

	Entity Victim = SPU_GetSelf( SPU, E1);
	Entity Killer = SPU_GetOther( SPU, E2);
	Entity Player = Entity::GetPlayer();
	Entity World = Entity::GetWorldEntity();

	if ( Player == Victim
		|| (Victim.Party.IsValid() && Victim.Party->PartyMemberType == gEPartyMemberType_Summoned) )
		return 0;

	// Kill command
	if ( Victim.NPC.IsValid() && !Killer.NPC.IsValid() )
		Killer = Player;
	
	int XP = 0;
	if ( Victim.NPC.IsValid() && Killer.NPC.IsValid() &&
		((Player == Killer) || SameSquad(Player,Killer) //Enhanced party checker
		|| (Killer.NPC->AttackReason == gEAttackReason_PlayerCommand) //Summon Animals
		|| (Killer.NPC->Type == gENPCType_Friend && !Player.PlayerMemory->TalkedToDiego)) ) //Ardea battle
	{
		XP = HardcodedXP( Victim.NPC->Species);
		if ( XP == 0 )
			XP = Max( (int)Victim.NPC->Level * 10, 50);
		// Round to multiples of 5 (no float ops)
		XP = ((XP * GetKillXPMultiplier() / 100 + 2) / 5) * 5;
		((GUI2*)nullptr)->PrintGameMessage( eCLocString( bCString("GO_XP")).GetString()
		                     + bCUnicodeString(" + ") 
		                     + bCUnicodeString(XP), (gEGameMessageType)2); //White
	}

	if ( /*Victim == World || !Victim.Instance*/ InXP > 0 )
	{
		InXP = InXP * GetQuestXPMultiplier() / 20;
		((GUI2*)nullptr)->PrintGameMessage( eCLocString( bCString("GO_XP")).GetString()
			+ bCUnicodeString(" + ") 
			+ bCUnicodeString(InXP), (gEGameMessageType)5); //Green
		XP += InXP;
	}

	// Killers may gain levels
	NPC_LevelUp( SPU, Killer, Victim, InXP);

	if ( XP > 0 )
	{
		// Process levels one by one
		int LevelUps = 0;
		Player.PlayerMemory->XP += XP;
		int XP_Next;
		while ( (XP_Next=(*NextLevelXP)(SPU,&Player,E1,0)) < Player.PlayerMemory->XP )
		{
			Player.NPC->Level++;
			((GUI2*)nullptr)->PrintGameMessage( eCLocString( bCString("GO_LevelUp")).GetString(), (gEGameMessageType)0);
//			((GUI2*)nullptr)->PrintGameMessage( bCUnicodeString(XP_Next), (gEGameMessageType)2);
			if ( LevelUps++ == 0 )
				EffectSystem::StartEffect( bCString("eff_event_levelup_01"), Player);
			Player.PlayerMemory->LPAttribs += 10;
			if ( Player.Inventory.IsSkillActive( Template("Perk_Learn")) )
				Player.PlayerMemory->LPAttribs++;
			if ( LevelUps > 3 )
				break;
		}
		return 1;
	}
	return 0;
}


void G3HookEntity::StartTransform_Hook( Entity& Other, float Seconds, bool KeepPlayer)
{
	if ( IsPlayer() ) //We'll assume PlayerMemory is present, so we call directly on gCPlayerMemory_PS
	{
		if ( !KeepPlayer )
		{
			Instance->Enable( false);
			Instance->EnableCollision( false);
			Navigation.SetDCCEnabled( false);
		}
		bCString HP_Str("HP");
		PlayerMemory->SetSecondsTransformRemain( 0);
		int MaxHP = PlayerMemory->GetMaximum( HP_Str);
		int CurHP = PlayerMemory->GetValue  ( HP_Str);
		int Level = NPC->Level;

		//Get Party members!!
		bTValArray<eCEntity*> PartyMembers = Party.GetMembers(false);

		Other.StartTakeOver();
		Entity PlayerEntity = Entity::GetPlayer(); //PlayerMemory SHOULD exist
		PlayerEntity.ScriptRoutine.ContinueRoutine();
		PlayerEntity.PlayerMemory->SetSecondsTransformRemain( Seconds);
		PlayerEntity.NPC.EnableStatusEffects( gEStatusEffects_Transformed, true);

		//Seconds is directly related to INT, Perk_Druid and Perk_WaterMage
		//So the creature will be more durable if hero has those or higher base HP
		//Since damage received scales terribly on higher difficulty, added that extra tweak
		int ExtraHP = ((MaxHP - 200) + int(Seconds)) * (4+Entity::GetCurrentDifficulty()) / 16;
		if ( ExtraHP > 0 )
			PlayerEntity.PlayerMemory.AddHitPointsMax( ExtraHP);
		PlayerEntity.NPC->SetLevel( Level);
		int CurHPCreature = PlayerEntity.PlayerMemory->GetMaximum( HP_Str) * CurHP / MaxHP;
		PlayerEntity.PlayerMemory.SetHitPoints( CurHPCreature);

		//Transfer party members to new Entity
		if ( !KeepPlayer )
		{
			for ( int i=0 ; i<PartyMembers.Num ; i++ )
				if ( PartyMembers.Data[i] 
				&& (PartyMembers.Data[i] != PlayerEntity.Instance)
				&& (PartyMembers.Data[i] != Instance) )
				{
					Entity PartyMember( PartyMembers.Data[i]);
					PlayerEntity.Party.Add( PartyMember);
				}
		}
	}
}

void G3HookEntity::EndTransform_Hook()
{
	if ( IsPlayer() )
	{
		PlayerMemory->SetSecondsTransformRemain( 0);
		NPC.EnableStatusEffects( gEStatusEffects_Transformed, false);
		NPC.EnableStatusEffects( gEStatusEffects_Ghost, false);
		bCString HP_Str("HP");
		int MaxHP = PlayerMemory->GetMaximum( HP_Str);
		int CurHP = PlayerMemory->GetValue  ( HP_Str);
		//Get Party members!!
		bTValArray<eCEntity*> PartyMembers = Party.GetMembers(false);
		EndTakeOver();

		Entity PlayerEntity = Entity::GetPlayer();
		if ( PlayerEntity.Instance )
		{
			PlayerEntity.Instance->Enable( true);
			PlayerEntity.Instance->EnableCollision( true);
		}
		eCEntity* OtherInstance;
		gCDynamicCollisionCircle_PS* DCC;
		if ((OtherInstance=PlayerEntity.Navigation->GetEntity()) != nullptr
		&& (DCC=(gCDynamicCollisionCircle_PS*)OtherInstance->GetPropertySet( eEPropertySetType_06)) != nullptr )
			DCC->SetDCCEnabled( true);
		if ( PlayerEntity.Inventory.IsValid() )
			PlayerEntity.Inventory->UpdateVisibility();
		PlayerEntity.PlayerMemory->SetSecondsTransformRemain( 0);
		int RestoreHP = PlayerEntity.PlayerMemory->GetMaximum( HP_Str) * CurHP / MaxHP;
		PlayerEntity.PlayerMemory.SetHitPoints( RestoreHP);

		//Transfer party members back to PC_Hero
		for ( int i=0 ; i<PartyMembers.Num ; i++ )
			if ( PartyMembers.Data[i] 
			&& (PartyMembers.Data[i] != PlayerEntity.Instance)
			&& (PartyMembers.Data[i] != Instance) )
			{
				Entity PartyMember( PartyMembers.Data[i]);
				PlayerEntity.Party.Add( PartyMember);
			}
	}
}


//********************************************************************************************
// The game wants NPC's to have arrows when necessary, AssureItems not only creates the items
// in question, but also returns the corresponding slot ID in the NPC's inventory.
//
// What we'll do here is let the game do as usual, then instead scan through said NPC's
// inventory and select the slot ID of the arrows with highest possible damage amount.
//
// This will allow NPC's like Jorn to shoot the 12 Exploding arrows you give him
//
int G3HookPSInventory::AssureItems_Middleman( const Template& Model, uint32 Quality, int Quantity)
{
	int Result = AssureItems( Model, Quality, Quantity);
	if ( PS && (Model == Template("Arrow")) ) //IsValid
	{
		int BestDamage = 0;
		int BestSlot = -1;
		int Count = PS->GetStackCount();
		for ( int i=0 ; i<Count ; i++ )
		{
			if ( PS->GetStackUseType(i) == gEUseType_Arrow )
			{
				eCTemplateEntity* Entity = PS->GetStack(i)->Template.GetEntity();
				gCDamage_PS* Damage;
				if ( Entity 
				&& (Damage=(gCDamage_PS*)Entity->GetPropertySet(eEPropertySetType_Damage)) != nullptr
				&& Damage->DamageAmount > BestDamage )
				{
					BestDamage = Damage->DamageAmount;
					BestSlot = i;
				}
			}
		}
		if ( BestSlot >= 0 )
			Result = BestSlot;
	}
	return Result;
}

//********************************************************************************************
// This function processes the damage and the corresponding effects on a NPC/Player
//
// What we'll do here is wait for the game to tell us the kind of effect on the victim and
// then modify said effects if certain conditions are met.
//
// Changes:
// - Exploding arrows cause same knockdown effect as headknocks, but are deadly.
//
int G3HookGlobal::AssessHit_Proxy( gCScriptProcessingUnit& SPU, Entity* InVictim, Entity* InDamageDealer, int I1)
{
	gEAction RetAction = (gEAction)(*AssessHit)(SPU,InVictim,InDamageDealer,I1);

	Entity Victim       = SPU_GetSelf( SPU, InVictim);
	Entity DamageDealer = SPU_GetOther( SPU, InDamageDealer);

	//General purpose checks
	if ( Victim.IsNPC() && Victim.DamageReceiver.IsValid() && DamageDealer.IsItem() && DamageDealer.IsInteractObject() && DamageDealer.Damage.IsValid() )
	{
		if ( DamageDealer.Damage->DamageAmount > 0 )
		{
			//Hit by explosive arrow
			if ( (RetAction == gEAction_Stumble) 
			&& (Victim.NPC->Species == gESpecies_Human || Victim.NPC->Species == gESpecies_Orc)
			&& (DamageDealer.GetName() == "ExplosiveArrow") )
			{
				//Change properties of arrow if hasn't killed the target
				gEDamageType OldDamageType = DamageDealer.Damage->DamageType;
				DamageDealer.Damage->DamageType = gEDamageType_Impact;
				RetAction = (gEAction)(*AssessHit)(SPU,&Victim,&DamageDealer,I1);
				DamageDealer.Damage->DamageType = OldDamageType; //Makes explosive arrow not bounce off target
			}

			//Hit by weapon
			Entity DamageInstigator = DamageDealer.GetOwner();
			if ( DamageInstigator.IsNPC() && !DamageInstigator.IsPlayer() && DamageInstigator.NPC->Species == gESpecies_Human && DamageInstigator.Inventory.IsValid() )
			{
				//Add weapon damage from human NPC's
				gEUseType UseType = DamageDealer.Interaction->GetUseType();
				int PctMult = (int)(DamageDealer.Damage->DamageHitMultiplier * 100.0f);
				Entity LeftHand = DamageInstigator.Inventory.GetItemFromSlot( gESlot_LeftHand);
				Entity RightHand = DamageInstigator.Inventory.GetItemFromSlot( gESlot_RightHand);
				if ( DamageDealer == LeftHand || DamageDealer == RightHand )
					Victim.DamageReceiver->DamageAmount += DamageDealer.Damage->DamageAmount * PctMult / (100 * 10);
				else if ( UseType == gEUseType_Arrow || UseType == gEUseType_Bolt )
				{
					int ProjectileDamage = DamageDealer.Damage->DamageAmount + (RightHand.Damage.IsValid() ? RightHand.Damage->DamageAmount : 0);
					Victim.DamageReceiver->DamageAmount += ProjectileDamage * PctMult / (100 * 10);
				}
			}
		}
	}

	return RetAction;
}


//********************************************************************************************
// Here is where the price of an item during a trade is set.
//
// Some of the modifications made:
// - Orcs and orc mercenaries pay more for orc weapons (50% instead of 30%)
// - Worn weapons cost less (-60%).
//
// Note: this function is called by the GUI, but it won't provide 'buyer' field so the Inventory
// menu will display the incorrect price when dealing with a NPC.
int G3HookGlobal::ItemTradePrice( gCScriptProcessingUnit& SPU, Entity* Buyer, Entity* Seller, int SellingSlot)
{
	Entity NPC_Buy = SPU_GetSelf( SPU, Buyer);
	Entity NPC_Sell = SPU_GetOther( SPU, Seller);
	Entity PlayerEntity = Entity::GetPlayer();
	Entity Selling = NPC_Sell.Inventory.GetTemplateItem( SellingSlot);

	//Item value
	int BaseValue = Selling.Item.GetGoldValue();

	//Item factor
	float ItemFactor = 1.0f;
	if ( NPC_Sell == PlayerEntity )
	{
		if ( !NPC_Buy.IsNPC() )
			NPC_Buy = PlayerEntity.Focus.GetFocusEntity();

		ItemFactor = 0.3f;
		gEUseType UseType = Selling.Interaction->UseType;
		gETradeCategory TradeCategory = NPC_Buy.IsNPC() ? NPC_Buy.Dialog->TradeCategory : gETradeCategory_None;
		if ( (TradeCategory == gETradeCategory_Trophy 
			&& (UseType == gEUseType_TrophyFur || UseType == gEUseType_TrophySkin) )
		||	(TradeCategory == gETradeCategory_Valuable 
			&& UseType == gEUseType_Valuable) )
		{
			ItemFactor  = 0.6f; //Trophies, valuables
		}
		else if ( NPC_Buy.IsNPC() && (NPC_Buy.NPC->PoliticalAlignment == gEPoliticalAlignment_Orc) 
		&& (Selling.Interaction->UseType == gEUseType_Axe || Selling.Interaction->UseType == gEUseType_Halberd)
		&& Selling.GetName().Contains("_Orc",0) ) 
			ItemFactor = 0.5f; //Orcs and mercs pay for orc weapons
	}
	if ( NPC_Sell.Inventory.PS && NPC_Sell.Inventory.GetQuality( SellingSlot) & gEQuality_Worn )
		ItemFactor *= 0.4f; //Worn weapons cost less

	//Player factor
	float PlayerFactor = !PlayerEntity.Inventory.IsSkillActive( Template("Perk_Barter")) ? 1.0f //No barter
						: (NPC_Sell == PlayerEntity) ? 1.1f //Selling
						: 0.9f; //Buying
	if ( NPC_Buy.IsNPC() )
	{
		if ( (NPC_Sell == PlayerEntity) && (*AttitudeTo)(SPU,&NPC_Sell,&NPC_Buy,0) == gEAttitude_Friendly )
			PlayerFactor -= 0.1f;
		else if ( (*AttitudeTo)(SPU,&NPC_Buy,&NPC_Sell,0) == gEAttitude_Friendly )
			PlayerFactor += 0.1f;
	}

	//I wonder what this really is
	if ( UnknownEngineBool() )
		PlayerFactor -= 0.05f;

	return Max( 1, (int)((float)BaseValue * ItemFactor * PlayerFactor));
}

static Entity GetWeaponryTreasureSet( const Entity& EntityNPC)
{
	Entity E;
#define CHECK_TREASURE(n) E=EntityNPC.Inventory.GetTreasureSet##n(); if ( E.TreasureSet.IsValid() && (E.TreasureSet.PS->TreasureDistribution == gETreasureDistribution_Weaponry) ) return E;
	CHECK_TREASURE(1);
	CHECK_TREASURE(2);
	CHECK_TREASURE(3);
	CHECK_TREASURE(4);
	CHECK_TREASURE(5);
#undef CHECK_TREASURE
	return Entity();
}
int G3HookGlobal::RefreshWeaponry_Proxy( gCScriptProcessingUnit& SPU, Entity* E1, Entity* E2, int)
{
	Entity EntityNPC = SPU_GetSelf( SPU, E1);
	Entity Entity2 = SPU_GetOther( SPU, E2);

	if ( EntityNPC.IsPlayer() || !EntityNPC.Inventory.IsValid() || !EntityNPC.NPC.IsValid() )
		return 1;

	gESpecies Species = EntityNPC.NPC->Species;
//	if ( Species == gESpecies_Human || Species == gESpecies_Skeleton || Species == gESpecies_Zombie )
//		EquipBestHelmet( EntityNPC);

	if ( !EntityNPC.Inventory.IsGeneratedPlunder() || (*IsGateGuard)(SPU,&EntityNPC,&None(),0) || (Species != gESpecies_Human) )
		return (*RefreshWeaponry)( SPU, &EntityNPC, &Entity2, 0);

	const uint32 TimeInterval = 60 * 60 * 24; //Every day
	uint32 CurrentTime = Entity::GetTimeStampInSeconds();
	if ( CurrentTime < TimeInterval )
		return 1;

	//Hack fixes
	if ( EntityNPC.GetName() == "Diego" )
		EntityNPC.NPC->Class = gEClass_Ranger;
	else if ( EntityNPC.GetName() == "Milten" && (CurrentTime > TimeInterval * 7) ) //Become mage one week later
		EntityNPC.NPC->Class = gEClass_Mage;

	// Find default weapons
	Entity TemplateBackRight, TemplateBackLeft, TemplateBow, TemplateCrossbow;
	Entity Weaponry = GetWeaponryTreasureSet( EntityNPC);
	Weaponry.Inventory.MergeStacks();
	if ( Weaponry.Inventory.IsValid() )
	{
		for ( int i=Weaponry.Inventory.GetStackCount()-1 ; i>=0 ; i-- )
		{
			gEUseType UseType = Weaponry.Inventory.GetUseType(i);
			if ( UseType == gEUseType_1H )
			{
				TemplateBackRight = Weaponry.Inventory.GetTemplateItem(i);
				if ( Weaponry.Inventory.GetAmount(i) > 1 )
					TemplateBackLeft = TemplateBackRight;
			}
			else if ( UseType == gEUseType_Shield )
				TemplateBackLeft = Weaponry.Inventory.GetTemplateItem(i);
			else if ( UseType == gEUseType_2H || UseType == gEUseType_Axe || UseType == gEUseType_Staff )
				TemplateBackRight = Weaponry.Inventory.GetTemplateItem(i);
			else if ( UseType == gEUseType_Bow )
				TemplateBow = Weaponry.Inventory.GetTemplateItem(i);
			else if ( UseType == gEUseType_CrossBow )
				TemplateCrossbow = Weaponry.Inventory.GetTemplateItem(i);
		}
	}

	// Get maximum attributes this NPC has
	int MaxDex = NPC_Max_Dex(EntityNPC);
	int MaxStr = NPC_Max_Str(EntityNPC);
	int MaxInt = NPC_Max_Int(EntityNPC);
	Entity* WeaponryTemplates[] = { &TemplateBackRight, &TemplateBackLeft, &TemplateBow, &TemplateCrossbow };
	for ( int i=0 ; i<4 ; i++ )
	{
		MaxDex = Max( MaxDex, GetDexReq(WeaponryTemplates[i]->Item));
		MaxStr = Max( MaxStr, GetStrReq(WeaponryTemplates[i]->Item));
		MaxInt = Max( MaxStr, GetIntReq(WeaponryTemplates[i]->Item));
	}

	// Select existing weapons in inventory if possible
	static const gESlot Slots[] = { gESlot_BackRight, gESlot_BackLeft, gESlot_Bow, gESlot_Crossbow };
	for ( int i=0 ; i<4 ; i++ )
	{
		gEUseType UseType = gEUseType_None;
		if ( WeaponryTemplates[i]->Interaction.IsValid() ) //Use same type of weapon as loadout
			UseType = WeaponryTemplates[i]->Interaction->UseType;
		else if ( (EntityNPC.NPC->Class == gEClass_Ranger) && (i == 2) ) //Rangers can use bows even if not in loadout
			UseType = gEUseType_Bow;

		if ( i==0 || (UseType != gEUseType_None) ) //Back right can always be equipped
		{
			if ( EquipBestOnSlot( EntityNPC, Slots[i], UseType, MaxDex, MaxStr, MaxInt) != -1 )
			{
				*WeaponryTemplates[i] = Entity();
				EntityNPC.NPC->TimeStampDiseased = CurrentTime;
			}
		}
	}
	// Attempt to upgrade existing weapons (8 damage per day tops)
	int ScoreIncrease = ((CurrentTime - EntityNPC.NPC->TimeStampDiseased) / (TimeInterval / 8));
	if ( !EntityNPC.Inventory.GetItemFromSlot(gESlot_BackRight).Item.IsValid() ) //No weapon at hand, reset
		ScoreIncrease = 0;
	int j = Util::Rand(4); //Randomize restock order
	for ( int k=0 ; k<4 ; k++ )
	{
		int i = (k+j) % 4;
		if ( WeaponryTemplates[i]->Damage.IsValid() )
		{
			// Starter pack
			int MinScore = 0;
			int MaxScore = 10 + Util::Rand(EntityNPC.NPC->LevelMax) + Util::Rand(30);
			Entity CurrentWeapon = EntityNPC.Inventory.GetItemFromSlot(Slots[i]);
			if ( CurrentWeapon.Damage.IsValid() ) //Already has weapon, upgrade
			{
				uint32 PreferredQuality = WeaponryTemplates[i]->Item.GetQuality();
				MinScore = WeaponScore( CurrentWeapon, PreferredQuality);
				MaxScore = Min( MinScore + ScoreIncrease, WeaponScore( *WeaponryTemplates[i],PreferredQuality) );
			}
			Template NewWeaponTemplate;
			if ( MinScore < MaxScore )
				NewWeaponTemplate = UpgradeWeaponry( *WeaponryTemplates[i], MinScore+1, MaxScore, MaxDex, MaxStr, MaxInt);
			if ( !NewWeaponTemplate.IsValid() && (i == 0) && (MinScore == 0) ) //Assure a club if no weapon
				NewWeaponTemplate = Template("It_1H_Club_01");
			if ( NewWeaponTemplate.IsValid() )
			{
				int OldWeaponSlot = EntityNPC.Inventory.FindStackIndex( Slots[i]);
				int NewWeaponSlot = EntityNPC.Inventory.AssureItems( NewWeaponTemplate, gEQuality_Worn, 1);
				if ( NewWeaponSlot != -1 )
				{
					if ( !EntityNPC.Inventory.EquipStackToSlot( NewWeaponSlot, Slots[i]) )
						EntityNPC.Inventory.DeleteStack(NewWeaponSlot);
					else if ( OldWeaponSlot != -1 )
					{
						EntityNPC.Inventory.DeleteStack( OldWeaponSlot);
						EntityNPC.NPC->TimeStampDiseased = CurrentTime;
					}
				}
			}
		}
	}

	EntityNPC.Inventory.MergeStacks();

	return 1;
}


//********************************************************************************************
// FAI_Ranged tells the NPC what action to take based on distance between itself
// and it's target.
//
// Some of the modifications made:
// - Base distance is 1700
// -- Rangers add  +300
// -- Level adds  +10 (per level)
// - May back off to create distance
int G3HookGlobal::FAI_Ranged( gCScriptProcessingUnit& SPU, Entity* InShooter, Entity* InTarget, int)
{
	Entity Shooter = SPU_GetSelf( SPU, InShooter);
	Entity Target  = SPU_GetOther( SPU, InTarget);

	if ( Shooter.NPC.IsValid() && Target.NPC.IsValid() )
	{
		float MaxRange = RangedAttackDistance( Shooter);
		float Distance = Shooter.GetDistanceTo( Target);
		if ( Distance <= MaxRange && Shooter.IsFreeLOS(Target,true) )
		{
			if ( (Distance <= MaxRange * 0.6f) && (Shooter.ScriptRoutine->StateTime < 0.4) && Shooter.CanEvade(Target,gEDirection_Back) )
				return gEAction_Back;
			(*SetAttackReason)( SPU, &Shooter, &Target, Shooter.NPC->AttackReason);
			Shooter.NPC.SetCurrentTarget( Target);
			Shooter.NPC->CombatState = 0;
			return gEAction_Shoot;
		}
	}
	return gEAction_Fwd;
}


// This is here for purely informative purposes
int G3HookGlobal::EquipWeaponry_Hook( gCScriptProcessingUnit& SPU, Entity* E1, Entity* E2, int)
{
	Entity EntityNPC = SPU_GetSelf( SPU, E1);
	Entity EntityTreasure = SPU_GetOther( SPU, E2);

	if ( !EntityTreasure.TreasureSet.IsValid() || EntityTreasure.TreasureSet->TreasureDistribution != gETreasureDistribution_Weaponry )
		return 0;

	EntityTreasure.Inventory.MergeStacks();
	int StackCount = EntityTreasure.Inventory.GetStackCount();
	for ( int Stack=0 ; Stack<StackCount ; Stack++ )
	{
		uint32 Quality = EntityTreasure.Inventory.GetQuality(Stack);
		gEUseType UseType = EntityTreasure.Inventory.GetUseType(Stack);
		int Amount = EntityTreasure.Inventory.GetAmount(Stack);

		if ( UseType != gEUseType_Arrow && UseType != gEUseType_Bolt )
			Quality |= gEQuality_Worn;

		int NewStack = EntityNPC.Inventory.AssureItems( EntityTreasure.Inventory.GetTemplate(Stack), Quality, Amount);
		int NewStack2 = -1;
		int OtherAmount = EntityTreasure.Inventory.GetAmount(Stack);
		if ( OtherAmount > 1 ) //TreasureSet has more than one weapon
			NewStack2 = EntityNPC.Inventory.SplitStack( NewStack, 1);
		if ( UseType == gEUseType_1H )
		{
			EntityNPC.Inventory.EquipStackToSlot( NewStack, gESlot_BackRight);
			EntityNPC.Inventory.EquipStackToSlot( NewStack2, gESlot_BackLeft);
		}
		else
			EntityNPC.Inventory.EquipStack( NewStack);
	}
	EntityNPC.Inventory.MergeStacks();
	return 1;
}

int G3HookGlobal::RefreshWeaponry_Rev( gCScriptProcessingUnit& SPU, Entity* E1, Entity* E2, int)
{
	Entity EntityNPC = SPU_GetSelf( SPU, E1);
	Entity Entity2 = SPU_GetOther( SPU, E2);
	Entity Treasure;

	if ( EntityNPC == Entity::GetPlayer() )
		return 0;

	//Full equip (friends and party used to qualify, but easily exploitable with knockdown)
	if ( !EntityNPC.NPC->DefeatedByPlayer || EntityNPC.ScriptRoutine->AIMode == gEAIMode_Arena
	|| (EntityNPC.NPC->Species != gESpecies_Orc && EntityNPC.NPC->Species != gESpecies_Human)
	|| !UnknownEngineBool() )
	{
		Treasure = EntityNPC.Inventory.GetTreasureSet1(); EquipWeaponry_Hook( SPU, &EntityNPC, &Treasure, 0);
		Treasure = EntityNPC.Inventory.GetTreasureSet2(); EquipWeaponry_Hook( SPU, &EntityNPC, &Treasure, 0);
		Treasure = EntityNPC.Inventory.GetTreasureSet3(); EquipWeaponry_Hook( SPU, &EntityNPC, &Treasure, 0);
		Treasure = EntityNPC.Inventory.GetTreasureSet4(); EquipWeaponry_Hook( SPU, &EntityNPC, &Treasure, 0);
		Treasure = EntityNPC.Inventory.GetTreasureSet5(); EquipWeaponry_Hook( SPU, &EntityNPC, &Treasure, 0);
	}
	else
	{
		if ( (*IsGateGuard)(SPU,&EntityNPC,&None(),0) )
			return 0;
	}

}