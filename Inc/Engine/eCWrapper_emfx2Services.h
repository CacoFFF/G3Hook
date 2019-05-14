#pragma once

#include "bCObjectBase.h"

class G3API eCWrapper_emfx2Services : public bCObjectBase
{
public:

	//bCObjectBase interface
	void Destroy()
	{
	}

	bEResult Create()
	{
		Destroy();
		return bEResult_OK;
	}
};
