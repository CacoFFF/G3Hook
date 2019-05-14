#pragma once

#include "SharedBase/bTPropertyContainer.h"
#include "Engine/eCEntity.h"

#define PS_EPROPERTY(name,type) \
	type name; \
	const type& Get##name() const { return name; } \
	void Set##name( const type&);


#define PS_BASE(psname,pstype) \
	friend class G3HookEntity; \
	friend class G3HookGlobal; \
	friend class G3HookUtils; \
	typedef pstype PSType; \
\
public: \
	PSType* PS; \
	psname( PSType* InPS=nullptr)          : PS(InPS) {} \
	psname( eCEntity*); \
	~psname()                              {} \
	const PSType* operator->() const       { return PS; } \
protected: \
	PSType* operator->()                   { return PS; } \
public: \
\
	bool IsValid() const                   { return PS != nullptr; } \
//	template <class T> inline typename ReturnType<T>::Type GetProperty()  { return (ReturnType<T>::Type)(*(T*)this); } \


template<typename T> struct ReturnType
{
	typedef T Type;
};


#define PS_PROPERTY(name,type) \
	struct DLLIMPORT Property##name \
	{ public: \
		operator type() const; \
	};
//	template<> inline type <Property##name>GetProperty()  { return (type)(*(Property##name*)this); }


#define DEF_GET_PS(pstype) \
	class gC##pstype##_PS; \
	template<> inline gC##pstype##_PS* GetPropertySet<gC##pstype##_PS>( eCEntity* EEntity) \
	{ return (gC##pstype##_PS*)EEntity->GetPropertySet(eEPropertySetType_##pstype); }

template <typename PSTYPE> inline PSTYPE* GetPropertySet( eCEntity* EEntity);
DEF_GET_PS(Item);
DEF_GET_PS(Interaction);
DEF_GET_PS(Damage);
#undef DEF_GET
