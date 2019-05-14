
#include <Windows.h>

#include "DLL_All.h"


int Util::Rand(int Num)
{
	return ((rand() & 0x7FFF) | (rand() << 15)) % Num;
}

void Util::EncodeJump( uint8* At, uint8* To)
{
	TScopedVirtualProtect<5> VirtualUnlock( At);
	uint32 Relative = To - (At + 5);
	*At = 0xE9;
	*(uint32*)(At+1) = Relative;
}

void Util::EncodeCall( uint8* At, uint8* To)
{
	TScopedVirtualProtect<5> VirtualUnlock( At);
	uint32 Relative = To - (At + 5);
	*At = 0xE8;
	*(uint32*)(At+1) = Relative;
}

void Util::ModifyPointer( uint8* At, uint8* To)
{
	TScopedVirtualProtect<4> VirtualUnlock( At);
	*(uint8**)(At) = To;
}

