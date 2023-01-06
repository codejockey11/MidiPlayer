#pragma once

#include "framework.h"

class CFont
{
public:

	HFONT s_hFont;

	CFont(HWND hWnd, const char* name, long size, long weight);
	
	~CFont();
};

