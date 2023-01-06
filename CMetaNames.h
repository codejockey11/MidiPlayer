#pragma once

#include "framework.h"

class CMetaNames
{
public:

	struct Table
	{
		BYTE event;

		const char* name;
	};

	static const int length = 31;

	const Table eventNameTable[length] =
	{
		0x00, { "Sequence number                " },
		0x01, { "Text event                     " },
		0x02, { "Copyright notice               " },
		0x03, { "Sequence or track name         " },
		0x04, { "Instrument name                " },
		0x05, { "Lyric text                     " },
		0x06, { "Marker text                    " },
		0x07, { "Cue point                      " },
		0x20, { "Channel prefix assignment      " },
		0x21, { "Port or cable number           " },
		0x2F, { "End of track                   " },
		0x51, { "Tempo setting                  " },
		0x54, { "SMPTE offset                   " },
		0x58, { "Time signature                 " },
		0x59, { "Key signature                  " },
		0x7F, { "Manufacturer-specific event    " },
		0xF1, { "Time code                      " },
		0xF2, { "Song position pointer          " },
		0xF3, { "Song select                    " },
		0xF4, { "(Unused)                       " },
		0xF5, { "(Unused)                       " },
		0xF6, { "Tune request                   " },
		0xF7, { "End system exclusive event(EOX)" },
		0xF8, { "Timing clock                   " },
		0xF9, { "(Unused)                       " },
		0xFA, { "Start playback                 " },
		0xFB, { "Continue playback              " },
		0xFC, { "Stop playback                  " },
		0xFD, { "(Unused)                       " },
		0xFE, { "Active sensing                 " },
		0xFF, { "System reset                   " }
	};

	const Table* GetName(BYTE s);
};
