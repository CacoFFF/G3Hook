#pragma once

class G3SHAREDAPI bCCriticalSectionWin32 //Size is 24
{
public:
	CRITICAL_SECTION CriticalSection;

	bCCriticalSectionWin32();
	~bCCriticalSectionWin32();

	void Acquire();
	void Release();
	bool TryAcquire();

	void SetSpinCount( uint32 SpinCount);
	uint32 GetLockCount() const;
};




inline bCCriticalSectionWin32::bCCriticalSectionWin32()
{
	InitializeCriticalSection( &CriticalSection);
}

inline bCCriticalSectionWin32::~bCCriticalSectionWin32()
{
	DeleteCriticalSection( &CriticalSection);
}

inline void bCCriticalSectionWin32::Acquire()
{
	EnterCriticalSection( &CriticalSection);
}

inline void bCCriticalSectionWin32::Release()
{
	LeaveCriticalSection( &CriticalSection);
}

inline bool bCCriticalSectionWin32::TryAcquire()
{
	return TryEnterCriticalSection( &CriticalSection) ? true : false;
}

inline void bCCriticalSectionWin32::SetSpinCount( uint32 SpinCount)
{
	SetCriticalSectionSpinCount( &CriticalSection, SpinCount);
}

inline uint32 bCCriticalSectionWin32::GetLockCount() const
{
	static_cast<uint32>(CriticalSection.LockCount);
}



