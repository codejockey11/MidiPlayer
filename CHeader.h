#pragma once

#include "framework.h"

class CHeader
{
public:

	BYTE m_type[5];

	int	m_length;

	short m_format;
	short m_trackCount;
	short m_division;

	int	m_ticksPerQuarterNote;

	void PrintData();
};
