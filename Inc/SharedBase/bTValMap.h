#pragma once

#include "bTValArray.h"

template <typename TK, typename TV> class bTValMap
{
public:
	struct bSNode
	{
		TK Key;
		TV Value;
		bSNode* Next;
	};

	bTValArray<bSNode*> NodeList;
	uint32 NodeCount;

	// No constructor/destructor yet
};
