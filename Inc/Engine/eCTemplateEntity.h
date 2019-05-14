#pragma once

//Superclass
#include "eCEntity.h"

class eCTemplateEntity : public eCEntity
{
public:

	bool IsDeleted() const;

	//bCObjectBase interface
	uint16 GetVersion() const;
};


inline uint16 eCTemplateEntity::GetVersion() const
{
	return 62; //Gothic 3 1.75
}
