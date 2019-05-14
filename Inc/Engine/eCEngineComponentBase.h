#pragma once

#include "eCInputReceiver.h"
#include "SharedBase/bTObjArray.h"

class G3ENGINEAPI eCEngineComponentBase : public eCInputReceiver
{
public:
	bool unk_10; //Both set to 1 in constructors
	bool unk_11;

	void Enable( bool bEnable);
	void Invalidate();

	// bCObjectBase interface
	void Destroy();                          // 0x14

	// eCEngineComponentBase interface
	virtual const bCGuid& GetID() const;     // 0x70
	virtual bEResult Initialize();           // 0x74
	virtual bEResult PreShutdown();          // 0x78 //rev when bCPropertyObjectBase is done
	virtual bEResult Shutdown();             // 0x7C
	virtual void OnAppInitialized();         // 0x80
	virtual bEResult WorldActivate();        // 0x84
	virtual bEResult WorldDeactivate();      // 0x88
	virtual bEResult ResetResources( bool);  // 0x8C
	virtual bEResult RestoreResources( bool);// 0x90
	virtual void Process();                  // 0x94
	virtual void PostProcess();              // 0x98
	virtual void OnBeginRenderSolid();       // 0x9C
	virtual void OnEndRenderSolid();         // 0xA0
	virtual void OnBeginRenderAlpha();       // 0xA4
	virtual void OnEndRenderAlpha();         // 0xA8
	virtual void OnPostRender();             // 0xAC
	virtual void CreateMenu( eCMenu*);       // 0xB0
	virtual void GetDebugLines( bTObjArray<eSModuleDebugLine>&) const;       // 0xB4

	static const bCPropertyObjectBase* GetRootObject();
};

inline void eCEngineComponentBase::Enable( bool bEnable)
{
	unk_10 = bEnable;
}

inline void eCEngineComponentBase::Invalidate()
{
	unk_10 = true;
	unk_11 = true;
}

inline void eCEngineComponentBase::Destroy()
{
	Invalidate();
	eCInputReceiver::Destroy();
}

inline void eCEngineComponentBase::OnAppInitialized()
{
}

inline bEResult eCEngineComponentBase::WorldActivate()
{
	return bEResult_OK;
}

inline bEResult eCEngineComponentBase::WorldDeactivate()
{
	return bEResult_OK;
}

inline bEResult eCEngineComponentBase::ResetResources(bool)
{
	return bEResult_OK;
}

inline bEResult eCEngineComponentBase::RestoreResources(bool)
{
	return bEResult_OK;
}

inline void eCEngineComponentBase::Process()
{
}

inline void eCEngineComponentBase::PostProcess()
{
}

inline void eCEngineComponentBase::OnBeginRenderSolid()
{
}

inline void eCEngineComponentBase::OnEndRenderSolid()
{
}

inline void eCEngineComponentBase::OnBeginRenderAlpha()
{
}

inline void eCEngineComponentBase::OnEndRenderAlpha()
{
}

inline void eCEngineComponentBase::OnPostRender()
{
}

inline void eCEngineComponentBase::CreateMenu( eCMenu*)
{
}

inline void eCEngineComponentBase::GetDebugLines( bTObjArray<eSModuleDebugLine>&) const
{
}
