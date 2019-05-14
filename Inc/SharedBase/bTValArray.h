#pragma once

#include "bCMemoryAdmin.h"

template<typename T> class bTValArray
{
public:
	T* Data;
	int Num;
	int NumMax;

	bTValArray()
		: Data(nullptr), Num(0), NumMax(0)
	{
	}

	// DOES NOT DERIVATE DESTRUCTORS!!
	~bTValArray()
	{
		if ( Data )
		{
			for ( int i=0 ; i<Num ; i++ )
				Data[i].~T();
			bCMemoryAdmin::GetInstance().Free( Data);
		}
	}

	T& operator[]( uint32 Offset)
	{
		return Data[Offset];
	}
};
