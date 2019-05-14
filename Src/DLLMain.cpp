#include <Windows.h>
#include <Psapi.h>

#include "DLL_All.h"

#pragma comment (lib,"Engine.lib")
#pragma comment (lib,"Script.lib")
#pragma comment (lib,"Game.lib")
#pragma comment (lib,"SharedBase.lib")

static HMODULE hScript_Game = 0;

uint8* ModuleBase::Script_Game = nullptr;
uint8* ModuleBase::Script = nullptr;
uint8* ModuleBase::Game = nullptr;
uint8* ModuleBase::Engine = nullptr;
uint8* ModuleBase::SharedBase = nullptr;

G3HookGlobal::F_ScriptProc_EEI G3HookGlobal::NextLevelXP = nullptr;
G3HookGlobal::F_ScriptProc_EEI G3HookGlobal::AttitudeTo = nullptr;
G3HookGlobal::F_ScriptProc_EEI G3HookGlobal::AssessHit = nullptr;
G3HookGlobal::F_ScriptProc_EEI G3HookGlobal::IsGateGuard = nullptr;
G3HookGlobal::F_ScriptProc_EEI G3HookGlobal::RefreshWeaponry = nullptr;
G3HookGlobal::F_ScriptProc_EEI G3HookGlobal::SetAttackReason = nullptr;
G3HookGlobal::F_UseTypesE G3HookGlobal::IsUseTypes = nullptr;
G3HookGlobal::F_CanKnockDown G3HookGlobal::CanKnockDown = nullptr;

#ifdef __MINGW32__
	#define ForceAssign(Member,dest) \
	__asm__ ( "mov %%eax,(%%ecx)": : "a"(Member), "c"(&dest) : "memory" );
#else
	#define ForceAssign(Member,dest) \
	__asm { \
		__asm mov eax,Member \
		__asm lea ecx,dest \
		__asm mov [ecx],eax }
/*
	#define ForceAssign(Member,dest) \
	__asm { \
		__asm mov eax,Member \
		__asm lea dest,eax }
*/
#endif

BOOL WINAPI DllMain( HINSTANCE /*hinstDLL*/, DWORD fdwReason, LPVOID /*lpvReserved*/)
{
	if ( fdwReason == DLL_PROCESS_ATTACH )
	{
		MODULEINFO mInfo;
		HANDLE Proc = GetCurrentProcess();
		GetModuleInformation( Proc, GetModuleHandleA("Script_Game.dll"), &mInfo, sizeof(MODULEINFO));
		ModuleBase::Script_Game = (uint8*)mInfo.lpBaseOfDll;
		GetModuleInformation( Proc, GetModuleHandleA("Script.dll"), &mInfo, sizeof(MODULEINFO));
		ModuleBase::Script = (uint8*)mInfo.lpBaseOfDll;
		GetModuleInformation( Proc, GetModuleHandleA("Game.dll"), &mInfo, sizeof(MODULEINFO));
		ModuleBase::Game = (uint8*)mInfo.lpBaseOfDll;
		GetModuleInformation( Proc, GetModuleHandleA("Engine.dll"), &mInfo, sizeof(MODULEINFO));
		ModuleBase::Engine = (uint8*)mInfo.lpBaseOfDll;
		GetModuleInformation( Proc, GetModuleHandleA("SharedBase.dll"), &mInfo, sizeof(MODULEINFO));
		ModuleBase::SharedBase = (uint8*)mInfo.lpBaseOfDll;

		G3HookGlobal::NextLevelXP = (G3HookGlobal::F_ScriptProc_EEI)(ModuleBase::Script_Game + 0x4E800);
		G3HookGlobal::AttitudeTo = (G3HookGlobal::F_ScriptProc_EEI)(ModuleBase::Script_Game + 0xE3B0);
		G3HookGlobal::AssessHit = (G3HookGlobal::F_ScriptProc_EEI)(ModuleBase::Script_Game + 0x2B580);
		G3HookGlobal::IsGateGuard = (G3HookGlobal::F_ScriptProc_EEI)(ModuleBase::Script_Game + 0x10E20);
		G3HookGlobal::RefreshWeaponry = (G3HookGlobal::F_ScriptProc_EEI)(ModuleBase::Script_Game + 0xAB9B0);
		G3HookGlobal::SetAttackReason = (G3HookGlobal::F_ScriptProc_EEI)(ModuleBase::Script_Game + 0x371C0);
		
		G3HookGlobal::IsUseTypes = (G3HookGlobal::F_UseTypesE)(ModuleBase::Script_Game + 0x40F0);
		G3HookGlobal::CanKnockDown = (G3HookGlobal::F_CanKnockDown)(ModuleBase::Script_Game + 0x3240);

		Util::ModifyData<double>( ModuleBase::Script_Game + 0x107788, 62000.0 + 10000.0); //Increase follow distance by 10k

		// Can't directly acquire member function pointers!
		// Assign using assembly, JumpDests requires offset, not array index

		//Call redirecters
		#define JUMP_COUNT 6
		uint8* JumpLocs[JUMP_COUNT];
		uint8* JumpDests[JUMP_COUNT];

		JumpLocs[0] = ModuleBase::Script_Game + 0xB0790;
		JumpDests[0] = (uint8*)&G3HookGlobal::ManaRegenTimer;

		JumpLocs[1] = ModuleBase::Script + 0x1AFE0;
		ForceAssign( G3HookEntity::StartTransform_Hook, JumpDests+0x4 )

		JumpLocs[2] = ModuleBase::Script_Game + 0x4E160;
		JumpDests[2] = (uint8*)&G3HookGlobal::KillXP;

		JumpLocs[3] = ModuleBase::Script + 0x1B230;
		ForceAssign( G3HookEntity::EndTransform_Hook, JumpDests+0xC )

		JumpLocs[4] = ModuleBase::Script_Game + 0x6B550;
		JumpDests[4] = (uint8*)&G3HookGlobal::ItemTradePrice;

		JumpLocs[5] = ModuleBase::Script_Game + 0x50370;
		JumpDests[5] = (uint8*)&G3HookGlobal::FAI_Ranged;

		for ( int i=0 ; i<JUMP_COUNT ; i++ )
			Util::EncodeJump( JumpLocs[i], JumpDests[i]);

		//Call procedure proxies/replacements
		#define CALL_COUNT 7
		uint8* CallLocs[CALL_COUNT];
		uint8* CallDests[CALL_COUNT];

		CallLocs[0] = ModuleBase::Script_Game + 0xAB2D1;
		CallLocs[1] = ModuleBase::Script_Game + 0xB583E;
		CallDests[0] = CallDests[1] = (uint8*)&G3HookGlobal::AssessHit_Proxy;

		CallLocs[2] = ModuleBase::Script_Game + 0x11C4C;
		CallLocs[3] = ModuleBase::Script_Game + 0x12A40;
		CallLocs[4] = ModuleBase::Script_Game + 0x13D09;
		CallLocs[5] = ModuleBase::Script_Game + 0xAB7C7;
		CallLocs[6] = ModuleBase::Script_Game + 0xAC989;
		CallDests[2] = CallDests[3] = CallDests[4] = CallDests[5] = CallDests[6] = (uint8*)&G3HookGlobal::RefreshWeaponry_Proxy;

		for ( int i=0 ; i<CALL_COUNT ; i++ )
			Util::EncodeCall( CallLocs[i], CallDests[i]);

		//External linking hooks
		uint8* AssureItems_MiddleMan;
		ForceAssign( G3HookPSInventory::AssureItems_Middleman, AssureItems_MiddleMan);
		Util::ModifyPointer( ModuleBase::Script_Game + 0xE432C, AssureItems_MiddleMan);

		//Other hooks
		Util::ModifyPointer( ModuleBase::Script_Game + 0xD24C6, (uint8*)&G3HookGlobal::AssessHit_Proxy);
		Util::ModifyPointer( ModuleBase::Script_Game + 0xE14F6, (uint8*)&G3HookGlobal::RefreshWeaponry_Proxy);
	}
	return 1;
}



