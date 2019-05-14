#pragma once

#include "Engine/eCEntityProxy.h"

class gCNPC_PS : public eCEntityPropertySet
{
public:
	bCString Description;
	bCString Voice;
	bCString RoleDescription;
	PS_EPROPERTY(Level,uint32);
	PS_EPROPERTY(LevelMax,uint32);
	PS_EPROPERTY(Gender,bTPropertyContainer<gEGender>);
	PS_EPROPERTY(Species,bTPropertyContainer<gESpecies>);
	PS_EPROPERTY(PoliticalAlignment,bTPropertyContainer<gEPoliticalAlignment>);
	PS_EPROPERTY(Class,bTPropertyContainer<gEClass>);
	PS_EPROPERTY(Type,bTPropertyContainer<gENPCType>);
	bCPropertyID Enclave;
	PS_EPROPERTY(AttitudeToPlayer2,bTPropertyContainer<gEAttitude>);
	PS_EPROPERTY(LastPlayerCrime,bTPropertyContainer<gEPlayerCrime>);
	PS_EPROPERTY(AttackReason,bTPropertyContainer<gEAttackReason>);
	PS_EPROPERTY(LastPlayerAR,bTPropertyContainer<gEAttackReason>);
	PS_EPROPERTY(LastFightAgainstPlayer,bTPropertyContainer<gELastFightAgainstPlayer>);
	unsigned long LastFightTimeStamp;
	unsigned long LastHitTimeStamp;
	unsigned long LastCastTimeStamp;
	bool Immortal;
	float LastDistToTarget;
	float DistToNearestMist;
	bool DefeatedByPlayer;
	bool Ransacked;
	bool Discovered;
	bool LastFightComment;
	eCEntityProxy CurrentTargetEntity;
	eCEntityProxy CurrentAttackerEntity;
	eCEntityProxy AlternativeTargetEntity;
	eCEntityProxy LastAttackerEntity;
	unsigned long CombatState;
	eCEntityProxy GuardPoint;
	int unk_138;
	gEGuardStatus GuardStatus;
	float LastDistToGuardPoint;
	int unk_144;
	gEBearing Bearing;
	bTObjArray<bCString> TeachAttribs;
	bTObjArray<eCTemplateEntityProxy> TeachSkills;
	int ManaUsed;
	eCEntityProxy SpellTarget;
	bCString LastSpell;
	unsigned long StatusEffects; //Bitfield
	uint32 TimeStampFrozen;
	uint32 TimeStampBurning;
	uint32 TimeStampPoisoned;
	uint32 TimeStampDiseased;
	uint32 TimeStampTransformed;
	int unk_1A0;
	int unk_1A4;
	int unk_1A8;
	bCString unk_1AC;
	int unk_1B0; //Zero'd on destruction
	eCEntityProxy unk_1B4;
	eCEntityProxy unk_1D0;
	eCEntityProxy unk_1EC;

	// eCEntityPropertySet interface
	bool NotifyPropertyValueChangedExitEx( const char*, bool);		// 5C - called after changing property
	bEResult ReadSaveGame( bCIStream& Stream);
	bEResult WriteSaveGame( bCOStream& Stream);
	bool IsProcessable() const                   { return true; }		// 84
	bool SupportsRenderDebugOutput() const       { return true; }		// 94
	eEPSSaveGameRelevance GetSaveGameRelevance() const { return eEPSSaveGameRelevance_2; }	// 108
	void OnPostRead();		// 10C - easy to rev

	// gCNPS_PS (?) interface
	// LAST FUNCTION IN VTABLE NEEDS TO BE RESOLVED!
};

//int Test = sizeof(gCNPC_PS);