#pragma once

#include "PropertySetContainer.h"

#include "Game/gCPlayerMemory_PS.h"

class G3API PSPlayerMemory
{
	PS_BASE(PSPlayerMemory,gCPlayerMemory_PS)

	void SetHitPoints( int Set);
	void SetHitPointsMax( int Set);
	void AddHitPointsMax( int Add);
	int GetManaPoints() const;
	int GetManaPointsMax() const;
	int GetMaximum( const bCString&) const;
};
