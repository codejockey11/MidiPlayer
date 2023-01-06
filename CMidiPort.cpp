#include "CMidiPort.h"

void CALLBACK midiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	CMidiPort* port = (CMidiPort*)dwInstance;

	switch (wMsg)
	{
	case MIM_OPEN:
	{
		printf("MIM_OPEN: %i hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx\n", wMsg,
			HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
			HIBYTE(HIWORD(dwParam2)), LOBYTE(HIWORD(dwParam2)), HIBYTE(LOWORD(dwParam2)), LOBYTE(LOWORD(dwParam2)));

		break;
	}
	case MIM_CLOSE:
	{
		printf("MIM_CLOSE: %i hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx\n", wMsg,
			HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
			HIBYTE(HIWORD(dwParam2)), LOBYTE(HIWORD(dwParam2)), HIBYTE(LOWORD(dwParam2)), LOBYTE(LOWORD(dwParam2)));

		break;
	}
	case MIM_DATA:
	{
		// +9 for drums
		port->m_midiMessageBuffer[0] = LOBYTE(LOWORD(dwParam1));

		// for some reason my yamaha is sending drum events on channel 8 sometimes
		if (LOBYTE(LOWORD(dwParam1)) == 0x98)
		{
			port->m_midiMessageBuffer[0] += 1;
		}
		port->m_midiMessageBuffer[1] = HIBYTE(LOWORD(dwParam1));
		port->m_midiMessageBuffer[2] = LOBYTE(HIWORD(dwParam1));

		port->m_midiHdr.dwBufferLength = 3;

		port->m_mmr = midiOutLongMsg(port->m_midiOut, &port->m_midiHdr, sizeof(MIDIHDR));

		if ((port->m_midiMessageBuffer[0] >= 0x90) && (port->m_midiMessageBuffer[0] <= 0x9F))
		{
			printf("MIM_DATA: %i Note On hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx %i\n", wMsg,
				HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
				(int)dwParam2);
		}

		if ((port->m_midiMessageBuffer[0] >= 0xC0) && (port->m_midiMessageBuffer[0] <= 0xCF))
		{
			printf("MIM_DATA: %i Note On hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx %i\n", wMsg,
				HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
				(int)dwParam2);

			SendMessage(port->m_hWnd, (UINT)Messages::UpdateInstrumentName, (WPARAM)port->m_midiMessageBuffer[1], (LPARAM)0);
		}

		break;
	}
	case MIM_LONGDATA:
	{
		printf("MIM_LONGDATA: %i hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx\n", wMsg,
			HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
			HIBYTE(HIWORD(dwParam2)), LOBYTE(HIWORD(dwParam2)), HIBYTE(LOWORD(dwParam2)), LOBYTE(LOWORD(dwParam2)));

		break;
	}
	case MIM_ERROR:
	{
		printf("MIM_ERROR: %i hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx\n", wMsg,
			HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
			HIBYTE(HIWORD(dwParam2)), LOBYTE(HIWORD(dwParam2)), HIBYTE(LOWORD(dwParam2)), LOBYTE(LOWORD(dwParam2)));

		break;
	}
	case MIM_LONGERROR:
	{
		printf("MIM_LONGERROR: %i hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx\n", wMsg,
			HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
			HIBYTE(HIWORD(dwParam2)), LOBYTE(HIWORD(dwParam2)), HIBYTE(LOWORD(dwParam2)), LOBYTE(LOWORD(dwParam2)));

		break;
	}
	}
}

void CALLBACK midiOutProc(HMIDIOUT hMidiOut, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	switch (wMsg)
	{
	case MOM_OPEN:
	{
		printf("MOM_OPEN: %i hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx\n", wMsg,
			HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
			HIBYTE(HIWORD(dwParam2)), LOBYTE(HIWORD(dwParam2)), HIBYTE(LOWORD(dwParam2)), LOBYTE(LOWORD(dwParam2)));

		break;
	}
	case MOM_CLOSE:
	{
		printf("MOM_CLOSE: %i hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx\n", wMsg,
			HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
			HIBYTE(HIWORD(dwParam2)), LOBYTE(HIWORD(dwParam2)), HIBYTE(LOWORD(dwParam2)), LOBYTE(LOWORD(dwParam2)));

		break;
	}
	case MOM_DONE:
	{
		//printf("MOM_DONE: %i hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx hh0x%02hhx lh0x%02hhx hl0x%02hhx ll0x%02hhx\n", wMsg,
			//HIBYTE(HIWORD(dwParam1)), LOBYTE(HIWORD(dwParam1)), HIBYTE(LOWORD(dwParam1)), LOBYTE(LOWORD(dwParam1)),
			//HIBYTE(HIWORD(dwParam2)), LOBYTE(HIWORD(dwParam2)), HIBYTE(LOWORD(dwParam2)), LOBYTE(LOWORD(dwParam2)));

		break;
	}
	}

	return;
}

void CALLBACK midiStrmProc(HMIDIOUT hMidiOut, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	printf("midiStrmProc: %i\n", wMsg);

	return;
}

CMidiPort::CMidiPort(HWND hWnd)
{
	memset(this, 0x00, sizeof(CMidiPort));

	m_hWnd = hWnd;

	m_deviceInList = new CLinkList;
	m_deviceOutList = new CLinkList;

	m_deviceCount = midiInGetNumDevs();

	for (UINT i = 0; i < m_deviceCount; i++)
	{
		m_mmr = midiInGetDevCaps(i, &m_midiInCaps, sizeof(MIDIINCAPS));

		CMidiDevice* d = new CMidiDevice(i, m_midiInCaps.szPname);

		m_deviceInList->Add((void*)d, i);
	}

	m_deviceCount = midiOutGetNumDevs();

	for (UINT i = 0; i < m_deviceCount; i++)
	{
		m_mmr = midiOutGetDevCaps(i, &m_midiOutCaps, sizeof(MIDIOUTCAPS));

		CMidiDevice* d = new CMidiDevice(i, m_midiOutCaps.szPname);

		m_deviceOutList->Add((void*)d, i);
	}

	m_mmr = midiOutGetDevCaps(MIDI_MAPPER, &m_midiOutCaps, sizeof(MIDIOUTCAPS));

	CMidiDevice* d = new CMidiDevice(MIDI_MAPPER, m_midiOutCaps.szPname);

	m_deviceOutList->Add((void*)d, MIDI_MAPPER);

	

	CMidiPort::OpenMidiIn(0);
	CMidiPort::OpenMidiOut(0);
}

CMidiPort::~CMidiPort()
{
	delete m_deviceInList;
	delete m_deviceOutList;

	m_mmr = midiInStop(m_midiIn);

	m_mmr = midiInClose(m_midiIn);

	m_mmr = midiOutClose(m_midiOut);
}

void CMidiPort::OpenMidiIn(UINT id)
{
	m_mmr = midiInOpen(&m_midiIn, id, (DWORD_PTR)midiInProc, (DWORD_PTR)this, CALLBACK_FUNCTION);
}

void CMidiPort::CloseMidiIn()
{
	m_mmr = midiInClose(m_midiIn);
}

void CMidiPort::StartMidiIn()
{
	m_mmr = midiInStart(m_midiIn);
}

void CMidiPort::StopMidiIn()
{
	m_mmr = midiInStop(m_midiIn);
}

void CMidiPort::OpenMidiOut(UINT id)
{
	m_mmr = midiOutOpen(&m_midiOut, id, (DWORD_PTR)midiOutProc, (DWORD_PTR)this, CALLBACK_FUNCTION);

	memset(&m_midiHdr, 0x00, sizeof(MIDIHDR));

	m_midiHdr.lpData = (CHAR*)m_midiMessageBuffer;

	m_mmr = midiOutPrepareHeader(m_midiOut, &m_midiHdr, sizeof(MIDIHDR));
}

void CMidiPort::CloseMidiOut()
{
	m_mmr = midiOutClose(m_midiOut);
}
