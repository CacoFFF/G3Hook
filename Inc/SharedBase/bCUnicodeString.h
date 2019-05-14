#pragma once

class G3SHAREDAPI bCUnicodeString
{
public:
	void* Data;

	bCUnicodeString()
		: Data(0)
	{}

	bCUnicodeString( const char*);
	bCUnicodeString( int);
	bCUnicodeString( int32);
	bCUnicodeString( uint32);
	~bCUnicodeString();

	bCUnicodeString operator+( const bCUnicodeString&) const;
};
