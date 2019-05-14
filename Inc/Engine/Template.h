#pragma once

#include "SharedBase/bCPropertyID.h"

//MOVE TO SCRIPT!!!!!!
class G3API Template : public bCPropertyID
{
public:
	Template();
	Template( const char*);
	Template( const bCPropertyID&);
	~Template();

	void Create( const char *);

	bool operator==( const bCPropertyID&) const;

	Template& operator=( const char*);
	Template& operator=( const bCPropertyID&);
};
