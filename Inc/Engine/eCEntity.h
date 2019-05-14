#pragma once

#include "SharedBase/bCObjectRefBase.h"

class G3ENGINEAPI eCEntity : public bCObjectRefBase
{
public: //Super could be eCNode as well
	eCEntity* Parent;
	uint16 unk_10;
	uint16 unk_12;

	void Enable( bool);
	void EnableCollision( bool);

	bool IsEnabled() const;

	const bCString& GetName() const; //at 0x138

	//Functions are identical to eCNode's but return types are not
	//This may mess up the vtable...
	virtual eCEntity* GetParent();             // 0x60
	virtual const eCEntity* GetParent() const; // 0x64
	virtual const eCEntity* GetRoot() const;   // 0x68
	virtual eCEntity* GetChildAt(int);         // 0x6C
	virtual const eCEntity* GetChildAt(int) const; // 0x70 //DIFFERENT CODE AS ABOVE!
	virtual void SetContext( eCContextBase*);  // 0x74
	virtual void Unknown_78();
	virtual int AttachChild( eCNode*);         // 0x7C
	virtual bool DetachChildByIndex(int);      // 0x80
	virtual void RemoveAllChildren(void);      // 0x84
protected: virtual eCNode* DoClone(void) const; // 0x88
public: virtual void ChildrenAvailable(bool);  // 0x8C //eCNode may end here
	virtual void SetName( const bCString&);    // 0x90
	virtual bool Unknown_94();
	virtual bool Unknown_98();
	virtual bool Unknown_9C(); //All 3 return false
	virtual bool IsKilled() const;             // 0xA0
	virtual bCVector GetLinearVelocity() const; // 0xA4
	virtual void SetLinearVelocity( const bCVector&); // 0xA8
	virtual bool Unknown_AC(); //Returns false
protected:
	virtual enum bEResult ReadV83( bCIStream &,uint16);              // 0xB0
	virtual enum bEResult ReadV63( bCIStream &,uint16);              // 0xB4
	virtual void OnUpdatedWorldMatrix();                             // 0xB8
	virtual void OnUpdatedWorldTreeBoundary();                       // 0xBC
	virtual void SetWorldTreeBoundary( const bCBox&);                // 0xC0
	virtual void SetLocalNodeBoundary( const bCBox&);                // 0xC4
	virtual void SetWorldNodeBoundary( const bCBox&);                // 0xC8
public: 
	virtual void SetLocalMatrix( const bCMatrix&);                   // 0xCC
	virtual void SetWorldPosition( const bCVector&);                 // 0xD0
	virtual void SetLocalPosition( const bCVector&);                 // 0xD4
	virtual void UpdateLocalBoundary();                              // 0xD8
	virtual void UpdateParentDependencies();                         // 0xDC
	virtual void UpdateChildDependencies();                          // 0xE0
	virtual bool AddPropertySet( eCEntityPropertySet*, bool);        // 0xE4
	virtual bool RemovePropertySet( const bCString&);                // 0xE8
	virtual eCEntityPropertySet* GetPropertySet( eEPropertySetType); // 0xEC
	virtual void Kill();                                             // 0xF0
	//There's more...
};

//int TestECEntity = sizeof(eCEntity);

inline eCEntity* eCEntity::GetParent()
{
	return Parent;
}

inline const eCEntity* eCEntity::GetParent() const
{
	return Parent;
}

inline const eCEntity* eCEntity::GetRoot() const
{
	const eCEntity* Root = GetParent();
	const eCEntity* NextRoot;
	while ( (NextRoot=Root->GetParent()) != nullptr )
		Root = NextRoot;
	return Root;
}
