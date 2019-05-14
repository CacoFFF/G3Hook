#pragma once


class G3SHAREDAPI bCPropertyObjectBase
{
public:
	uint32 PropertyFlags;


	bool IsRoot() const;
	bool IsPersistable() const;
	bool IsEmbedded() const;

	// bCPropertyObjectBase interface
	virtual void Pure_00() = 0;
	virtual void Pure_04() = 0;
	virtual void Pure_08() = 0;
	virtual void Pure_0C() = 0;
	virtual void Pure_10() = 0;

	virtual uint16 Read( bCIStream&);
	virtual void Write( bCOStream&);
protected:
	virtual uint16 ReadData( bCIStream&, uint16);
	virtual void WriteData( bCOStream&);

public:
	virtual void Pure_24() = 0;
	virtual void Pure_28() = 0;
	virtual void Pure_2C() = 0;
	virtual uint32 AddReference();
	virtual uint32 ReleaseReference();
	virtual void Pure_38() = 0;

	virtual void CopyFrom( const bCPropertyObjectBase&);

	virtual ~bCPropertyObjectBase();

	bCIStream& operator<<( bCIStream& In);
	bCOStream& operator>>( bCOStream& Out);
};


inline bool bCPropertyObjectBase::IsRoot() const
{
	return (bool)(PropertyFlags & 1);
}

inline bool bCPropertyObjectBase::IsPersistable() const
{
	return (bool)((PropertyFlags>>1) & 1);
}

inline bool bCPropertyObjectBase::IsEmbedded() const
{
	return (bool)((PropertyFlags>>2) & 1);
}

inline bCIStream& bCPropertyObjectBase::operator<<( bCIStream& In)
{
	Read( In);
	return In;
}

inline bCOStream& bCPropertyObjectBase::operator>>( bCOStream& Out)
{
	Write( Out);
	return Out;
}