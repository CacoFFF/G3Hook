#pragma once

#include "eCTemplateEntity.h"

class G3ENGINEAPI eCTemplateEntityProxy
{
public:
	int unk_04;
	int unk_08;


	eCTemplateEntity* GetEntity();
	const eCTemplateEntity* GetEntity() const;
protected:
	void Invalidate();

public:
	virtual uint16 GetVersion() const;
	virtual bCString GetAddress() const;
	virtual bEResult Read( bCIStream&);
	virtual bEResult Write( bCOStream&);

protected:
	virtual bEResult CopyFrom( const eCTemplateEntityProxy& Other);
	virtual bool Compare( const eCTemplateEntityProxy&) const;

public:
	virtual ~eCTemplateEntityProxy();
};

inline void eCTemplateEntityProxy::Invalidate()
{
	unk_04 = 0;
	unk_08 = 0;
}

inline uint16 eCTemplateEntityProxy::GetVersion() const
{
	return 1;
}
