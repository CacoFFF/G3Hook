#pragma once

class bCString;

class G3API bCPropertyID
{
public:
	int unk_00;
	int unk_04;
	int unk_08;
	int unk_0C;
	int unk_10;

	//Constructor initializes all to zero
	bCPropertyID();

	bool bCPropertyID::operator==( const bCPropertyID& Other) const;
	bool bCPropertyID::operator!=( const bCPropertyID& Other) const;

	bool IsValid() const;

	bCString GetText() const;

	void Invalidate();



/*	operator const bCPropertyID&() const 
	{
		return (bCPropertyID&)*this;
	}*/
};
