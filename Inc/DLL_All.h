#pragma once

#include <Windows.h>

#pragma warning (disable : 4251) //We want to inline some code and importing it will get in the way

#define DLLIMPORT __declspec(dllimport)
#define DLLEXPORT __declspec(dllexport)
#define G3API DLLIMPORT
#define G3ENGINEAPI DLLIMPORT
#define G3SHAREDAPI DLLIMPORT
#define G3SCRIPTAPI DLLIMPORT
#define G3GAMEAPI DLLIMPORT

// NOTE: Gothic 3 appears to have been compiled using __stdcall as default calling convention
// So make sure the compiler uses /Gz in it's command line

#ifndef _M_IX86
	#error You must target the project to x86 architecture
#endif


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;


inline void memzero_dwords( void* Dest, uint32 dword_count)
{	
	__asm
	{
		mov		ecx, [dword_count]
		mov		edi, [Dest]
		xor     eax, eax
		rep		stosd
	}
	//NEED MINGW IMPLEMENTATION!
}

enum gEZoneType;
enum gEAnimDirection;
enum gEDirection;
enum gEGotoStatus;
enum gEWalkMode;
enum gECharMovementMode;
class bCIStream;
class bCOStream;
class gCNavPath_PS;
class gSObstacleEvadeSwitch;
class gCCharacterMovement_PS;
struct eSPropertySetDebugLine;
struct eCCollisionDesc;
struct eSRayIntersectionDesc;
struct eSModuleDebugLine;
struct eCMenu;
struct bCMatrix;
struct bCMemoryStream;
struct bCGuid;
struct bCVolume;
struct bCTriangle;
struct bCBox;
struct eCContextBase;
struct eCNode;
struct bCMotion;

class eCInpShared
{
public:
	class eSGameKeyMessage;
	class eSInputMessage;
};

//Temporary, for compiler
#include "Engine/eCApplication.h"
#include "Engine/eCSceneAdmin.h"
#include "SharedBase/bCVector.h"
#include "SharedBase/bTValMap.h"
#include "SharedBase/bCCriticalSectionWin32.h"

#include "G3HookGlobals.h"
#include "G3HookTemplates.h"
