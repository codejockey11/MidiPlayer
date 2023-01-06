#include "CControllerNames.h"

const CControllerNames::Table* CControllerNames::GetName(BYTE s)
{
	for (int i = 0; i < length; i++)
	{
		if (eventNameTable[i].event == s)
		{
			return &eventNameTable[i];
		}
	}

	return nullptr;
}
