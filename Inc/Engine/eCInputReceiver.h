#pragma once

#include "SharedBase/bCObjectRefBase.h"

class G3ENGINEAPI eCInputReceiver : public bCObjectRefBase
{
public:
	bool InputEnabled; // 0x0C: Both constructors initialize as 1

	enum eEInputPriority;

	bool IsInputEnabled() const;
	void EnableInput( bool bEnable);
	void Invalidate();

	// eCInputReceiver interface
	virtual eEInputPriority GetInputPriority() const;                   // 0x60
	virtual int OnAction( const eCInpShared::eSGameKeyMessage&);// 0x64
	virtual int OnKeyboard( const eCInpShared::eSInputMessage&);// 0x68
	virtual int OnMouse( const eCInpShared::eSInputMessage&);   // 0x6C

	static const bCPropertyObjectBase* GetRootObject();
};


inline bool eCInputReceiver::IsInputEnabled() const
{
	return InputEnabled;
}

inline void eCInputReceiver::EnableInput( bool bEnable)
{
	InputEnabled = bEnable;
}

inline void eCInputReceiver::Invalidate()
{
	InputEnabled = true;
}

inline eCInputReceiver::eEInputPriority eCInputReceiver::GetInputPriority() const
{
	return (eCInputReceiver::eEInputPriority)0;
}

inline int eCInputReceiver::OnAction( const eCInpShared::eSGameKeyMessage&)
{
	return -1;
}

inline int eCInputReceiver::OnKeyboard( const eCInpShared::eSInputMessage&)
{
	return -1;
}

inline int eCInputReceiver::OnMouse( const eCInpShared::eSInputMessage&)
{
	return -1;
}