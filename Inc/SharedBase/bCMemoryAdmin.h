#pragma once


class G3SHAREDAPI bCMemoryAdmin
{
public:
	bool HeapProfiler;
	bool MemoryLeakReport;
	bool DumpHeapProfiling;

	bCMemoryAdmin();
	bCMemoryAdmin( bool);
	~bCMemoryAdmin();

	bCMemoryAdmin& operator=( const bCMemoryAdmin& Other);

protected:
	void Create();
	void Invalidate();
public:
	void Destroy();

	void* Malloc( uint32 Size); //Need MemHeap class
	void* Realloc( void* Ptr, uint32 NewSize);
	void Free( void* Ptr);

	void* NewObject( uint32 ObjectSize);
	void DeleteObject( void* Object);

	void EnableHeapProfiler( bool bEnable);
	void EnableMemoryLeakReport( bool bEnable);
	void EnableDumpHeapProfiling( bool bEnable);

	static bCMemoryAdmin& GetInstance();

private:
	static bool ms_bInitialized;
};




inline bCMemoryAdmin::bCMemoryAdmin()
{
	Create();
}

inline bCMemoryAdmin::bCMemoryAdmin( bool P1)
{
	Create();
	HeapProfiler = P1;
}

inline bCMemoryAdmin::~bCMemoryAdmin()
{
	Destroy();
}

inline bCMemoryAdmin& bCMemoryAdmin::operator=( const bCMemoryAdmin& Other)
{
	*(int*)this = *(int*)&Other;
	return *this;
}

/*inline void bCMemoryAdmin::Create()
{
	static bool Created = false; //Allocated 1 byte after ms_bInitialized (static var in SharedBase.dll)
	if ( !Created )
	{
		HeapProfiler = false;
		MemoryLeakReport = true;
		Created = true;
		ms_bInitialized = true;
	}
}*/

inline void bCMemoryAdmin::Invalidate()
{
	HeapProfiler = false;
	MemoryLeakReport = true;
}

inline void* bCMemoryAdmin::NewObject( uint32 ObjectSize)
{
	return Malloc( ObjectSize);
}

inline void bCMemoryAdmin::DeleteObject( void* Object)
{
	Free( Object);
}

inline void bCMemoryAdmin::EnableHeapProfiler(bool bEnable)
{
	if ( bEnable )
		HeapProfiler = bEnable;
}

inline void bCMemoryAdmin::EnableMemoryLeakReport( bool bEnable)
{
	MemoryLeakReport = bEnable;
}

inline void bCMemoryAdmin::EnableDumpHeapProfiling( bool bEnable)
{
	DumpHeapProfiling = bEnable;
}