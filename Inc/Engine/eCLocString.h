#pragma once

#include "SharedBase/bCUnicodeString.h"

class G3ENGINEAPI eCLocString
{
public:
	int unk_00;
	int pad[3]; //Extra size in stack just in case

	eCLocString( const bCString&);

	const bCUnicodeString GetString() const;
};
