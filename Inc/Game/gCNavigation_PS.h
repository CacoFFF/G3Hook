#pragma once

class gCDynamicCollisionCircle_PS;

class G3GAMEAPI gCNavigation_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(StartPosition,bCVector);              // 0x14
	PS_EPROPERTY(WorkingPoint,bCPropertyID);           // 0x20
	PS_EPROPERTY(RelaxingPoint,bCPropertyID);          // 0x34
	PS_EPROPERTY(SleepingPoint,bCPropertyID);          // 0x48
	PS_EPROPERTY(Routine,bCString);                    // 0x5C
	PS_EPROPERTY(WorkingPoints,bTValArray<bCPropertyID>); // 0x60
	PS_EPROPERTY(RelaxingPoints,bTValArray<bCPropertyID>); // 0x6C
	PS_EPROPERTY(SleepingPoints,bTValArray<bCPropertyID>); // 0x78
	PS_EPROPERTY(RoutineNames,bTObjArray<bCString>);   // 0x84
	PS_EPROPERTY(CurrentDestinationPointProxy,eCEntityProxy); // 0x90
	PS_EPROPERTY(CurrentZoneEntityProxy,eCEntityProxy); // 0xAC
	PS_EPROPERTY(LastZoneEntityProxy,eCEntityProxy);   // 0xC8
	PS_EPROPERTY(LastUseableNavigationPosition,bCVector); // 0xE4
	PS_EPROPERTY(LastUseableNavigationZoneID,bCPropertyID); // 0xF0
	PS_EPROPERTY(LastUseableNavigationZoneIsPath,bool); // 0x104
	PS_EPROPERTY(IsOnDestinationTimeStamp,uint32);    // 0x108
	PS_EPROPERTY(Destination,bTValArray<bCMotion>);   // 0x10C
	PS_EPROPERTY(Evade,bTValArray<bCVector>);         // 0x118
	PS_EPROPERTY(LastObstacleID,bCPropertyID);        // 0x124
	PS_EPROPERTY(Next,bTValArray<bCMotion>);          // 0x138
	PS_EPROPERTY(Passed,bTValArray<bCVector>);        // 0x144
	PS_EPROPERTY(WishedTargetEntityProxy,eCEntityProxy); // 0x150
	PS_EPROPERTY(ReachedTargetEntityProxy,eCEntityProxy); // 0x16C
	PS_EPROPERTY(CurrentAniDirection,gEAnimDirection); // 0x188
	PS_EPROPERTY(UnderWaterDepth,float);              // 0x18C
	PS_EPROPERTY(CurrentDestination,bTValArray<bCVector>); // 0x190
	PS_EPROPERTY(CurrentDestinationID,bTValArray<bCPropertyID>); // 0x19C
	PS_EPROPERTY(CurrentNavPath,bTValArray<gCNavPath_PS*>); // 0x1A8
	int unk_1B4;
	int unk_1B8;
	int unk_1BC;
	PS_EPROPERTY(CurrentInterPose,bTValArray<bCMotion>); // 0x1C0
	int LastNegZoneStake;                      // 0x1CC
	bool OnTheWay;                             // 0x1D0
	bool FinalTargetDetected;                  // 0x1D1
	int unk_1D4; //PreferredPathPSObject
	gCNavPath_PS* NavigationPath;              // 0x1D8
	gCDynamicCollisionCircle_PS* DCC;          // 0x1DC
	gCCharacterMovement_PS* CharacterMovement; // 0x1E0
	bool unk_1E4;
	bool InProcessingRange; // 0x1E5
	bool FloorDetectionFailed;  // 0x1E6
	int unk_1E8;
	int unk_1EC;
	int unk_1F0;
	int unk_1F4;
	int unk_1F8;
	int unk_1FC;
	int unk_200;
	int unk_204;
	bool unk_208;
	bool GoalReached;                      // 0x209
	gEDirection NextAniDirection;          // 0x20C
	bool unk_210;
	bool NewInterPose;                     // 0x211
	eCEntity* InteractObject;              // 0x214
	gECharMovementMode WishedMovementMode; // 0x218
	gEGotoStatus GotoStatus;               // 0x218;
	int unk_21C;
	bool HasFinalTarget;                   // 0x220
	//gSObstacleEvadeSwitch ObstacleEvadeSwitch // 0x224
	//gSObstacleEvadeSwitch NPCEvadeSwitch // 0x23C
	//bool Enabled; //0x254
	//bool KiledByDeadlock; //0x255
	//bool at 2BC


	gCCharacterMovement_PS* GetCharacterMovement(); //Important accessor
};
