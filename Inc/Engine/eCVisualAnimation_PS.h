#pragma once

class G3ENGINEAPI eCVisualAnimation_PS : public eCEntityPropertySet
{
public:
	bCString ResourceFilePath; //bCAnimationResourceString
	bCString FacialAnimPath;   //bCAnimationResourceString
	PS_EPROPERTY(PhysicsControlled,bool);
	PS_EPROPERTY(ConstrainRootToWorld,bool);
	PS_EPROPERTY(InterBoneCollision,bool);
	PS_EPROPERTY(SkeletonCollisionEnabled,bool);
	PS_EPROPERTY(BoneRaycastsEnabled,bool);
	PS_EPROPERTY(BonesAreBreakable,bool);
	PS_EPROPERTY(BonesBreakMaxForce,float);
	PS_EPROPERTY(BonesBreakMaxTorque,float);
	PS_EPROPERTY(BoneLinearDamping,float);
	PS_EPROPERTY(BoneAngularDamping,float);
	PS_EPROPERTY(BoneTwistSpringEnabled,bool);
	PS_EPROPERTY(BoneTwistSpring,float);
	PS_EPROPERTY(BoneTwistSpringDamping,float);
	PS_EPROPERTY(BoneSwingSpringEnabled,bool);
	PS_EPROPERTY(BoneSwingSpring,float);
	PS_EPROPERTY(BoneSwingSpringDamping,float);
	PS_EPROPERTY(BoneJointSpringEnabled,bool);
	PS_EPROPERTY(BoneJointSpring,float);
	PS_EPROPERTY(BoneJointSpringDamping,float);
	PS_EPROPERTY(BoneProjectionDistance,float);
	PS_EPROPERTY(BoneShapeGroup,bTPropertyContainer<eEShapeGroup>);
	PS_EPROPERTY(BoneShapeMaterial,bTPropertyContainer<eEShapeMaterial>);
	PS_EPROPERTY(SkeletonShapeGroup,bTPropertyContainer<eECollisionGroup>);
	PS_EPROPERTY(SpringParentNodesOnly,bool);
	PS_EPROPERTY(SpringParentNodesScale,float);
	PS_EPROPERTY(CreateSpringMassCloth,bool);
	PS_EPROPERTY(DisablePhysicLodding,bool);
	//bTPropertyObject<eCSpringAndDamperEffector,eCEffector> ClothEffector; // 0x80
	//int MaterialSwitch; // 0x90
	//uint32 NumAttachments; // 0xC8 //prossibly a member of a TValArray
	

};

//int TestVA = sizeof(eCVisualAnimation_PS);