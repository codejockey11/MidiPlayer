#pragma once

#include "framework.h"

#include "CMeta.h"

#include "CControllerNames.h"
#include "CGeneralMidiNames.h"

class CEvent
{
public:

	int m_absTime;
	int m_vTime;

	BYTE m_type;

	BYTE m_first;
	BYTE m_second;

	CMeta m_meta;

	CControllerNames m_controllerNames;
	CGeneralMidiNames m_generalMidiNames;

	bool Read(FILE* file);

	void PrintData();
};

