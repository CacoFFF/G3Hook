#pragma once

//****************************
// Arithmetic - Unreal Styled
template<typename T> T Min( const T& A, const T& B)
{
	return A < B ? A : B;
}
template<typename T> T Max( const T& A, const T& B)
{
	return A > B ? A : B;
}
template<class T> inline T Clamp( const T X, const T Min, const T Max )
{
	return X<Min ? Min : X<Max ? X : Max;
}


//***************
// Virtual Memory
template <size_t MemSize> class TScopedVirtualProtect
{
	uint8* Address;
	uint32 RestoreProtection;

	TScopedVirtualProtect() {}
public:
	TScopedVirtualProtect( uint8* InAddress)
		: Address( InAddress)
	{
		if ( Address )	VirtualProtect( Address, MemSize, PAGE_EXECUTE_READWRITE, &RestoreProtection);
	}

	~TScopedVirtualProtect()
	{
		if ( Address )	VirtualProtect( Address, MemSize, RestoreProtection, &RestoreProtection);
	}
};

template <size_t N> struct TCodeBackup
{
	uint8* Address;
	uint8 Bytes[N];

	TCodeBackup( uint8* InAddress=nullptr)
	{
		CreateBackup( InAddress);
	}

	~TCodeBackup()
	{
		ApplyBackup();
	}

	void CreateBackup( uint8* InAddress)
	{
		if ( (Address=InAddress) == nullptr )
			return;
		for ( size_t i=0 ; i<N ; i++ )
			Bytes[i] = Address[i];
	}

	void ApplyBackup()
	{
		if ( !Address )
			return;
		for ( size_t i=0 ; i<N ; i++ )
			Address[i] = Bytes[i];
	}
private:
	TCodeBackup<N>& operator=( TCodeBackup<N>&);
};



//************************************
// Data modifier on VM protected areas

template<typename T>
void Util::ModifyData( uint8* At, T Data)
{
	TScopedVirtualProtect<sizeof(T)> VirtualUnlock( At);
	*(T*)At = Data;
}