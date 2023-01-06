#include "CHeader.h"

void CHeader::PrintData()
{
	printf("Header %s", m_type);
	printf("\nlength %i", m_length);
	printf("\nformat %i", m_format);
	printf("\ntrackCount %i", m_trackCount);
	printf("\ndivision %i", m_division);
}
