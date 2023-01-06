#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <shobjidl.h>
#include <CommCtrl.h>
#include <stdio.h>

#include <mmeapi.h>
#pragma comment(lib, "Winmm.lib")

// instead of #define
enum Constants
{
	maxStringLength = 256,
	bufferInSize = 256,

	forceSize = 0xFFFF
};

enum Messages
{
	UpdateInstrumentName = 0x012C	// 300
};

// instead of #define
enum Controls
{
	BTN_OPENFILE = 200,
	EDT_FILENAME,
	BTN_PLAY,
	CBX_INSTRUMENTS,
	BTN_STARTMIDIIN,
	BTN_STOPMIDIIN,
	CBX_MIDIIN,
	CBX_MIDIOUT
};
