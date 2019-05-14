#pragma once

class bCIStream;
class bCOStream;
class NxVec3;
struct bCMatrix;

//TODO: Inline missing code (imported with G3SHAREDAPI macro)

class bCVector
{
public:
	float X, Y, Z;

	bCVector();
	bCVector( float InF);
	bCVector( float InX, float InY, float InZ);
	bCVector( const float* F);
	bCVector( const bCVector& Other);
	bCVector( const NxVec3& Other);
	~bCVector();

	bool operator==( const bCVector& Other) const;
	bool operator!=( const bCVector& Other) const;

	bCVector operator-() const;
	bCVector& operator=( const bCVector& V);
	bCVector operator+( const bCVector& V) const;
	bCVector operator-( const bCVector& V) const;
	bCVector operator*( float F) const;
	G3SHAREDAPI bCVector operator*( const bCMatrix& M) const;
	bCVector operator/( float F) const;
	G3SHAREDAPI bCVector operator/( const bCMatrix& M) const;


	float& operator[]( int Coordinate);
	const float& operator[]( int Coordinate) const;
	operator NxVec3&();
	operator const NxVec3&() const;

	float GetSquareMagnitude() const;

	G3SHAREDAPI bCIStream& operator<<( bCIStream& In);
	G3SHAREDAPI bCOStream& operator>>( bCOStream& Out);
};


inline bCVector::bCVector()
{}
inline bCVector::bCVector( float InF)
	: X(InF), Y(InF), Z(InF)
{}
inline bCVector::bCVector( float InX, float InY, float InZ)
	: X(InX), Y(InY), Z(InZ)
{}
inline bCVector::bCVector( const float* F)
	: X(F[0]), Y(F[1]), Z(F[2])
{}
inline bCVector::bCVector( const bCVector& Other)
	: X(Other.X), Y(Other.Y), Z(Other.Z)
{}
inline bCVector::bCVector( const NxVec3& Other) //Delegate to array of floats (C++11)
	: bCVector( (const float*)&Other)
{}
inline bCVector::~bCVector()
{}


inline bCVector bCVector::operator-() const
{
	return bCVector( -X, -Y, -Z);
}

inline bCVector & bCVector::operator=(const bCVector & Other)
{
	X=Other.X; Y=Other.Y; Z=Other.Z;
	return *this;
}

inline bCVector bCVector::operator+(const bCVector & V) const
{
	return bCVector( X+V.X, Y+V.Y, Z+V.Z);
}

inline bCVector bCVector::operator-(const bCVector & V) const
{
	return bCVector( X-V.X, Y-V.Y, Z-V.Z);
}

inline bCVector bCVector::operator*(float F) const
{
	return bCVector( X*F, Y*F, Z*F);
}

inline bCVector bCVector::operator/(float F) const
{
	float Rcp = 1 / F;
	return bCVector( X*Rcp, Y*Rcp, Z*Rcp);
}

inline bool bCVector::operator==( const bCVector& Other) const
{
	return X==Other.X && Y==Other.Y && Z==Other.Z;
}

inline bool bCVector::operator!=( const bCVector& Other) const
{
	return X!=Other.X || Y!=Other.Y || Z!=Other.Z;
}

inline float& bCVector::operator[]( int Coordinate)
{
	return *(&X + Coordinate);
}

inline const float & bCVector::operator[]( int Coordinate) const
{
	return *(&X + Coordinate);
}

inline bCVector::operator NxVec3&()
{
	return *(NxVec3*)&X;
}

inline bCVector::operator const NxVec3&() const
{
	return *(const NxVec3*)&X;
}

inline float bCVector::GetSquareMagnitude() const
{
	return X*X + Y*Y + Z*Z;
}

