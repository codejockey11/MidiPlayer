#include "CMidiFile.h"

void LoadBigEndian(BYTE* str, BYTE* v, int size, int start);
void WriteVarLen(FILE* file, long value);
int ReadVarLen(FILE* file);

bool CMidiFile::LoadFile(const char* file)
{
	errno_t result = fopen_s(&m_file, file, "rb");

	if (result != 0)
	{
		return false;
	}

	while (fread_s(m_header.m_type, 4, sizeof(BYTE), 4, m_file))
	{
		if (m_header.m_type[0] == 'M' && m_header.m_type[1] == 'T' && m_header.m_type[2] == 'h' && m_header.m_type[3] == 'd')
		{
			fread_s(m_buffer, 10, sizeof(BYTE), 10, m_file);

			LoadBigEndian(m_buffer, (BYTE*)&m_header.m_length, 4, 0);
			LoadBigEndian(m_buffer, (BYTE*)&m_header.m_format, 2, 4);
			LoadBigEndian(m_buffer, (BYTE*)&m_header.m_trackCount, 2, 6);
			LoadBigEndian(m_buffer, (BYTE*)&m_header.m_division, 2, 8);

			CalculateQuarterNoteTicks();

			m_header.PrintData();
		}
		else if (m_header.m_type[0] == 'M' && m_header.m_type[1] == 'T' && m_header.m_type[2] == 'r' && m_header.m_type[3] == 'k')
		{
			// reading size of entire track chunk
			fread_s(m_buffer, 4, sizeof(BYTE), 4, m_file);

			LoadBigEndian(m_buffer, (BYTE*)&m_track.m_length, 4, 0);

			bool processingTrack = true;

			m_absTime = 0;

			while (processingTrack)
			{
				processingTrack = m_track.m_event.Read(m_file);

				m_absTime += m_track.m_event.m_vTime;
				m_track.m_event.m_absTime = m_absTime;

				m_track.m_event.PrintData();
			}
		}
		else
		{
			printf("\nGarbage info found");
		}
	}

	return true;
}

void CMidiFile::CalculateQuarterNoteTicks()
{
	byte res = m_header.m_division >> 15;
	// SMPTE and MIDI time code
	if ((res) == 1)
	{
		BYTE format = 0x00;
		BYTE ticksPerFrame = 0x00;

		BYTE* a = (BYTE*)&m_header.m_division;
		BYTE* f = &format;
		BYTE* t = &ticksPerFrame;

		// extract left part of division
		*f = a[1];

		// extract right part of division
		*t = a[0];

		// 2's compliment left hand of division
		format = 0xFF - format + 1;

		int framesPerSecond = 0;

		//-24, -25, -29, or -30
		switch (format)
		{
		case 24:
		{
			framesPerSecond = 24;

			break;
		}
		case 25:
		{
			framesPerSecond = 25;

			break;
		}
		case 29:
		{
			framesPerSecond = 29;

			break;
		}
		case 30:
		{
			framesPerSecond = 30;

			break;
		}
		default:
		{
			printf("\nCheck smpte programming");

			break;
		}
		}

		m_header.m_ticksPerQuarterNote = framesPerSecond * ticksPerFrame;
	}
	else
	{
		m_header.m_ticksPerQuarterNote = m_header.m_division;
	}
}
