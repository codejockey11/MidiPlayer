#include "CString.h"

CString::CString()
{
	memset(this, 0x00, sizeof(CString));
}

CString::CString(const char* s)
{
	memset(this, 0x00, sizeof(CString));

	if (s == NULL)
	{
		return;
	}

	length = (UINT)strlen(s);

	text = new char[(UINT64)length + 1];

	memset(text, 0x00, (UINT64)length + 1);

	memcpy(text, s, length);
}

CString::CString(UINT l)
{
	memset(this, 0x00, sizeof(CString));

	length = l;

	text = new char[(UINT64)length + 1];

	memset(text, 0x00, (UINT64)length + 1);
}

CString::~CString()
{
	delete[] text;
}

void CString::Clear()
{
	memset(text, 0x00, length);
}

void CString::Format(const char* format, ...)
{
	va_start(argptr, format);

	Clear();

	vsprintf_s(text, length, format, argptr);

	va_end(argptr);
}