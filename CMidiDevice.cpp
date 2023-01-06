#include "CMidiDevice.h"

CMidiDevice::CMidiDevice(UINT id, char* name)
{
	memset(this, 0x00, sizeof(CMidiDevice));

	m_deviceId = id;

	memcpy_s(m_deviceName, Constants::maxStringLength, name, strlen(name));
}
