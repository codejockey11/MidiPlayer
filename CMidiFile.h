#pragma once

#include "framework.h"

#include "CHeader.h"
#include "CTrack.h"

class CMidiFile
{
public:

	FILE* m_file;

	CHeader m_header;

	CTrack m_track;

	int m_absTime;

	bool LoadFile(const char* file);

private:

	BYTE m_buffer[10];

	void CalculateQuarterNoteTicks();
};

