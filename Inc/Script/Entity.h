#pragma once

class Entity;
class eCEntity;

// Commons for all the property sets
#include "G3Enums.h"
#include "Engine/eCEntityPropertySet.h"
#include "PropertySetContainer.h"

#include "SharedBase/bCUnicodeString.h"

#include "PSInventory.h"
#include "PSPlayerMemory.h"
#include "PSNPC.h"
#include "PSRoutine.h"
#include "PSNavigation.h"
#include "PSParty.h"
#include "PSDamageReceiver.h"
#include "PSAnimation.h"
#include "PSFocus.h"
#include "PSDamage.h"
#include "PSDialog.h"
#include "PSInteraction.h"
#include "PSItem.h"
#include "PSTreasureSet.h"

//Move to property set container!
#include "Game/gCDynamicCollisionCircle_PS.h"


//Entity has no vftable
//Constructs to zero
class G3SCRIPTAPI Entity
{
public:
	eCEntity* Instance;
	PSRoutine        ScriptRoutine;  // 0x04
	PSAnimation      VisualAnimation;// 0x08
	int unk_0C;
	int unk_10; //PSClock?
	int unk_14; 
	PSFocus          Focus;          // 0x18
	PSInteraction    Interaction;    // 0x1C
	int unk_20; //InfoManager (?)
	PSInventory      Inventory;      // 0x24
	PSItem           Item;           // 0x28
	int unk_2C;
	PSNavigation     Navigation;     // 0x30
	PSNpc            NPC;            // 0x34
	PSPlayerMemory   PlayerMemory;   // 0x38
	int unk_3C; //Secondary PSInventory???
	int unk_40;
	int unk_44; //CharacterMovement
	PSDamage         Damage;         // 0x48
	PSDamageReceiver DamageReceiver; // 0x4C
	int unk_50;
	PSDialog         Dialog;         // 0x54
	PSParty          Party;          // 0x58
	int unk_5C;
	int unk_60;
	int unk_64;
	int unk_68;
	int unk_6C;
	int unk_70; //PSProjectile
	int unk_74;
	int unk_78;
	int unk_7C;
	int unk_80;
	int unk_84;
	int unk_88;
	int unk_8C; //gCAIZone_PS >>> 0x18:Type, 0x20:SecurityLevel
	int unk_90; //PSEffect
	int unk_94;
	int unk_98;
	int unk_9C;
	int unk_A0;
	PSTreasureSet    TreasureSet;    // 0xA4

	Entity();
	Entity( const eCEntity*);
	Entity( const Entity& Other);

	bool AttachTo( eCEntity*);

	bool IsInteractObject() const                   { return Interaction.PS != 0; }
	bool IsItem() const                             { return Item.PS != 0; }
	bool IsCharacter() const                        { return Navigation.PS != 0; }
	bool IsNPC() const                              { return Navigation.PS && !unk_40; }
	bool IsPlayer() const;
	Template GetTemplate() const;
	Entity GetOwner() const; //1C
	Entity GetUser() const; //1C
	Entity GetEnclave() const; 
	void SetEnclave( const Entity&);

	bool operator==( const Entity& Other) const 
	{
		return Instance == Other.Instance;
	}

	bool operator!=( const Entity& Other) const 
	{
		return Instance != Other.Instance;
	}
		

	void MoveTo( const Entity& TargetEntity);
	void MoveTo( const bCMatrix& TargetPos);

	bool Teleport( const Entity& TargetEntity);
	bool Teleport( const bCString& TargetName);
	bCString GetName() const;
	bCString GetDisplayName() const;

	static Entity GetPlayer();
	static Entity GetWorldEntity();
	static bTObjArray<Entity> GetNPCs();
	static bool IsCheatGodEnabled();
	static bool IsCheatInvisibleEnabled();
	static bool IsTestModeEnabled();
	static bool HasCopyCheckFailed();
	static EDifficulty GetCurrentDifficulty();
	static bool IsAlternateCameraEnabled();

	void EnablePicking( bool);
	void EnableCollision( bool);
	void EnableCollision( enum eEShapeGroup, bool, int);
	void EnableCollisionWith( const Entity&, bool);
	void SetCollisionGroup( eECollisionGroup);
	eECollisionGroup GetCollisionGroup() const;

	Entity GetWeapon( bool) const; //TODO: FIGURE OUT PARAMETER

	void EnableRendering( bool);
	void SetAlpha( float);
	void EnableProcessing( bool);
	bool IsInFOV( const Entity&) const;
	bool IsFreeLOS( const Entity&, bool) const;
	bool IsFreeLOSKneeHeight( const Entity&) const;

	bool HasInfo( const Entity&) const;
	bool HasImportantInfo( const Entity&) const;
	bool HasCommentInfo( const Entity&) const;
	bool StartComment( const Entity&) const;

	bool IsDead() const; //Checks for ScriptRoutine->AIMode = 9
	bool IsDown() const; //checks for 8
	bool IsReady() const; //checks for other than 8 or 9
	bool IsSneaking() const; //Always false!!
	bool IsStanding() const; //Redirects to CharacterMovement.IsStanding (if exists)
	bool IsFalling() const; //Same with all below
	bool IsSwimming() const;
	bool IsDiving() const;
	bool IsRunning() const;
	bool IsSprinting() const;
	bool IsJumping() const;
	bool IsBraking() const;
	bool IsInMovingState() const;
	gECharMovementMode GetMovementMode() const;
	void SetMovementMode( gECharMovementMode);

	bool CanEvade( const Entity& Other, gEDirection Direction) const;
	bool CanGoto( Entity const &) const;
	bool CanGoto( bCVector const &) const;
	bool StartGoto( Entity&, enum gEWalkMode);
	bool StartGoto( const bCVector&, enum gEWalkMode);
	void StopGoto();
	void SetLookAtTarget( const Entity&);
	bCVector GetNearestNavigationPoint( bCVector, float);
	gEZoneType GetAIZoneType(void) const;
	void SetAIZoneType( gEZoneType);
	enum gESecurityLevel GetAIZoneSecurityLevel() const;
	void SetAIZoneSecurityLevel(enum gESecurityLevel);
	Entity GetAIZoneOwner() const;
	void SetAIZoneOwner( Entity&);

	static int GetRandomNumber( int);
	static void SetWorldTime( float);
	static float GetWorldTime(); //Hour of the day
	static void SetPlayingTime( float);
	static float GetPlayingTime();
	static uint32 GetTimeStampInSeconds(); //Game timestamp (game progresses at speed of 12 seconds/s)

	bool FindSpawnPose( bCMatrix&, const Entity&, bool, unsigned short) const; //TODO: Figure out parameters 

	void Kill();
	void Decay();
	void StartTakeOver();
	void EndTakeOver();
	void StartTransform( Entity&, float, bool);
	void EndTransform();

	bCVector GetVelocity() const;
	float GetDistanceTo( const Entity&) const;

	void StartPlayAni( bCString, int, bool, float Speed, bool);
};



inline Entity::Entity()
{
	memzero_dwords( this, sizeof(Entity)/sizeof(uint32) );
}
