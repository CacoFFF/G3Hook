#pragma once

// Superclass
#include "SharedBase/bCObjectRefBase.h"

#include "SharedBase/bTValArray.h"
#include "SharedBase/bTObjArray.h"

class eCRenderContext;
class eCContactIterator;
class eCTemplateEntityProxy;
class eCTemplateEntity;

enum eEDecayState;

class G3API eCEntityPropertySet : public bCObjectRefBase
{
public:
	eCEntity* Entity; // 0C
	char unk_10;

	enum eEPSSaveGameRelevance
	{
		eEPSSaveGameRelevance_0,
		eEPSSaveGameRelevance_1,
		eEPSSaveGameRelevance_2 //FIND OUT WHAT THIS MEANS
	};

	// bCObjectRefBase --- need to see if this class has own versions!
	bool NotifyPropertyValueChangedEnterEx( const char*, bool);		// 58 - called before changing property
	bool NotifyPropertyValueChangedExitEx( const char*, bool);		// 5C - called after changing property


	// eCEntityPropertySet interface
	virtual enum eEPropertySetType GetPropertySetType() const;		// 60
	virtual const bCString* GetPropertySetClassName();		// 64
	virtual eCEntity* GetEntity();		// 68
	virtual const eCEntity GetEntity() const;		// 6C
	virtual bool CanBePaused() const                     { return true; }		// 70
	virtual bool IsReferencedByTemplate() const          { return true; }		// 74
	virtual bool IsPersistable() const                   { return true; }		// 78
	virtual bool IsCopyable() const                      { return true; }		// 7C
	virtual bool IsVisual() const                        { return false; }		// 80
	virtual bool IsProcessable() const                   { return false; }		// 84
	virtual bool IsPhysicRelevant() const                { return false; }		// 88
	virtual bool IsEditorRelevant() const                { return true; }		// 8C
	virtual eCRenderContext* QueryRenderContext()        { return nullptr; }		// 90
	virtual bool SupportsRenderDebugOutput() const       { return false; }		// 94
	virtual bool IsRefracted() const                     { return false; }		// 98
	virtual bool HasRenderAlphaComponent() const         { return false; }		// 9C
	virtual bEResult ReadSaveGame( bCIStream& Stream);		// A0 -- Rev is easy
	virtual bEResult WriteSaveGame( bCOStream& Stream);		// A4
	virtual eEPSSaveGameRelevance GetSaveGameRelevance() const { return eEPSSaveGameRelevance_0; }	// A8
	virtual void OnPostRead()                            {}		// AC
	virtual void GetDependencies( bTValArray<bCString>&, bTValArray<bCString>&, bTObjArray<eCTemplateEntityProxy>&);		// B0
	virtual eCEntityPropertySet* Clone( eCEntity*) const;		// B4
	virtual void SetEntity( eCEntity* InEntity)          { Entity = InEntity; }		// B8

protected:
	virtual int OnAction( const eCInpShared::eSGameKeyMessage&)         { return -1; }		// BC
	virtual int OnMouse( const eCInpShared::eSInputMessage&)            { return -1; }		// C0
	virtual int OnKeyboard( const eCInpShared::eSInputMessage&)         { return -1; }		// C4
	virtual void OnTrigger( eCEntity*, eCEntity*)                       {}		// C8
	virtual void OnUntrigger( eCEntity*, eCEntity*)                     {}		// CC
	virtual void OnTouch( eCEntity*, eCContactIterator&)                {}		// D0 //NPC has own
	virtual void OnIntersect( eCEntity*, eCContactIterator&)            {}		// D4
	virtual void OnUntouch( eCEntity*, eCContactIterator&)              {}		// D8
	virtual void OnDamage( eCEntity*, eCEntity*, int, int, class eCContactIterator&) {}		// DC

public:
	virtual void OnEnterProcessingRange()                {}		// E0 //NPC has own
	virtual void OnExitProcessingRange()                 {}		// E4 //NPC has own

protected:
	virtual void Trigger( const bCString&)               {}		// E8

public:
	virtual bool IsAutoKillEnabled() const               { return false; }		// EC
	virtual eEDecayState GetDecayState() const           { return (eEDecayState)(((int)unk_10 >> 1) & 7); }		// F0
	virtual void eCEntityPropertySet::Decay()            { unk_10 = (unk_10 & 0xF5) | 0x04; }		// F4
	virtual void GetOnScreenDebugLines( uint32, bTObjArray<eSPropertySetDebugLine>&) const {} // F8 //NPC has own

protected:
	virtual void OnRender( short)                        {}		// FC
	virtual void OnRenderAlpha( short)                   {}		// 100

public:
	virtual void OnRenderDebug()                         {}		// 104

protected:
	virtual void OnUpdateInternals()                     {}		// 108
	virtual void OnPostUpdateInternals()                 {}		// 10C
	virtual void OnUpdatedWorldMatrix()                  {}		// 110
	virtual void OnUpdatedWorldTreeBoundary()            {}		// 114
	virtual void OnCacheIn()                             {}		// 118
	virtual void OnCacheOut()                            {}		// 11C

public:
	virtual void GetBoundary( bCBox&, bool)        {}		// 120
	virtual void OnProcess()                             {}		// 124 //NPC has own
	virtual void OnPreProcess()                          {}		// 128 //NPC has own
	virtual void OnPostProcess()                         {}		// 12C
	virtual void OnSaveGameEntityPostRead()              {}		// 130 //NPC has own
	virtual void OnPostCopy( const eCEntityPropertySet&) {}		// 134 //NPC has own
	virtual void OnDeinitialize()                        {}		// 138
	virtual void OnPropertySetAdded()                    {}		// 13C
	virtual void OnPropertySetRemoved()                  {}		// 140
	virtual void OnChildrenAvailable( uint32, uint32, eCTemplateEntity*) {}		// 144
	virtual void OnCustomPatch( const eCEntityPropertySet*) {}		// 148 //NPC has own
	virtual bool IntersectsRay( eSRayIntersectionDesc&, const bCMatrix&, eCCollisionDesc**) const { return 0; } // 14C
	virtual bool IntersectsVolume( bCVolume&, const bCMatrix&, bTValArray<bCTriangle>*, bool) const { return 0; } // 150
};
