#pragma once


#include "bCMemoryAdmin.h"
#include "bEResult.h"

class G3SHAREDAPI bCObjectBase
{
public:
	const bCObjectBase& operator=( const bCObjectBase&);

	// 0xbCObjectBase interface
	virtual uint16 GetVersion() const;              // 0x00
	virtual bool IsValid() const;                   // 0x04
	virtual bEResult Write( bCOStream&);            // 0x08
private:
	virtual bool Write( bCOStream&) const;          // 0x0C
public:
	virtual bEResult Read( bCIStream&);             // 0x10
protected:
	virtual void Destroy();                         // 0x14
public:
	virtual bEResult Create();                      // 0x18
	virtual bEResult CopyFrom( const bCObjectBase&);// 0x1C
	virtual uint32 AddReference();                  // 0x20
	virtual uint32 ReleaseReference();              // 0x24
	virtual uint32 GetReferenceCount();             // 0x28
	virtual const uint32 GetProfileLastTicksFirst() const;      // 0x2C
	virtual const uint32 GetProfileLastTicksSecond() const;     // 0x30
	virtual const uint32 GetProfileLastTicksThird() const;      // 0x34

	// Virtual destructor
	virtual ~bCObjectBase();                        // 0x38
};


inline const bCObjectBase& bCObjectBase::operator=( const bCObjectBase& Other)
{
	CopyFrom( Other);
	return *this;
}

inline uint16 bCObjectBase::GetVersion() const
{
	return 1; 
}

inline bool bCObjectBase::IsValid() const
{
	return true;
}

inline bEResult bCObjectBase::Create()
{
	return bEResult_OK;
}

inline bEResult bCObjectBase::CopyFrom( const bCObjectBase&)
{
	return bEResult_OK;
}

inline uint32 bCObjectBase::AddReference()
{
	return 1;
}

inline uint32 bCObjectBase::GetReferenceCount()
{
	return 1;
}

inline const uint32 bCObjectBase::GetProfileLastTicksFirst() const
{
	return 0;
}

inline const uint32 bCObjectBase::GetProfileLastTicksSecond() const
{
	return 0;
}

inline const uint32 bCObjectBase::GetProfileLastTicksThird() const
{
	return 0;
}

inline bCObjectBase::~bCObjectBase()
{
}
