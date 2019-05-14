#pragma once


enum gEQuality
{
	gEQuality_Disease  = 0x002,
	gEQuality_Poison   = 0x004,
	gEQuality_Fire     = 0x008,
	gEQuality_Ice      = 0x010,
	gEQuality_Sharp    = 0x020,
	gEQuality_Blessed  = 0x040,
	gEQuality_Forged   = 0x080,
	gEQuality_Worn     = 0x100,
};

enum gEDirection
{
	gEDirection_unk_0,
	gEDirection_unk_1,
	gEDirection_Back,
};

enum gEItemCategory
{
	gEItemCategory_None      = 0,
	gEItemCategory_Weapon    = 1,
	gEItemCategory_Armor     = 2,
	gEItemCategory_Artefact  = 3,
	gEItemCategory_Alchemy   = 4,
	gEItemCategory_Empty_A   = 5,
	gEItemCategory_Misc      = 6,
	gEItemCategory_Written   = 7,
	gEItemCategory_Empty_B   = 8,
	gEItemCategory_Spellbook = 9,
	gEItemCategory_Skill    = 10,
	gEItemCategory_Count    = 11,
};

enum gETreasureDistribution
{
	gETreasureDistribution_Plunder         = 0,
	gETreasureDistribution_Unique          = 1,
	gETreasureDistribution_Trophy          = 2,
	gETreasureDistribution_Weaponry        = 3,
	gETreasureDistribution_Trade_Generate  = 4,
	gETreasureDistribution_Trade_Refresh   = 5,
	gETreasureDistribution_Mining          = 6,
	gETreasureDistribution_Pickpocket      = 7,
	gETreasureDistribution_Trade_NotRandom = 8,
};

enum gEFocusNameType
{
	gEFocusNameType_Skeleton = 0,
	gEFocusNameType_Entity   = 1,
	gEFocusNameType_Bone     = 2,
	gEFocusNameType_Disable  = 3,
};

enum gEFocusPriority
{
	gEFocusPriority_None   = 0,
	gEFocusPriority_Normal = 1,
	gEFocusPriority_High   = 2,
};

enum gETradeCategory
{
	gETradeCategory_None     = 0,
	gETradeCategory_Valuable = 1,
	gETradeCategory_Trophy   = 2,
	gETradeCategory_Empty_A  = 3,
	gETradeCategory_Empty_B  = 4,
};

enum EDifficulty
{
	EDifficulty_Easy   = 0,
	EDifficulty_Medium = 1,
	EDifficulty_Hard   = 2,
};

enum gEProjectilePath
{
	gEProjectilePath_Line,
	gEProjectilePath_Curve,
	gEProjectilePath_Physics,
	gEProjectilePath_Missile,
};

enum gEStackType
{
	gEStackType_Normal,
	gEStackType_Treasure,
	gEStackType_Merchandise,
};

enum gEPhase //WHAT IS THIS?
{
	gEPhase_00,
	gEPhase_01,
	gEPhase_02,
	gEPhase_03,
	gEPhase_04,
	gEPhase_05,
	gEPhase_06,
};

enum eEShapeGroup
{
	eEShapeGroup_Static            =  1,
	eEShapeGroup_Dynamic           =  2,
	eEShapeGroup_Shield            =  3,
	eEShapeGroup_MeleeWeapon       =  4,
	eEShapeGroup_Projectile        =  5,
	eEShapeGroup_Movement          =  6,
	eEShapeGroup_WeaponTrigger     =  7,
	eEShapeGroup_ParadeSphere      =  8,
	eEShapeGroup_Tree_Trunk        =  9,
	eEShapeGroup_Tree_Branches     = 10,
	eEShapeGroup_Camera            = 11,
	eEShapeGroup_Movement_ZoneNPC  = 12,
	eEShapeGroup_HeightRepulsor    = 13,
	eEShapeGroup_Cloth             = 14,
	eEShapeGroup_PhysicalBodyPart  = 15,
	eEShapeGroup_KeyframedBodyPart = 16,
	eEShapeGroup_Camera_Obstacle   = 17,
	eEShapeGroup_Projectile_Level  = 18,
	eEShapeGroup_Trigger           = 19,
	eEShapeGroup_Door              = 20,
};

enum eEShapeMaterial
{
	eEShapeMaterial_None             =  0,
	eEShapeMaterial_Wood             =  1,
	eEShapeMaterial_Metal            =  2,
	eEShapeMaterial_Water            =  3,
	eEShapeMaterial_Stone            =  4,
	eEShapeMaterial_Earth            =  5,
	eEShapeMaterial_Ice              =  6,
	eEShapeMaterial_Leather          =  7,
	eEShapeMaterial_Clay             =  8,
	eEShapeMaterial_Glass            =  9,
	eEShapeMaterial_Flesh            = 10,
	eEShapeMaterial_Snow             = 11,
	eEShapeMaterial_Debris           = 12,
	eEShapeMaterial_Foliage          = 13,
	eEShapeMaterial_Magic            = 14,
	eEShapeMaterial_Grass            = 15,
	eEShapeMaterial_SpringAndDamper1 = 16,
	eEShapeMaterial_SpringAndDamper2 = 17,
	eEShapeMaterial_SpringAndDamper3 = 18,
};

enum gESlot //N: no physical slot
{
	gESlot_None          =  0,
	gESlot_RightHand     =  1,
	gESlot_LeftHand      =  2,
	gESlot_EquipLeftHand =  3, //N
	gESlot_Beard         =  4,
	gESlot_BackLeft      =  5, //MeleeBackLeft
	gESlot_BackRight     =  6, //MeleeBackRight
	gESlot_Bow           =  7,
	gESlot_Crossbow      =  8, //N
	gESlot_Armor         =  9, //N
	gESlot_Belt          = 10, //N
	gESlot_Amulet        = 11, //N
	gESlot_Ring1         = 12, //N
	gESlot_Ring2         = 13, //N
	gESlot_Ammo          = 14, //N
	gESlot_Hair          = 15,
	gESlot_Head          = 16,
	gESlot_Body          = 17,
	gESlot_Helmet        = 18,
};

enum gEUseType
{
	gEUseType_None            =   0,
	gEUseType_Action          =   1,
	gEUseType_1H              =   2,
	gEUseType_2H              =   3,
	gEUseType_Arrow           =   4,
	gEUseType_Bow             =   5,
	gEUseType_CrossBow        =   6,
	gEUseType_Bolt            =   7,
	gEUseType_Fist            =   8,
	gEUseType_Shield          =   9,
	gEUseType_Armor           =  10,
	gEUseType_Helmet          =  11,
	gEUseType_Staff           =  12,
	gEUseType_Amulet          =  13,
	gEUseType_Ring            =  14,
	gEUseType_Cast            =  15,
	gEUseType_Potion          =  16,
	gEUseType_Plant           =  17,
	gEUseType_Meat            =  18,
	gEUseType_Fruit           =  19,
	gEUseType_Bread           =  20,
	gEUseType_Bottle          =  21,
	gEUseType_Cup             =  22,
	gEUseType_Bowl            =  23,
	gEUseType_Torch           =  24,
	gEUseType_Alarmhorn       =  25,
	gEUseType_Broom           =  26,
	gEUseType_Brush           =  27,
	gEUseType_Lute            =  28,
	gEUseType_Rake            =  29,
	gEUseType_TrophyTeeth     =  30,
	gEUseType_Valuable        =  31,
	gEUseType_Smoke           =  32,
	gEUseType_OrcPipe         =  33,
	gEUseType_Scoop           =  34,
	gEUseType_Stick           =  35,
	gEUseType_Shovel          =  36,
	gEUseType_Hammer          =  37,
	gEUseType_Fan             =  38,
	gEUseType_Pan             =  39,
	gEUseType_Saw             =  40,
	gEUseType_TrophySkin      =  41,
	gEUseType_Map             =  42,
	gEUseType_Book            =  43,
	gEUseType_Letter          =  44,
	gEUseType_Key             =  45,
	gEUseType_Lockpick        =  46,
	gEUseType_CarryFront      =  47,
	gEUseType_CarryShoulder   =  48,
	gEUseType_Pickaxe         =  49,
	gEUseType_TrophyFur       =  50,
	gEUseType_Halberd         =  51,
	gEUseType_Axe             =  52,
	gEUseType_ITEM_E          =  53,
	gEUseType_Modify          =  54,
	gEUseType_PhysicalFist    =  55,
	gEUseType_ITEM_H          =  56,
	gEUseType_Anvil           =  57,
	gEUseType_Forge           =  58,
	gEUseType_GrindStone      =  59,
	gEUseType_Cauldron        =  60,
	gEUseType_Barbecue        =  61,
	gEUseType_Alchemy         =  62,
	gEUseType_Bookshelf       =  63,
	gEUseType_BookStand       =  64,
	gEUseType_TakeStone       =  65,
	gEUseType_DropStone       =  66,
	gEUseType_PickOre         =  67,
	gEUseType_PickGround      =  68,
	gEUseType_DigGround       =  69,
	gEUseType_Field           =  70,
	gEUseType_Repair          =  71,
	gEUseType_SawLog          =  72,
	gEUseType_Lumberjack      =  73,
	gEUseType_Bed             =  74,
	gEUseType_SleepGround     =  75,
	gEUseType_CleanFloor      =  76,
	gEUseType_Dance           =  77,
	gEUseType_FanBoss         =  78,
	gEUseType_Boss            =  79,
	gEUseType_Throne          =  80,
	gEUseType_Pace            =  81,
	gEUseType_Bard            =  82,
	gEUseType_Stool           =  83,
	gEUseType_Bench           =  84,
	gEUseType_Waterpipe       =  85,
	gEUseType_WaterBarrel     =  86,
	gEUseType_PirateTreasure  =  87,
	gEUseType_Campfire        =  88,
	gEUseType_SitCampfire     =  89,
	gEUseType_SitGround       =  90,
	gEUseType_Smalltalk       =  91,
	gEUseType_Preach          =  92,
	gEUseType_Spectator       =  93,
	gEUseType_Stand           =  94,
	gEUseType_Guard           =  95,
	gEUseType_Trader          =  96,
	gEUseType_Listener        =  97,
	gEUseType_OrcDance        =  98,
	gEUseType_Stoneplate      =  99,
	gEUseType_OrcDrum         = 100,
	gEUseType_Door            = 101,
	gEUseType_OrcBoulder      = 102,
	gEUseType_EatGround       = 103,
	gEUseType_DrinkWater      = 104,
	gEUseType_Pee             = 105,
	gEUseType_Chest           = 106,
	gEUseType_Shrine          = 107,
	gEUseType_AttackPoint     = 108,
	gEUseType_Roam            = 109,
	gEUseType_BODY_A          = 110,
	gEUseType_Beard           = 111,
	gEUseType_Hair            = 112,
	gEUseType_Head            = 113,
	gEUseType_Body            = 114,
	gEUseType_Flee            = 115,
	gEUseType_Talk            = 116,
};

enum eEPropertySetType
{
	eEPropertySetType_00,
	eEPropertySetType_01,
	eEPropertySetType_02,
	eEPropertySetType_03,
	eEPropertySetType_04,
	eEPropertySetType_05,
	eEPropertySetType_06, //gCDynamicCollisionCircle_PS
	eEPropertySetType_07,
	eEPropertySetType_08,
	eEPropertySetType_09,
	eEPropertySetType_0A,
	eEPropertySetType_0B,
	eEPropertySetType_0C,
	eEPropertySetType_0D,
	eEPropertySetType_0E,
	eEPropertySetType_0F,
	eEPropertySetType_10,
	eEPropertySetType_11,
	eEPropertySetType_12,
	eEPropertySetType_13,
	eEPropertySetType_14,
	eEPropertySetType_15,
	eEPropertySetType_16,
	eEPropertySetType_17,
	eEPropertySetType_18,
	eEPropertySetType_19,
	eEPropertySetType_1A,
	eEPropertySetType_1B,
	eEPropertySetType_1C,
	eEPropertySetType_1D,
	eEPropertySetType_1E,
	eEPropertySetType_1F, //Inventory?
	eEPropertySetType_20,
	eEPropertySetType_21,
	eEPropertySetType_22,
	eEPropertySetType_23,
	eEPropertySetType_24,
	eEPropertySetType_25,
	eEPropertySetType_26,
	eEPropertySetType_27,
	eEPropertySetType_28,
	eEPropertySetType_29,
	eEPropertySetType_2A,
	eEPropertySetType_2B,
	eEPropertySetType_2C,
	eEPropertySetType_2D,
	eEPropertySetType_2E,
	eEPropertySetType_2F,
	eEPropertySetType_Item            = 48,
	eEPropertySetType_Interaction     = 49,
	eEPropertySetType_32,
	eEPropertySetType_Damage          = 51,
	eEPropertySetType_34,
	eEPropertySetType_35,
	eEPropertySetType_36,
	eEPropertySetType_37,
	eEPropertySetType_38,
	eEPropertySetType_39,
	eEPropertySetType_3A,
	eEPropertySetType_3B,
	eEPropertySetType_3C,
	eEPropertySetType_3D,
	eEPropertySetType_3E,
	eEPropertySetType_3F,
};

enum gEDamageType
{
	gEDamageType_None      = 0,
	gEDamageType_Impact    = 1,
	gEDamageType_Blade     = 2,
	gEDamageType_Missile   = 3,
	gEDamageType_Fire      = 4,
	gEDamageType_Ice       = 5,
	gEDamageType_Lightning = 6,
	gEDamageType_Physics   = 7,
};

enum gEPartyMemberType
{
	gEPartyMemberType_None       = 0,
	gEPartyMemberType_Party      = 1,
	gEPartyMemberType_Mob        = 2,
	gEPartyMemberType_Slave      = 3,
	gEPartyMemberType_Controlled = 4,
	gEPartyMemberType_Summoned   = 5
};

enum gEStatusEffects //Names are guesses
{
	gEStatusEffects_Burning      = 0x0001,
	gEStatusEffects_Frozen       = 0x0002,
	gEStatusEffects_Poisoned     = 0x0004,
	gEStatusEffects_Diseased     = 0x0008,
	gEStatusEffects_Transformed  = 0x0010,
	gEStatusEffects_Unknown020   = 0x0020,
	gEStatusEffects_Unknown040   = 0x0040, //Set during teleport
	gEStatusEffects_Unknown080   = 0x0080,
	gEStatusEffects_MagicBarrier = 0x0100,
	gEStatusEffects_Ghost        = 0x0200,
};

enum gEWeaponConfig
{
	gEWeaponConfig_Melee  = 0,
	gEWeaponConfig_Ranged = 1,
	gEWeaponConfig_Magic  = 2
};

enum gEHitDirection
{
	gEHitDirection_Left,
	gEHitDirection_Right,
};

enum gEAniState
{
	gEAniState_Dummy0         = 0,
	gEAniState_Dummy1         = 1,
	gEAniState_Stand0         = 2,
	gEAniState_Sneak          = 3,
	gEAniState_Parade         = 4,
	gEAniState_Kneel          = 5,
	gEAniState_SitGround      = 6,
	gEAniState_SitStool       = 7,
	gEAniState_SitBench       = 8,
	gEAniState_SitThrone      = 9,
	gEAniState_SleepBed       = 10,
	gEAniState_SleepGround    = 11,
	gEAniState_TiltOrcBoulder = 12,
	gEAniState_HoldOrcBoulder = 13,
	gEAniState_LiftOrcBoulder = 14,
	gEAniState_SitKnockDown   = 15,
	gEAniState_LieKnockDown   = 16,
	gEAniState_LieKnockOut    = 17,
	gEAniState_LieStraightDead= 18,
	gEAniState_LieDead        = 19,
	gEAniState_LiePiercedKO   = 20,
	gEAniState_LiePiercedDead = 21,
	gEAniState_TalkStand      = 22,
	gEAniState_TalkSitGround  = 23,
	gEAniState_TalkSitStool   = 24,
	gEAniState_TalkSitBench   = 25,
	gEAniState_TalkSitThrone  = 26,
	gEAniState_Wade           = 27,
	gEAniState_Swim           = 28,
	gEAniState_Dive           = 29,
	gEAniState_Count          = 30,
};

enum gEAmbientAction
{
	gEAmbientAction_Ambient = 0,
	gEAmbientAction_Listen  = 1,
	gEAmbientAction_Count   = 2,
};

enum gEAction
{
	gEAction_None             = 0,
	gEAction_Attack           = 1,
	gEAction_PowerAttack      = 2,
	gEAction_QuickAttack      = 3,
	gEAction_QuickAttackR     = 4,
	gEAction_QuickAttackL     = 5,
	gEAction_SimpleWhirl      = 6,
	gEAction_TurnLeft         = 7,
	gEAction_TurnRight        = 8,
	gEAction_SprintAttack     = 9,
	gEAction_WhirlAttack      = 10,
	gEAction_PierceAttack     = 11,
	gEAction_JumpAttack       = 12,
	gEAction_RamAttack        = 13,
	gEAction_HackAttack       = 14,
	gEAction_FinishingAttack  = 15,
	gEAction_Parade           = 16,
	gEAction_ParadeR          = 17,
	gEAction_ParadeL          = 18,
	gEAction_ExitParade       = 19,
	gEAction_QuickParadeStumble = 20,
	gEAction_ParadeStumble    = 21,
	gEAction_ParadeStumbleR   = 22,
	gEAction_ParadeStumbleL   = 23,
	gEAction_HeavyParadeStumble = 24,
	gEAction_QuickStumble     = 25,
	gEAction_Stumble          = 26,
	gEAction_StumbleR         = 27,
	gEAction_StumbleL         = 28,
	gEAction_SitKnockDown     = 29,
	gEAction_GetUpAttack      = 30,
	gEAction_GetUpParade      = 31,
	gEAction_LieKnockDown     = 32,
	gEAction_LieKnockOut      = 33,
	gEAction_PierceStumble    = 34,
	gEAction_Die              = 35,
	gEAction_LieDead          = 36,
	gEAction_LiePirecedKO     = 37,
	gEAction_LiePiercedDead   = 38,
	gEAction_AbortAttack      = 39,
	gEAction_Aim              = 40,
	gEAction_Shoot            = 41,
	gEAction_Reload           = 42,
	gEAction_Cock             = 43,
	gEAction_Cast             = 44,
	gEAction_PowerCast        = 45,
	gEAction_MagicParade      = 46,
	gEAction_QuickCast        = 47,
	gEAction_Summon           = 48,
	gEAction_Heal             = 49,
	gEAction_Wait             = 50,
	gEAction_JumpBack         = 51,
	gEAction_Fwd              = 52,
	gEAction_Back             = 53,
	gEAction_Left             = 54,
	gEAction_Right            = 55,
	gEAction_Move             = 56,
	gEAction_Jump             = 57,
	gEAction_Evade            = 58,
	gEAction_Slide            = 59,
	gEAction_Fall             = 60,
	gEAction_Dive             = 61,
	gEAction_COMBATACTIONS_END = 62,
	gEAction_Use              = 63,
	gEAction_Equip            = 64,
	gEAction_Reach            = 65,
	gEAction_Take             = 66,
	gEAction_Drop             = 67,
	gEAction_Hold             = 68,
	gEAction_HoldLeft         = 69,
	gEAction_HoldRight        = 70,
	gEAction_Transfer         = 71,
	gEAction_FlameSword       = 72,
	gEAction_Fry              = 73,
	gEAction_Eat              = 74,
	gEAction_Drink            = 75,
	gEAction_Stand            = 76,
	gEAction_Sneak            = 77,
	gEAction_Kneel            = 78,
	gEAction_SitGround        = 79,
	gEAction_SitStool         = 80,
	gEAction_SitBench         = 81,
	gEAction_SitThrone        = 82,
	gEAction_SleepBed         = 83,
	gEAction_SleepGround      = 84,
	gEAction_OrcDrum          = 85,
	gEAction_Waterpipe        = 86,
	gEAction_Anvil            = 87,
	gEAction_OrcAnvil         = 88,
	gEAction_Forge            = 89,
	gEAction_CoolWeapon       = 90,
	gEAction_DrinkWaterBarrel = 91,
	gEAction_GrindStone       = 92,
	gEAction_Cauldron         = 93,
	gEAction_Barbecue         = 94,
	gEAction_Alchemy          = 95,
	gEAction_Bookstand        = 96,
	gEAction_Stoneplate       = 97,
	gEAction_PickOre          = 98,
	gEAction_OpenChest        = 99,
	gEAction_Lockpick         = 100,
	gEAction_OpenDoor         = 101,
	gEAction_ExitInteract     = 102,
	gEAction_PickGround       = 103,
	gEAction_DigGround        = 104,
	gEAction_Repair           = 105,
	gEAction_SawLog           = 106,
	gEAction_Lumberjack       = 107,
	gEAction_RakeField        = 108,
	gEAction_CleanFloor       = 109,
	gEAction_TiltOrcBoulder   = 110,
	gEAction_HoldOrcBoulder   = 111,
	gEAction_LiftOrcBoulder   = 112,
	gEAction_Fan              = 113,
	gEAction_Dance            = 114,
	gEAction_OrcDance         = 115,
	gEAction_FieldWork        = 116,
	gEAction_EatGround        = 117,
	gEAction_DrinkWater       = 118,
	gEAction_ArmsCrossed      = 119,
	gEAction_HandsOnHips      = 120,
	gEAction_Warn             = 121,
	gEAction_Ambient          = 122,
	gEAction_Think            = 123,
	gEAction_Pee              = 124,
	gEAction_Say              = 125,
	gEAction_Listen           = 126,
	gEAction_WatchFight       = 127,
	gEAction_Cheer            = 128,
	gEAction_SuperCheer       = 129,
	gEAction_Applaud          = 130,
	gEAction_QuickUse0        = 131,
	gEAction_QuickUse1        = 132,
	gEAction_QuickUse2        = 133,
	gEAction_QuickUse3        = 134,
	gEAction_QuickUse4        = 135,
	gEAction_QuickUse5        = 136,
	gEAction_QuickUse6        = 137,
	gEAction_QuickUse7        = 138,
	gEAction_QuickUse8        = 139,
	gEAction_QuickUse9        = 140,
	gEAction_QuickUseH        = 141,
	gEAction_QuickUseM        = 142,
	gEAction_QuickUseS        = 143,
	gEAction_Count            = 144,
};


enum gEAIMode //2 and 7 unknown
{
	gEAIMode_Routine     = 0,
	gEAIMode_Reaction    = 1,
	gEAIMode_Combat      = 3,
	gEAIMode_Flee        = 4,
	gEAIMode_Arena       = 5,
	gEAIMode_Talk        = 6,
	gEAIMode_Down        = 8,
	gEAIMode_Dead        = 9,
	gEAIMode_Abandoned   = 10,
	gEAIMode_PlayerParty = 11
};

enum gEBearing
{
	gEBearing_None   = 0,
	gEBearing_Babe   = 1,
	gEBearing_Zombie = 2
};

enum gEClass
{
	gEClass_None     = 0,
	gEClass_Mage     = 1,
	gEClass_Paladin  = 2,
	gEClass_Warrior  = 3,
	gEClass_Ranger   = 4,
	gEClass_EMPTY_A  = 5,
	gEClass_EMPTY_B  = 6,
	gEClass_EMPTY_C  = 7,
	gEClass_EMPTY_D  = 8,
	gEClass_EMPTY_E  = 9,
	gEClass_EMPTY_F  = 10,
	gEClass_EMPTY_G  = 11,
};

enum gEGender
{
	gEGender_Male   = 0,
	gEGender_Female = 1
};

enum gEGuardStatus
{
	gEGuardStatus_Active = 0,
	gEGuardStatus_FirstWarnGiven = 1,
	gEGuardStatus_SecondWarnGiven = 2,
	gEGuardStatus_Inactive = 3,
	gEGuardStatus_Behind = 4
};

enum gELastFightAgainstPlayer
{
	gELastFightAgainstPlayer_None     = 0,
	gELastFightAgainstPlayer_Lost     = 1,
	gELastFightAgainstPlayer_Won      = 2,
	gELastFightAgainstPlayer_Cancel   = 3,
	gELastFightAgainstPlayer_Running  = 4,
	gELastFightAgainstPlayer_Friendly = 5
};

enum gENPCType
{
	gENPCType_Personal  = 0,
	gENPCType_Enclave   = 1,
	gENPCType_Political = 2,
	gENPCType_Friend    = 3
};

enum gEPlayerCrime
{
	gEPlayerCrime_None      = 0,
	gEPlayerCrime_Livestock = 1,
	gEPlayerCrime_Attack    = 2,
	gEPlayerCrime_Theft     = 3,
	gEPlayerCrime_Murder    = 4,
	gEPlayerCrime_Count     = 5
};

enum gEAttackReason
{
	gEAttackReason_None           = 0,
	gEAttackReason_LeaveZone      = 1,
	gEAttackReason_Livestock      = 2,
	gEAttackReason_StopThief      = 3,
	gEAttackReason_Theft          = 4,
	gEAttackReason_UseInteractObject = 5,
	gEAttackReason_ReactToWeapon  = 6,
	gEAttackReason_Angry          = 7,
	gEAttackReason_StopFight      = 8,
	gEAttackReason_ReactToDamage  = 9,
	gEAttackReason_GateGuard      = 10,
	gEAttackReason_Intruder       = 11,
	gEAttackReason_Enemy          = 12,
	gEAttackReason_Murder         = 13,
	gEAttackReason_Prey           = 14,
	gEAttackReason_DriveAway      = 15,
	gEAttackReason_PlayerCommand  = 16,
	gEAttackReason_Duel           = 17,
	gEAttackReason_Arena          = 18,
	gEAttackReason_Revolution     = 19,
	gEAttackReason_Kill           = 20
};

enum gEAttitude
{
	gEAttitude_None     = 0,
	gEAttitude_Friendly = 1,
	gEAttitude_Neutral  = 2,
	gEAttitude_Angry    = 3,
	gEAttitude_Hostile  = 4,
	gEAttitude_Predator = 5,
	gEAttitude_Panic    = 6
};

enum gESpecies
{
	gESpecies_Human            = 0,
	gESpecies_Skeleton         = 1,
	gESpecies_Zombie           = 2,
	gESpecies_Golem            = 3,
	gESpecies_Demon            = 4,
	gESpecies_Orc              = 5,
	gESpecies_Goblin           = 6,
	gESpecies_Troll            = 7,
	gESpecies_Minecrawler      = 8,
	gESpecies_Scavenger        = 9,
	gESpecies_Wolf             = 10,
	gESpecies_Boar             = 11,
	gESpecies_Sabertooth       = 12,
	gESpecies_Shadowbeast      = 13,
	gESpecies_Bison            = 14,
	gESpecies_Rhino            = 15,
	gESpecies_Ripper           = 16,
	gESpecies_Lurker           = 17,
	gESpecies_Varan            = 18,
	gESpecies_Snapper          = 19,
	gESpecies_Alligator        = 20,
	gESpecies_Trex             = 21,
	gESpecies_FireVaran        = 22,
	gESpecies_Bloodfly         = 23,
	gESpecies_Lizard           = 24,
	gESpecies_Fish             = 25,
	gESpecies_Meatbug          = 26,
	gESpecies_Vulture          = 27,
	gESpecies_Rabbit           = 28,
	gESpecies_Deer             = 29,
	gESpecies_Chicken          = 30,
	gESpecies_Molerat          = 31,
	gESpecies_Snake            = 32,
	gESpecies_Pig              = 33,
	gESpecies_Cow              = 34,
	gESpecies_Spider           = 35,
	gESpecies_Turtle           = 36,
	gESpecies_Bird             = 37,
	gESpecies_Gargoyle         = 38,
	gESpecies_SwampLurker      = 39,
	gESpecies_EMPTY_B          = 40,
	gESpecies_Ogre             = 41,
	gESpecies_Ray              = 42,
	gESpecies_Scorpion         = 43,
	gESpecies_Seagull          = 44,
	gESpecies_Walrus           = 45,
	gESpecies_Whale            = 46,
	gESpecies_Eagle            = 47,
	gESpecies_FireGolem        = 48,
	gESpecies_IceGolem         = 49,
	gESpecies_ScorpionKing     = 50,
	gESpecies_Stalker          = 51,
	gESpecies_Dragon           = 52
};

enum gEPoliticalAlignment
{
	gEPoliticalAlignment_None    = 0,
	gEPoliticalAlignment_Orc     = 1,
	gEPoliticalAlignment_Nrd     = 2,
	gEPoliticalAlignment_Reb     = 3,
	gEPoliticalAlignment_Mid     = 4,
	gEPoliticalAlignment_Ass     = 5,
	gEPoliticalAlignment_Nom     = 6,
	gEPoliticalAlignment_Out     = 7,
	gEPoliticalAlignment_Slave   = 8,
	gEPoliticalAlignment_Pirate  = 9,
};

enum eECollisionGroup
{
	eECollisionGroup_Static        = 1,
	eECollisionGroup_Dynamic       = 2,
	eECollisionGroup_Player        = 3,
	eECollisionGroup_NPC           = 4,
	eECollisionGroup_Item_Equipped = 5,
	eECollisionGroup_Item_World    = 6,
	eECollisionGroup_Item_Attack   = 7,
	eECollisionGroup_Interactable  = 8,
	eECollisionGroup_Trigger       = 9,
	eECollisionGroup_Zone          = 10,
	eECollisionGroup_Camera        = 11,
	eECollisionGroup_Tree          = 12,
	eECollisionGroup_DownCharacter = 13,
	eECollisionGroup_PlayerTrigger = 14,
	eECollisionGroup_ObjectTrigger = 15,
	eECollisionGroup_Ghost         = 16,
	eECollisionGroup_Mover         = 17,
	eECollisionGroup_RagDoll       = 18,
};

enum eEPhysicRangeType
{
	eEPhysicRangeType_World,
	eEPhysicRangeType_ProcessingRange,
	eEPhysicRangeType_VisibilityRange
};

enum EAttribReqOperation
{
	EOP_ValGreaterEqual,
	EOP_MaxGreaterEqual,
};

enum EAttrib___Operation
{
	EOP_AddToVal,
	EOP_AddToMax,
	EOP_AddPercentageToVal,
	EOP_AddPercentageToMax,
	EOP_SetVal,
	EOP_SetMax,
	EOP_SetValToPercentage,
	EOP_SetMaxToPercentage,
	EOP_SetValToMax,
};