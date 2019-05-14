#pragma once

struct ScopedHANDLE
{
	HANDLE Handle;

	ScopedHANDLE( HANDLE InHandle=0)
		: Handle(InHandle)
	{
	}

	~ScopedHANDLE()
	{
		if ( Handle )
		{
			CloseHandle( Handle);
			Handle = 0;
		}
	}

	operator HANDLE()
	{
		return Handle;
	}

	operator const HANDLE() const
	{
		return Handle;
	}
};
