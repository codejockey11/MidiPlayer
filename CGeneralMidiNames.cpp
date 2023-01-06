#include "CGeneralMidiNames.h"

const CGeneralMidiNames::Table* CGeneralMidiNames::GetInstrumentName(BYTE s)
{
	for (int i = 0; i < instrumentLength; i++)
	{
		if (instrumentNameTable[i].number == s)
		{
			return &instrumentNameTable[i];
		}
	}

	return nullptr;
}

const CGeneralMidiNames::Table* CGeneralMidiNames::GetDrumName(BYTE s)
{
	for (int i = 0; i < drumLength; i++)
	{
		if (drumNameTable[i].number == s)
		{
			return &drumNameTable[i];
		}
	}

	return nullptr;
}

const CGeneralMidiNames::Table* CGeneralMidiNames::GetDrumNoteName(BYTE s)
{
	for (int i = 0; i < drumNoteLength; i++)
	{
		if (drumNoteNameTable[i].number == s)
		{
			return &drumNoteNameTable[i];
		}
	}

	return nullptr;
}

const CGeneralMidiNames::NoteTable* CGeneralMidiNames::GetNoteName(BYTE s)
{
	for (int i = 0; i < noteLength; i++)
	{
		if (noteNameTable[i].number == s)
		{
			return &noteNameTable[i];
		}
	}

	return nullptr;
}
