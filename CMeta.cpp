#include "CMeta.h"

int ReadVarLen(FILE* file);

bool CMeta::Read(FILE* file)
{
	fread_s(&m_type, 1, sizeof(BYTE), 1, file);

	m_vLength = ReadVarLen(file);

	memset(m_data, 0x00, 256);

	// end-of-track
	if (m_type == 0x2F)
	{
		return false;
	}

	fread_s(m_data, 256, sizeof(BYTE), m_vLength, file);

	return true;
}

void CMeta::PrintData()
{
	const CMetaNames::Table* n = m_metaNames.GetName(m_type);

	if (n == nullptr)
	{
		printf("\t0x%02x\t0x%02x\tNo event name", m_vLength, m_type);

		return;
	}
	else
	{
		printf("\t0x%02x\t0x%02x\t%s\t", m_vLength, m_type, n->name);
	}

	if (m_vLength == 0)
	{
		printf("\n");

		return;
	}

	for (int i = 0; i < m_vLength; i++)
	{
		printf("0x%02x ", m_data[i]);
	}

	printf("||");

	for (int i = 0; i < m_vLength; i++)
	{
		printf("%c", (char)m_data[i]);
	}
}
