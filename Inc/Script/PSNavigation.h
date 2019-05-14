#pragma once

#include "Game/gCNavigation_PS.h"

class G3API PSNavigation
{
public:
	PS_BASE(PSNavigation,gCNavigation_PS)

	Entity GetAIGotoDestination() const;
	gEDirection GetAniDirection() const;
	Entity GetCurrentDestinationPoint() const;
	Entity GetCurrentZone() const;
	bool GetDCCEnabled() const;
	float GetDCCRadius() const;
	gEGotoStatus GetGotoStatus() const;
	Entity GetLastZone() const;
	Entity GetRelaxingPoint() const;
	Entity GetSleepingPoint() const;
	Entity GetWorkingPoint() const;
	bool HasAnyDestination() const;
	bool IsInProcessingRange() const;
	bool IsTravelling() const;
	void Reset() const;
	void ResetAll() const;
	bool SetCurrentDestinationPoint( Entity&);
	void SetDCCEnabled( bool bEnable);
	void SetDCCRadius( float NewRadius);
	bool SetRelaxingPoint( Entity&);
	bool SetRoutine( const bCString&);
	bool SetSleepingPoint( Entity&);
	bool SetWorkingPoint( Entity&);
	bool StartGoto( Entity&, Entity&, gEWalkMode);
	bool StartGoto( Entity&, const bCVector&, gEWalkMode);
};