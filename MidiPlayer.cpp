#include "framework.h"

#include "MidiPlayer.h"
#include "CFont.h"
#include "CGeneralMidiNames.h"
#include "CMidiFile.h"
#include "CMidiPort.h"

// Global Variables:
HINSTANCE hInst;

char szTitle[Constants::maxStringLength];
char szWindowClass[Constants::maxStringLength];

FILE* console = nullptr;

HWND buttonOpenFile;
HWND editFileName;
HWND buttonPlay; 
HWND comboBoxInstruments;
HWND buttonStartMidiIn;
HWND buttonStopMidiIn;
HWND comboBoxMidiIn;
HWND comboBoxMidiOut;


CFont* fontTahoma;
CMidiPort* midiPort;

CGeneralMidiNames generalMidiNames;
CGeneralMidiNames::Table instrument;

char  filename[Constants::maxStringLength];
CMidiFile* midiFile;

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
	{
		return (INT_PTR)true;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));

			return (INT_PTR)true;
		}

		break;
	}
	}

	return (INT_PTR)FALSE;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 600, 600, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	buttonOpenFile = CreateWindow(WC_BUTTON, "Open File", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		/* position */ 10, 10,		
		/* size     */ 64, 32,
		hWnd,
		(HMENU)Controls::BTN_OPENFILE,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	editFileName = CreateWindow(WC_EDIT, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
		/* position */ 78, 14,
		/* size     */ 300, 24,
		hWnd,
		(HMENU)Controls::EDT_FILENAME,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	buttonPlay = CreateWindow(WC_BUTTON, "Play File", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		/* position */ 382, 10,
		/* size     */ 64, 32,
		hWnd,
		(HMENU)Controls::BTN_OPENFILE,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	comboBoxInstruments = CreateWindow(WC_COMBOBOX, NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | BS_DEFSPLITBUTTON | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
		/* position */ 10, 46,
		/* size     */ 300, 300,
		hWnd,
		(HMENU)Controls::CBX_INSTRUMENTS,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	buttonStartMidiIn = CreateWindow(WC_BUTTON, "Start Midi", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		/* position */ 10, 82,
		/* size     */ 64, 32,
		hWnd,
		(HMENU)Controls::BTN_STARTMIDIIN,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	buttonStopMidiIn = CreateWindow(WC_BUTTON, "Stop Midi", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		/* position */ 78, 82,
		/* size     */ 64, 32,
		hWnd,
		(HMENU)Controls::BTN_STOPMIDIIN,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	comboBoxMidiIn = CreateWindow(WC_COMBOBOX, NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | BS_DEFSPLITBUTTON | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
		/* position */ 10, 118,
		/* size     */ 200, 300,
		hWnd,
		(HMENU)Controls::CBX_MIDIIN,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	comboBoxMidiOut = CreateWindow(WC_COMBOBOX, NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | BS_DEFSPLITBUTTON | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
		/* position */ 212, 118,
		/* size     */ 200, 300,
		hWnd,
		(HMENU)Controls::CBX_MIDIOUT,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	SendMessage(buttonOpenFile, WM_SETFONT, (WPARAM)fontTahoma->s_hFont, (LPARAM)MAKELONG(true, 0));
	SendMessage(editFileName, WM_SETFONT, (WPARAM)fontTahoma->s_hFont, (LPARAM)MAKELONG(true, 0));
	SendMessage(buttonPlay, WM_SETFONT, (WPARAM)fontTahoma->s_hFont, (LPARAM)MAKELONG(true, 0));
	SendMessage(comboBoxInstruments, WM_SETFONT, (WPARAM)fontTahoma->s_hFont, (LPARAM)MAKELONG(true, 0));
	SendMessage(buttonStartMidiIn, WM_SETFONT, (WPARAM)fontTahoma->s_hFont, (LPARAM)MAKELONG(true, 0));
	SendMessage(buttonStopMidiIn, WM_SETFONT, (WPARAM)fontTahoma->s_hFont, (LPARAM)MAKELONG(true, 0));
	SendMessage(comboBoxMidiIn, WM_SETFONT, (WPARAM)fontTahoma->s_hFont, (LPARAM)MAKELONG(true, 0));
	SendMessage(comboBoxMidiOut, WM_SETFONT, (WPARAM)fontTahoma->s_hFont, (LPARAM)MAKELONG(true, 0));

	for (int i = 0; i < CGeneralMidiNames::instrumentLength; i++)
	{
		SendMessage(comboBoxInstruments, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)(generalMidiNames.instrumentNameTable[i].name));
	}
	
	SendMessage(comboBoxInstruments, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

	CLinkListNode* lln = midiPort->m_deviceInList->list;

	while(lln->element)
	{
		CMidiDevice* d = (CMidiDevice*)lln->element;

		SendMessage(comboBoxMidiIn, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)(d->m_deviceName));

		lln = lln->next;
	}

	SendMessage(comboBoxMidiIn, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

	lln = midiPort->m_deviceOutList->list;

	while (lln->element)
	{
		CMidiDevice* d = (CMidiDevice*)lln->element;

		SendMessage(comboBoxMidiOut, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)(d->m_deviceName));

		lln = lln->next;
	}

	SendMessage(comboBoxMidiOut, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

	UpdateWindow(hWnd);

	ShowWindow(hWnd, nCmdShow);

	return true;
}

void OpenFileDialog()
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			hr = pFileOpen->Show(NULL);

			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;

				hr = pFileOpen->GetResult(&pItem);

				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;

					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					const char* c = WideToMBS(pszFilePath);
					memcpy(filename, c, strlen(c));

					pItem->Release();
				}
			}

			pFileOpen->Release();
		}

		CoUninitialize();
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		AllocConsole();
		
		freopen_s(&console, "CONOUT$", "w", stdout);
		freopen_s(&console, "CONOUT$", "w", stderr);

		fontTahoma = new CFont(hWnd, "Tahoma", 10, FW_NORMAL);

		midiPort = new CMidiPort(hWnd);

		break;
	}
	case Messages::UpdateInstrumentName:
	{
		const CGeneralMidiNames::Table* n = generalMidiNames.GetInstrumentName(LOBYTE(wParam));

		SendMessage(comboBoxInstruments, (UINT)CB_SETCURSEL, (WPARAM)n->number, (LPARAM)0);

		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_ABOUT:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);

			break;
		}
		case IDM_EXIT:
		{
			DestroyWindow(hWnd);

			break;
		}
		case Controls::BTN_OPENFILE:
		{
			OpenFileDialog();

			SetWindowText(editFileName, filename);

			midiFile = new CMidiFile();
			midiFile->LoadFile(filename);

			break;
		}
		case Controls::CBX_INSTRUMENTS:
		{
			if (HIWORD(wParam) == CBN_CLOSEUP)
			{
				int index = (int)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

				instrument = generalMidiNames.instrumentNameTable[index];

				midiPort->m_midiMessageBuffer[0] = 0xC0;
				midiPort->m_midiMessageBuffer[1] = instrument.number;

				midiPort->m_midiHdr.dwBufferLength = 2;

				midiPort->m_mmr = midiOutLongMsg(midiPort->m_midiOut, &midiPort->m_midiHdr, sizeof(MIDIHDR));
			}

			break;
		}
		case Controls::BTN_STARTMIDIIN:
		{
			midiPort->StartMidiIn();

			break;
		}
		case Controls::BTN_STOPMIDIIN:
		{
			midiPort->StopMidiIn();

			break;
		}
		case Controls::CBX_MIDIIN:
		{
			if (HIWORD(wParam) == CBN_CLOSEUP)
			{
				int index = (int)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

				CLinkListNode* i = midiPort->m_deviceInList->Search(index);

				if (i != nullptr)
				{
					midiPort->StopMidiIn();
					midiPort->CloseMidiIn();

					CMidiDevice* d = (CMidiDevice*)i->element;

					midiPort->OpenMidiIn(d->m_deviceId);
					midiPort->StartMidiIn();
				}
			}

			break;
		}
		case Controls::CBX_MIDIOUT:
		{
			if (HIWORD(wParam) == CBN_CLOSEUP)
			{
				int index = (int)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

				CLinkListNode* i = midiPort->m_deviceOutList->Search(index);

				if (i != nullptr)
				{
					midiPort->StopMidiIn();
					midiPort->CloseMidiOut();

					CMidiDevice* d = (CMidiDevice*)i->element;

					midiPort->OpenMidiOut(d->m_deviceId);
				}
			}

			break;
		}
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		}

		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);
		
		EndPaint(hWnd, &ps);

		break;
	}

	case WM_DESTROY:
	{
		delete fontTahoma;

		delete midiFile;

		delete midiPort;

		if (console)
		{
			fclose(console);
		}

		FreeConsole();

		PostQuitMessage(0);

		break;
	}

	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}

	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, Constants::maxStringLength);
	LoadString(hInstance, IDC_MIDIPLAYER, szWindowClass, Constants::maxStringLength);
	
	WNDCLASSEX wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIDIPLAYER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MIDIPLAYER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MIDIPLAYER));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}
