#pragma once

#include "framework.h"

#include "CMetaNames.h"

class CMeta
{
public:

	BYTE m_type;

	int	m_vLength;

	BYTE m_data[256];

	CMetaNames m_metaNames;

	bool Read(FILE* file);

	void PrintData();
};
