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


HWND hEditControl, hEditControl2, hEditControl3, hEditControl4, hPressedButton;
HWND hButtonStart;
PNOTIFYICONDATA pNID;
HICON hIcon;
BOOL FLAG = TRUE;
HANDLE hThread;

TCHAR* str = new TCHAR[_tcslen(TEXT("The universe has a beginning, but no end. Infinity. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist."))+1];
int missesCount = -1;
int characterAmount = 0;

DWORD WINAPI Timer(LPVOID lp)
{
	int minutes = 0;
	int seconds = 0;
	TCHAR tchar[16];
	while (FLAG == TRUE)
	{
		if (seconds == 60) {
			seconds = 0;
			minutes++;
		}
		wsprintf(tchar, TEXT("         %d:%d"), minutes, seconds);
		SetWindowText(hEditControl3, tchar);
		Sleep(1000);
		seconds++;
	}
	FLAG = FALSE;
	return 0;
}
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
void ButtonPressed(HWND hWnd, TCHAR symbol) {
	EnableWindow(hPressedButton, FALSE);
	int identificator;
	if (int(symbol) >= 65 && int(symbol) <= 90 || int(symbol) == 32)
		identificator = 0;
	else if (int(symbol) >= 97 && int(symbol) <= 122)
		identificator = 32;
	else
		return;
	hPressedButton = GetDlgItem(hWnd, (10000 - identificator + int(symbol)));
	EnableWindow(hPressedButton, TRUE);
}
void ClearType() {
	TerminateThread(hThread, 0);
	hThread = CreateThread(NULL, 0, Timer, hEditControl3, 0, NULL);
	EnableWindow(hButtonStart, FALSE);
	EnableWindow(hEditControl3, TRUE);
	EnableWindow(hEditControl, TRUE);
	EnableWindow(hEditControl2, TRUE);
	EnableWindow(hEditControl4, TRUE);
	delete[] str;
	str = new TCHAR[_tcslen(TEXT("The universe has a beginning, but no end. Infinity. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist.")) + 1];
	TCHAR buffer[512] = TEXT("The universe has a beginning, but no end. Infinity. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist.");
	wsprintf(str, buffer);

	SetWindowText(hEditControl2, str);
	SetWindowText(hEditControl4, TEXT("Mistakes - 0\r\nCharacters - 0"));
	SetWindowText(hEditControl, TEXT(""));

	PlaySoundA((LPCSTR)"quest.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

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
		hEditControl = GetDlgItem(hWnd, IDC_EDIT4);
		hEditControl2 = GetDlgItem(hWnd, IDC_EDIT7);
		hEditControl3 = GetDlgItem(hWnd, IDC_EDIT6);
		hEditControl4 = GetDlgItem(hWnd, IDC_EDIT2);
		hButtonStart = GetDlgItem(hWnd, IDC_START);

		TCHAR buffer[512] = TEXT("The universe has a beginning, but no end. Infinity. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist.");
		wsprintf(str, buffer);
		SetWindowText(hEditControl2, str);
		SetWindowText(hEditControl4, TEXT("Mistakes - 0\r\nCharacters - 0"));
		pNID = new NOTIFYICONDATA;
		HINSTANCE hInst = GetModuleHandle(NULL);
		EnableWindow(hEditControl, FALSE);
		EnableWindow(hEditControl2, FALSE);
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

		SendMessage(hEditControl2, PBM_SETRANGE, 0, MAKELPARAM(0, 20));
		SendMessage(hEditControl2, PBM_SETSTEP, 1, 0);
		SendMessage(hEditControl2, PBM_SETPOS, 0, 0);
		SendMessage(hEditControl2, PBM_SETBARCOLOR, 0, LPARAM(RGB(215, 215, 215)));
		
		return TRUE;

	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDC_HIDE:
			ShowWindow(hWnd, SW_HIDE); // Hides window
			Shell_NotifyIcon(NIM_ADD, pNID); // Adds icon to the tray
			break;
		case IDC_START: {
			ClearType();
			break;
		}
			

		case IDC_EDIT4:
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				
				TCHAR buffer[512];
				TCHAR buffer2[512];
				GetWindowText(hEditControl, buffer2, 512);
				GetWindowText(hEditControl2, buffer, 512);
				int size = _tcslen(buffer2);
				ButtonPressed(hWnd, buffer2[size - 1]);

				if (_tcslen(buffer) == 1) {
					FLAG = FALSE;
					PlaySoundA((LPCSTR)"questwin.wav", NULL, SND_FILENAME | SND_ASYNC);
					MessageBox(hWnd, TEXT("You won!"), TEXT("VICTORY!"), MB_OK | MB_ICONINFORMATION);
					EnableWindow(hButtonStart, TRUE);
					EnableWindow(hEditControl3, FALSE);
					EnableWindow(hEditControl, FALSE);
					EnableWindow(hEditControl2, FALSE);
					EnableWindow(hEditControl4, FALSE);
					FLAG = TRUE;
					characterAmount = -1;
					missesCount = -1;
					SetWindowText(hEditControl4, TEXT("Mistakes - 0\r\nCharacters - 0"));
				}


				if (_tcslen(buffer) > 0) {
					if (buffer2[size - 1] == buffer[0]) {
						DeleteFirstCharacter();
						characterAmount++;
					}
					else {
						if(buffer2[size - 1] != ' ')
							missesCount++;
					}
				}
				wsprintf(buffer, TEXT("Mistakes - %d\r\nCharacters - %d"), missesCount, characterAmount);
				SetWindowText(hEditControl4, buffer);

				return TRUE;
			}
		}
	}
	return FALSE;
}
	
	

	