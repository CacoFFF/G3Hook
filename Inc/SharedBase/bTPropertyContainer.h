#pragma once

#include "bCObjectBase.h"

template <typename T> class bTPropertyContainer : public bCObjectBase
{
public:
	T Property;

	operator T&();
	operator const T&() const;
	T& Get();
	const T& Get() const;

	bTPropertyContainer<T>& operator=( const T& Other);

	bool operator==( const T& Other);
	bool operator==( const bTPropertyContainer<T>& Other);

};


template<typename T>
inline bTPropertyContainer<T>::operator T&()
{
	return Property;
}

template<typename T>
inline bTPropertyContainer<T>::operator const T&() const
{
	return Property;
}

template<typename T>
inline T& bTPropertyContainer<T>::Get()
{
	return Property;
}

template<typename T>
inline const T& bTPropertyContainer<T>::Get() const
{
	return Property;
}

template<typename T>
inline bTPropertyContainer<T>& bTPropertyContainer<T>::operator=(const T & Other)
{
	Property = Other;
	return *this;
}

template<typename T>
inline bool bTPropertyContainer<T>::operator==(const T & Other)
{
	return Property == Other;
}

template<typename T>
inline bool bTPropertyContainer<T>::operator==(const bTPropertyContainer<T>& Other)
{
	return Property == Other.Property;
}
