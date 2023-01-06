#include "CFont.h"


CFont::CFont(HWND hWnd, const char* name, long size, long weight)
{
	const TCHAR* fontName = _T("Tahoma");
	const long nFontSize = 10;

	HDC hdc = GetDC(hWnd);

	LOGFONT logFont = { 0 };
	logFont.lfHeight = -MulDiv(size, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logFont.lfWeight = weight;
	_tcscpy_s(logFont.lfFaceName, name);

	s_hFont = CreateFontIndirect(&logFont);

	ReleaseDC(hWnd, hdc);
}

CFont::~CFont()
{
	DeleteObject(s_hFont);
}
