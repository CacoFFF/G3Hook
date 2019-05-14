#pragma once

#include "SharedBase/bCPropertyId.h"
#include "SharedBase/bCString.h"
#include "SharedBase/bEResult.h"

class eCEntity;


//SUPER IS eCWrapper (?)
class G3API eCEntityProxy //Size: 28 bytes
{
public:
	int unk_04; //Constructed as zero
	bCPropertyID Property_08; //Find real name, destroyed in constructor

	eCEntityProxy();
	eCEntityProxy( eCEntity*);

	eCEntity* GetEntity();
	const eCEntity* GetEntity() const;

	virtual eCEntity* ResolveEntity();		// 00
	virtual unsigned short GetVersion()		// 04
	{
		return 1;
	}
	virtual bCString GetAddress() const;		// 08
	virtual bEResult Read( bCIStream&);		// 0C
	virtual bEResult Write( bCOStream&);		// 10
	virtual bEResult CopyFrom( const eCEntityProxy&);		// 14
	virtual bool Compare( const eCEntityProxy*);		// 18
	virtual int Unknown_1( char);		// 1C
	// There may be 4 or 5 more functions in the vftable
};

//int Test3 = sizeof(eCEntityProxy);