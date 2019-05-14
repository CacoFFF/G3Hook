
#include "All.h"
#include "ScopedHandle.h"

#include <Psapi.h>

#include "Cacus/TCharBuffer.h"


static HMODULE FindNamedModule( HANDLE hProcess, HMODULE* ModuleList, size_t ModuleCount, const wchar_t* ModuleName)
{
	TCharBuffer<256,wchar_t> Name;
	for ( size_t i=0 ; i<ModuleCount ; i++ )
	{
		GetModuleBaseNameW( hProcess, ModuleList[i], *Name, Name.Size());
		if ( !_wcsicmp( *Name, ModuleName) )
			return ModuleList[i];
	}
	return 0;
}


int main( int pc, char** pl)
{
	//Find Gothic 3 process and attach to it
	while ( true )
	{
		uint32 Gothic3ProcessId = 0;
		printf( "Looking for Gothic 3 process... ");
		while ( !Gothic3ProcessId )
		{
			Sleep( 1000);

			uint32 ProcessCount;
			uint32 ProcessList[1024];
			if ( !EnumProcesses( ProcessList, sizeof(ProcessList), &ProcessCount) || !ProcessCount )
				continue;
			ProcessCount /= sizeof(DWORD);

			for ( uint32 i=0 ; i<ProcessCount ; i++ )
			{
				ScopedHANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, ProcessList[i]);
				if ( hProcess )
				{
					TCharBuffer<1024,wchar_t> ProcessName;
					if ( GetModuleFileNameEx( hProcess, nullptr, *ProcessName, 1024) )
					{
						const wchar_t *Pos, *TestPos;
						for ( Pos=TestPos=*ProcessName ; TestPos ; TestPos=CStrstr(Pos,TEXT("\\")) )
							Pos=TestPos+1;
						
						if ( !_wcsicmp( Pos, TEXT("Gothic3.exe")) )
						{
							printf( "FOUND (%i)\n", (int32)ProcessList[i]);
							Gothic3ProcessId = ProcessList[i];
							break;
						}
					}
				}
			}
		}

		if ( Gothic3ProcessId )
		{
			printf( "Waiting for game to load scripts... ");
			HMODULE hScript = 0;
			HMODULE hScript_Game = 0;
			HMODULE hKernel32 = 0;
			while ( true )
			{
				Sleep( 1000);

				ScopedHANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, false, Gothic3ProcessId);
				uint32 ModuleCount = 0;
				HMODULE ModuleList[128];
				if ( !hProcess || !EnumProcessModules( hProcess, ModuleList, sizeof(ModuleList), &ModuleCount) )
				{
					Gothic3ProcessId = 0;
					printf( "Gothic 3 has terminated\n");
					break;
				}
				ModuleCount /= sizeof(uint32);

				uint32 IsLoaded = hScript && hScript_Game;
				hScript      = FindNamedModule( hProcess, ModuleList, ModuleCount, TEXT("Script.dll"));
				hScript_Game = FindNamedModule( hProcess, ModuleList, ModuleCount, TEXT("Script_Game.dll"));
				hKernel32    = FindNamedModule( hProcess, ModuleList, ModuleCount, TEXT("Kernel32.dll"));
				if ( !IsLoaded && hScript && hScript_Game && hKernel32 )
				{
					printf( "DONE\n");
					//Apply game hooks

					//Get path of app/dll
					TChar8Buffer<512> DllPath;
					GetModuleFileNameA( GetModuleHandle( NULL), *DllPath, DllPath.Size());
					char* Pos = CStrstr( *DllPath, ".exe");
					if ( !Pos )
						continue;
					CStrcpy_s( Pos, DllPath.Size()-(Pos-*DllPath),  "Dll.dll");

					//Calculate LoadLibraryA offset of Gothic3 process
					uint8* MyLoadLibraryA = (uint8*)GetProcAddress(GetModuleHandleA("Kernel32.dll"),"LoadLibraryA");
					MODULEINFO OwnInfo, G3Info;
					GetModuleInformation( GetCurrentProcess(), GetModuleHandleA("Kernel32.dll"), &OwnInfo, sizeof(MODULEINFO));
					GetModuleInformation( hProcess, hKernel32, &G3Info, sizeof(MODULEINFO));
//					printf( "OwnLoad=%i, OwnBase=%i, G3Base=%i \n", (int32)MyLoadLibraryA, (int32)OwnInfo.lpBaseOfDll, (int32)G3Info.lpBaseOfDll);

					//Allocate memory containing path inside the game
					size_t AllocSize = DllPath.Len() + 1;
					void* g3ModuleName = VirtualAllocEx( hProcess, 0, AllocSize, MEM_COMMIT, PAGE_READWRITE);
					WriteProcessMemory(hProcess, g3ModuleName, (void*)&DllPath, AllocSize, 0);

					// Create a Remote Thread in the target process which
					// calls LoadLibraryA as our dllpath as an argument -> program loads our dll
					HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0,
						(LPTHREAD_START_ROUTINE)((uint8*)G3Info.lpBaseOfDll + (MyLoadLibraryA-(uint8*)OwnInfo.lpBaseOfDll)) //Calculate address of LoadLibraryA
						, g3ModuleName, 0, 0);
					WaitForSingleObject(hLoadThread, INFINITE);
					VirtualFreeEx(hProcess, g3ModuleName, AllocSize, MEM_RELEASE);

					//Hook fails, see if LoadLibraryA is same here and in Gothic3, otherwise apply difference (?)

					/**
					The problem you're likely running into is that the address of LoadLibraryA() in your application might not be the same in the target process,
					due to ASLR - a technology designed specifically to thwart the activity you're attempting. Modern versions of Windows (Vista+) have this enabled by default for system DLLs
					In order to do what you want, you'll need to implement a proper ThreadProc in your application that loads your DLL,
					allocate some executable memory (PAGE_EXECUTE) memory in your target process, copy it there, and use this address as your thread start point.
*/

					printf( "Injected %s into game\n", *DllPath);
				}

			}
		}

		Sleep( 1000);
	}
	return 0;
}
