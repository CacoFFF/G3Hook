#pragma once

template<typename T> class bTObjArray
{
public:
	T* Data;
	int Num;
	int NumMax;

	bTObjArray()
		: Data(nullptr), Num(0), NumMax(0)
	{
	}

	~bTObjArray()
	{
		if ( Data )
		{
			for ( int i=0 ; i<Num ; i++ )
				Data[i].~T();
			bCMemoryAdmin::GetInstance().Free( Data);
		}
	}
};
