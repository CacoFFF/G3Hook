#pragma once

// Superclass
#include "bCObjectBase.h"

#include "bCPropertyObjectBase.h"

#include "bCString.h"

class G3SHAREDAPI bCObjectRefBase : public bCObjectBase
{
public:
	bCPropertyObjectBase* PropertyObject;
	int unk_08;

	// Constructors and destructors
	bCObjectRefBase();

	void Invalidate();
	bCPropertyObjectBase* GetPropertyObject();
	const bCPropertyObjectBase* GetPropertyObject() const;

	// bCObjectBase interface
	bool IsValid() const;                   // 0x04
	void Destroy();                         // 0x14
	uint32 GetReferenceCount();             // 0x28

	// bCObjectRefBase interface
	virtual bool IsVirtualReferencingEnabled();                          // 0x3C
	virtual bEResult PostInitializeProperties();                         // 0x40
	virtual uint32 NotifyPropertyValueChangedEnter( const char*);        // 0x44
	virtual uint32 NotifyPropertyValueChangedExit( const char*);         // 0x48
	virtual bool OnNotifyPropertyValueChangedEnterEx( const char*, bool);// 0x4C
	virtual bool OnNotifyPropertyValueChangedExitEx( const char*, bool); // 0x50
	virtual void NotifyPropertyDeprecated( const bCString*, const bCString*, bCMemoryStream*, uint16);// 0x54
	virtual bool NotifyPropertyValueChangedEnterEx(char const*, bool);   // 0x58
	virtual bool NotifyPropertyValueChangedExitEx(char const*, bool);    // 0x5C
};


inline bCObjectRefBase::bCObjectRefBase()
	: PropertyObject(nullptr)
	, unk_08(1)
{
}

inline void bCObjectRefBase::Invalidate()
{
	PropertyObject = nullptr;
	unk_08 = 0;
}

inline bCPropertyObjectBase* bCObjectRefBase::GetPropertyObject()
{
	return PropertyObject;
}

inline const bCPropertyObjectBase* bCObjectRefBase::GetPropertyObject() const
{
	return PropertyObject;
}

inline bool bCObjectRefBase::IsValid() const
{
	return (unk_08 & 0x80000000) != 0;
}

inline void bCObjectRefBase::Destroy()
{
	if ( IsValid() )
	{
		unk_08 &= 0x7FFFFFFF;
		IsValid();
	}
}

inline uint32 bCObjectRefBase::GetReferenceCount()
{
	return unk_08 & 0x7FFFFFFF;
}

inline bool bCObjectRefBase::IsVirtualReferencingEnabled()
{
	return true;
}

inline bEResult bCObjectRefBase::PostInitializeProperties()
{
	return bEResult_OK;
}

inline bool bCObjectRefBase::OnNotifyPropertyValueChangedEnterEx( const char*, bool)
{
	return true;
}

inline bool bCObjectRefBase::OnNotifyPropertyValueChangedExitEx( const char*, bool)
{
	return true;
}

inline void bCObjectRefBase::NotifyPropertyDeprecated( const bCString*, const bCString*, bCMemoryStream*, unsigned short)
{
}
