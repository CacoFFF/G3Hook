#pragma once

#include "Engine/eCEngineComponentBase.h"

//eCScriptAdminBase is the real superclass
class G3API gCScriptAdmin : public eCEngineComponentBase
{
public:

	// gCEngineComponentBase interface
	void Process();                  // 0x8C
	void PostProcess();              // 0x90


	// gCScriptAdmin interface
	virtual int CallScript( const bCString&, eCEntity*, eCEntity*, int) = 0;         // 0xB8
	virtual bool LoadAllScriptDLLs();                                                // 0xBC
	virtual bool UnloadAllScriptDLLs();                                              // 0xC0
	virtual bool LoadScriptDLL( const bCString&);                                    // 0xC4
	virtual bool UnloadScriptDLL( const bCString&);                                  // 0xC8
	virtual bool IsScriptDLLLoaded( const bCString&) const;                          // 0xCC
	virtual bool GetScriptDLLWithState( const bCString&, bCString&) const;           // 0xD0
	virtual bool GetScriptDLLWithFunction( const bCString&, bCString&) const;        // 0xD4
	virtual bool GetScriptDLLWithCallback( const bCString&, bCString&) const;        // 0xD8
	virtual bool GetScriptDLLWithRoutine( const bCString&, bCString&) const;         // 0xDC
	virtual bool GetScriptDLLWithScript( const bCString&, bCString&) const;          // 0xE0
	virtual bool GetScriptSourceFileWithState( const bCString&, bCString&) const;    // 0xE4
	virtual bool GetScriptSourceFileWithFunction( const bCString&, bCString&) const; // 0xE8
	virtual bool GetScriptSourceFileWithCallback( const bCString&, bCString&) const; // 0xEC
	virtual bool GetScriptSourceFileWithRoutine( const bCString&, bCString&) const;  // 0xF0
	virtual bool GetScriptSourceFileWithScript( const bCString&, bCString&) const;   // 0xF4
	virtual bool GetScriptDLL( const bCString&, bCString&) const;                    // 0xF8
	virtual bool GetScriptSourceFile( const bCString&, bCString&) const;             // 0xFC
};
