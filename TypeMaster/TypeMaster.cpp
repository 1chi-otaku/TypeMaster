#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"comctl32")

#pragma warning(disable : 4996)

using namespace std;


BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}


HWND hEditControl;
HWND hEditControl2;
HWND hEditControl3; 
PNOTIFYICONDATA pNID;
HICON hIcon;


TCHAR* str = new TCHAR[_tcslen(TEXT("The universe has a beginning, but no end. Infinity. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist."))+1];
int missesCount = 0;

void DeleteFirstCharacter() {
	int size = _tcslen(str);
	TCHAR* str2 = new TCHAR[size];
	int i = 0;
	int j = 0;
	while (j < size)
	{
		if (i == 0) {
			i++;
			continue;
		}
		str2[j] = str[i];
		i++;
		j++;
	}
	str2[_tcslen(str2)] = '\0';
	delete[]str;
	str = str2;
	SetWindowText(hEditControl2, str);
}

void ButtonPressed(TCHAR symbol) {
	TCHAR buffer3[5];
	wsprintf(buffer3, TEXT("%d"), int(symbol));
	
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_APP:
		if (lParam == WM_LBUTTONDBLCLK)
		{
			Shell_NotifyIcon(NIM_DELETE, pNID); // Deleteing icon from
			ShowWindow(hWnd, SW_NORMAL); // Recreate window
			SetForegroundWindow(hWnd); 
		}
		break;

	case WM_CLOSE:
		delete[] str;
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG: {
		PlaySoundA((LPCSTR)"quest.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(10);
		TCHAR buffer[512] = TEXT("The universe has a beginning, but no end. Infinity. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist.");
		wsprintf(str, buffer);
		hEditControl = GetDlgItem(hWnd, IDC_EDIT4);
		hEditControl2 = GetDlgItem(hWnd, IDC_EDIT7);
		hEditControl3 = GetDlgItem(hWnd, IDC_EDIT6);
		SetWindowText(hEditControl2, str);
		pNID = new NOTIFYICONDATA;
		HINSTANCE hInst = GetModuleHandle(NULL);




		hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // upload an icon
		SetClassLong(hWnd, -14, LONG(hIcon)); // install an icon
		memset(pNID, 0, sizeof(NOTIFYICONDATA)); 
		pNID->cbSize = sizeof(NOTIFYICONDATA); 
		pNID->hIcon = hIcon; 
		pNID->hWnd = hWnd; 
		// tray
		lstrcpy(pNID->szTip, TEXT("TypeMaster")); 
		pNID->uCallbackMessage = WM_APP;
		pNID->uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE | NIF_INFO;
		lstrcpy(pNID->szInfo, TEXT("Type Master is hidden."));
		lstrcpy(pNID->szInfoTitle, TEXT("TypeMaster"));
		pNID->uID = WM_USER;
		return TRUE;

	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_HIDE:
			ShowWindow(hWnd, SW_HIDE); // Hides window
			Shell_NotifyIcon(NIM_ADD, pNID); // Adds icon to the tray
			break;

		case IDC_EDIT4:
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				
				TCHAR buffer[512];
				TCHAR buffer2[512];
				GetWindowText(hEditControl, buffer2, 512);
				GetWindowText(hEditControl2, buffer, 512);
				int size = _tcslen(buffer2);
				ButtonPressed(buffer2[size - 1]);

				if (_tcslen(buffer) == 1) {
					PlaySoundA((LPCSTR)"questwin.wav", NULL, SND_FILENAME | SND_ASYNC);
					MessageBox(hWnd, TEXT("You won!"), TEXT("VICTORY!"), MB_OK | MB_ICONINFORMATION);
				}

				if (_tcslen(buffer) > 0) {
					if (buffer2[size - 1] == buffer[0]) {
						DeleteFirstCharacter();
					}
					else {
						if(buffer2[size - 1] != ' ')
							missesCount++;

						wsprintf(buffer, TEXT("%d"), missesCount);
						SetWindowText(hEditControl3, buffer);
					}
				}

				return TRUE;
			}
		}
	}
	return FALSE;
}
	
	

	