#pragma once

#include "framework.h"

#include "CEvent.h"

class CTrack
{
public:

	BYTE m_type[5];
	
	int m_length;

	CEvent m_event;

	void PrintData();
};
