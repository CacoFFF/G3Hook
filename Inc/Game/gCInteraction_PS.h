#pragma once

class G3GAMEAPI gCInteraction_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(FocusPriority,bTPropertyContainer<gEFocusPriority>);
	PS_EPROPERTY(Owner,eCEntityProxy);
	PS_EPROPERTY(User,eCEntityProxy);
	PS_EPROPERTY(UseType,bTPropertyContainer<gEUseType>);
	PS_EPROPERTY(UseFunc,bCString);
	PS_EPROPERTY(AnchorPoint,eCEntityProxy);
	PS_EPROPERTY(FocusNameType,bTPropertyContainer<gEFocusNameType>);
	PS_EPROPERTY(FocusNameBone,bCString);
	PS_EPROPERTY(FocusViewOffset,bCVector);
	PS_EPROPERTY(FocusWorldOffset,bCVector);
	PS_EPROPERTY(UsedByPlayer,bool);
	PS_EPROPERTY(EnterROIScript,bCString);
	PS_EPROPERTY(ExitROIScript,bCString);
	PS_EPROPERTY(Spell,eCTemplateEntityProxy);
	//eCPropertySetProxy at 0xB8
	//bool at 0xDC >>> set to 0 by Invalidate() >>> which is called by Destroy()
};
