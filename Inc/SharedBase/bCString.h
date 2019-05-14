#pragma once

class G3SHAREDAPI bCString
{
public:
	struct bSStringData
	{
		int Length;
		uint16 RefCount;
		char Data[1];
	};


	void* Data;

	bCString()
		: Data(0)
	{}

	bCString( const char*);
	~bCString();

	bool operator==( const char*) const;

	bCString operator+( const char*) const;

	int GetLength() const;
	const char* GetText() const;

	bool Contains( const char*, int) const;

protected:
	bSStringData* GetData() const;
	int GetRefCount() const;

protected:
	static void Increment( bSStringData*);
	static int Decrement( bSStringData*);
};


inline int bCString::GetLength() const
{
	return Data ? GetData()->Length : 0;
}

inline bCString::bSStringData* bCString::GetData() const
{
	return (bCString::bSStringData*)((uint8*)Data - 0x08);
}

inline int bCString::GetRefCount() const
{
	return GetData()->RefCount;
}

inline void bCString::Increment( bSStringData* Data)
{
	Data->RefCount++;
}

inline int bCString::Decrement( bSStringData* Data)
{
	return --Data->RefCount;
}
