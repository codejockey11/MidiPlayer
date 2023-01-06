#pragma once

#include "framework.h"

class CString
{
public:

	CString();

	CString(const char* s);

	CString(UINT l);

	~CString();

	UINT GetLength() { return length; }

	char* GetText() { return text; }

	void Clear();

	void Format(const char* format, ...);

private:

	UINT length;

	char* text;

	int l;

	char* t;

	va_list	argptr;
};
