#pragma once

class Effect
{
	int unk_00;
};

class G3SCRIPTAPI EffectSystem
{
public:
	static Effect StartEffect( const bCString&, const Entity&);
};
