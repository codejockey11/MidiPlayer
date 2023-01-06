#include "GeneralFunctions.h"

__declspec(dllexport) WCHAR* MBSToWide(const CHAR* s)
{
	mbstowcs_s(&gfsize, gfwcs, 1024, s, strlen(s));

	return gfwcs;
}

__declspec(dllexport) CHAR* WideToMBS(const WCHAR* s)
{
	wcstombs_s(&gfsize, gfstr, 1024, s, wcslen(s));

	return gfstr;
}

__declspec(dllexport) void LoadBigEndian(BYTE* str, BYTE* v, int size, int start)
{
	v += size - 1;

	for (int i = start; i < (start + size); i++)
	{
		*v = str[i];
		v--;
	}
}

__declspec(dllexport) void WriteVarLen(FILE* file, long value)
{
	long buffer = value & 0x7f;

	while ((value >>= 7) > 0)
	{
		buffer <<= 8;
		buffer |= 0x80;
		buffer += (value & 0x7f);
	}

	while (true)
	{
		putc(buffer, file);

		if (buffer & 0x80)
		{
			buffer >>= 8;
		}
		else
		{
			break;
		}
	}
}

__declspec(dllexport) int ReadVarLen(FILE* file)
{
	int value;
	BYTE c;

	if ((value = getc(file)) & 0x80)
	{
		value &= 0x7f;

		do
		{
			value = (value << 7) + ((c = getc(file)) & 0x7f);
		} while (c & 0x80);
	}

	return (value);
}
