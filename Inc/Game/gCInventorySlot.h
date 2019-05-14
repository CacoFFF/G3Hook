#pragma once

//Superclass
#include "SharedBase/bCObjectRefBase.h"

#include "Engine/eCTemplateEntityProxy.h"
#include "Engine/eCEntityProxy.h"

class G3GAMEAPI gCInventorySlot : public bCObjectRefBase
{
public:
	PS_EPROPERTY(Template,eCTemplateEntityProxy);
	PS_EPROPERTY(Item,eCEntityProxy);
	PS_EPROPERTY(Slot,bTPropertyContainer<gESlot>);


	gEUseType GetUseType() const;
};
