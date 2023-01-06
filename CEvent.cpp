#include "CEvent.h"

int ReadVarLen(FILE* file);

bool CEvent::Read(FILE* file)
{
	m_vTime = ReadVarLen(file);

	fread_s(&m_type, 1, sizeof(BYTE), 1, file);

	if (m_type == 0xFF)
	{
		if (m_meta.Read(file))
		{
			return true;
		}

		return false;
	}

	// This is rare so I skipped it
	if (m_type == 0xF0)
	{
		printf("File contains SysEx Event");

		return false;
	}

	BYTE res = m_type >> 4;
	res = res << 4;

	// see CControllerNames::Table::eventNameTable for complete list
	switch (res)
	{
		// Two values in event
	case 0x80:
	case 0x90:
	case 0xA0:
	case 0xB0:
	case 0xE0:
	{
		fread_s(&m_first, 1, sizeof(BYTE), 1, file);
		fread_s(&m_second, 1, sizeof(BYTE), 1, file);

		break;
	}

	// Single value in event
	default:
	{
		fread_s(&m_first, 1, sizeof(BYTE), 1, file);

		m_second = 0x00;

		break;
	}
	}

	return true;

}

void CEvent::PrintData()
{
	printf("\n%08i\t%08i\t0x%02x", m_absTime, m_vTime, m_type);

	if (m_type == 0xFF)
	{
		m_meta.PrintData();

		return;
	}

	const CControllerNames::Table* n = m_controllerNames.GetName(m_type);

	if (n == nullptr)
	{
		printf("\tNo Controller Name");

		return;
	}

	printf("\t%s", n->name);

	if (n->values == 0x01)
	{
		printf("\t0x%02x", m_first);
	}
	
	if (n->values == 0x02)
	{
		printf("\t0x%02x\t0x%02x", m_first, m_second);
	}

	if (m_type == 0x99 || m_type == 0x89)
	{
		const CGeneralMidiNames::Table* n = m_generalMidiNames.GetDrumNoteName(m_first);

		printf("\t%s", n->name);
	}
	else if (m_type >= 0x80 && m_type < 0xA0)
	{
		const CGeneralMidiNames::NoteTable* n = m_generalMidiNames.GetNoteName(m_first);

		printf("\t%s", n->name);
	}

	if (m_type >= 0xC0 && m_type < 0xD0)
	{
		const CGeneralMidiNames::Table* n;

		if (m_type == 0xC9)
		{
			n = m_generalMidiNames.GetDrumName(m_first);
		}
		else
		{
			n = m_generalMidiNames.GetInstrumentName(m_first);
		}

		printf("\t%s", n->name);
	}
}
