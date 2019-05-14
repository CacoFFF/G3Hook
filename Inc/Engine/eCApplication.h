#pragma once


class eCApplication
{
public:
	const struct eSSetupEngine& GetEngineSetup() const; //lea     eax, [ecx+98h]

	static eCApplication& __stdcall GetInstance();
};
