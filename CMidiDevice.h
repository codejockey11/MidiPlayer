#pragma once

#include "framework.h"

class CMidiDevice
{
public:

	UINT m_deviceId;

	char m_deviceName[Constants::maxStringLength];

	CMidiDevice(UINT id, char* name);
	
};

