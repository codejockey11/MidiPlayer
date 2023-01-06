#pragma once

#include "framework.h"

#include "CMidiDevice.h"
#include "CLinkList.h"

class CMidiPort
{
public:

	HWND		m_hWnd;

	UINT        m_deviceCount;

	MMRESULT	m_mmr;
	HMIDI		m_midi;
	HMIDIIN		m_midiIn;
	HMIDIOUT	m_midiOut;
	HMIDISTRM	m_midiStrm;
	MIDIINCAPS	m_midiInCaps;
	MIDIOUTCAPS	m_midiOutCaps;
	UINT		m_midiInDeviceId;
	UINT		m_midiOutDeviceId;
	MIDIHDR		m_midiHdr;

	BYTE        m_midiMessageBuffer[Constants::bufferInSize];

	CLinkList*  m_deviceInList;
	CLinkList*  m_deviceOutList;

	CMidiPort(HWND hWnd);
	~CMidiPort();

	void OpenMidiIn(UINT id);
	void CloseMidiIn();
	void StartMidiIn();
	void StopMidiIn();

	void OpenMidiOut(UINT id);
	void CloseMidiOut();
};
