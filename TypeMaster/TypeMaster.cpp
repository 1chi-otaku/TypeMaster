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
BOOL isActive = TRUE;
HANDLE hThread;
//Initialization of the input string and variables for displaying statistics.
TCHAR* str = new TCHAR[_tcslen(TEXT("The universe has a beginning, but no end. Infinity. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist."))+1];
int missesCount = -1;
int characterAmount = 0;
const int BUFFERLEN = 256;

DWORD WINAPI Timer(LPVOID lp)			//Starts a timer until the string is completely written.
{
	int seconds = 0, minutes = 0;		
	TCHAR tchar[16];					
	while (isActive == TRUE)			//Calculates timer using Sleep function.
	{
		if (seconds == 60) {
			seconds = 0;
			minutes++;
		}
		wsprintf(tchar, TEXT("      %d:%d"), minutes, seconds);		//Forms tchar string every second and sends it to 'time edit control'.
		SetWindowText(hEditControl3, tchar);
		Sleep(1000);
		seconds++;
	}
	isActive = TRUE;												//Returns flag to the true state, so the timer could work again.
	return 0;
}

void DeleteFirstCharacter() { //Handles the logic to remove the first element from the input string if the input was valid.
	int size = _tcslen(str);					//Taking current size of input string.
	TCHAR* str2 = new TCHAR[size];				//Allocating memory for temporary string.
	int i = 0, j = 0;
	while (j < size)							//Shifts all characters one element to the beginning.
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
	delete[]str;								//Deleting previous string memory.
	str = str2;									//Moving the pointer.
	SetWindowText(hEditControl2, str);			//Sends current state of string to edit control.
}

void ButtonPressed(HWND hWnd, TCHAR symbol) { //Calculates what button was pressed in order to visualize it on the virtual keyboard.
	EnableWindow(hPressedButton, FALSE);											//Disabling the previous key.
	int identificator;																			//A variable that must close the 'gap' between uppercase and lowercase letters in order to be processed correctly.
	if (int(symbol) >= 65 && int(symbol) <= 90 || int(symbol) == 32)							//If the last symbol is not uppercase.
		identificator = 0;																		//There will be no gap.
	else if (int(symbol) >= 97 && int(symbol) <= 122)											//If the last symbol is uppercase.
		identificator = 32;																		//ASCII gap between uppercase and lowercase is 32.
	else
		return;
	hPressedButton = GetDlgItem(hWnd, (10000 - identificator + int(symbol)));		//Getting HWND of the pressed button.
	EnableWindow(hPressedButton, TRUE);												//Enabling the current key.
}

void ClearType() {//Clears edit controls and starts new game.
	TerminateThread(hThread, 0);																											//Terminating Time process.
	hThread = CreateThread(NULL, 0, Timer, hEditControl3, 0, NULL);			//Starting new Time process.
	//Enabling edit control and disabling 'Start' button.
	EnableWindow(hButtonStart, FALSE);
	EnableWindow(hEditControl3, TRUE);
	EnableWindow(hEditControl, TRUE);
	EnableWindow(hEditControl2, TRUE);
	EnableWindow(hEditControl4, TRUE);

	//Dynamic memory handling logic.
	delete[] str;
	str = new TCHAR[_tcslen(TEXT("The universe has a beginning, but no end. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist.")) + 1];
	TCHAR buffer[512] = TEXT("The universe has a beginning, but no end. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist.");
	wsprintf(str, buffer);

	//Sets default text to the edit controls.
	SetWindowText(hEditControl2, str);
	SetWindowText(hEditControl4, TEXT("Mistakes - 0\r\nCharacters - 0"));
	SetWindowText(hEditControl, TEXT(""));

	//Plays uplifting music.
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
		//Setting Icon
		HICON hIcon1 = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
		SendMessage(hWnd, WM_SETICON, 1, (LPARAM)hIcon1);

		hEditControl = GetDlgItem(hWnd, IDC_EDIT4); //Writing Edit
		hEditControl2 = GetDlgItem(hWnd, IDC_EDIT7); //Text Edit
		hEditControl3 = GetDlgItem(hWnd, IDC_EDIT6); //Time Edit
		hEditControl4 = GetDlgItem(hWnd, IDC_EDIT2); //Statistic Edit
		hButtonStart = GetDlgItem(hWnd, IDC_START);	//'Start' Button

		TCHAR buffer[512] = TEXT("The universe has a beginning, but no end. Stars, too, have their own beginnings, but their own power results in their destruction. Finite. It is those who possess wisdom who are the greatest fools. History has shown us this. You could say that this is the final warning from God to those who resist.");
		wsprintf(str, buffer);
		SetWindowText(hEditControl2, str);
		SetWindowText(hEditControl4, TEXT("Mistakes - 0\r\nCharacters - 0"));
		//Disabling Input and output edit controls.
		EnableWindow(hEditControl, FALSE);
		EnableWindow(hEditControl2, FALSE);

		// Tray data.
		pNID = new NOTIFYICONDATA;
		memset(pNID, 0, sizeof(NOTIFYICONDATA)); 
		pNID->cbSize = sizeof(NOTIFYICONDATA); 
		pNID->hIcon = hIcon; 
		pNID->hWnd = hWnd; 
		lstrcpy(pNID->szTip, TEXT("TypeMaster")); 
		pNID->uCallbackMessage = WM_APP;
		pNID->uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE | NIF_INFO;
		lstrcpy(pNID->szInfo, TEXT("Type Master is hidden."));
		lstrcpy(pNID->szInfoTitle, TEXT("TypeMaster"));
		pNID->uID = WM_USER;

		//Setting Fonts
		HFONT hFont;
		LOGFONT LF = { -22, 0, 0, 0, FW_HEAVY, 0, 0, 0, RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, 0, TEXT("Microsoft Sans Serif") };
		hFont = CreateFontIndirect(&LF);
		SendDlgItemMessage(hWnd, IDC_EDIT4, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hWnd, IDC_EDIT7, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		LF = { -13, 0, 0, 0, FW_HEAVY, 0, 0, 0, RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, 0, TEXT("Microsoft Sans Serif") };
		hFont = CreateFontIndirect(&LF);
		SendDlgItemMessage(hWnd, IDC_EDIT2, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hWnd, IDC_EDIT6, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		
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
			ClearType();			//Calls clear function.
			break;
		}
		case IDC_EDIT4:							//If it's input edit control
			switch (HIWORD(wParam)) {	
			case EN_CHANGE:						//If there are any changes.
				
				TCHAR buffer[512];
				TCHAR buffer2[512];
				GetWindowText(hEditControl, buffer2, BUFFERLEN);					//Getting string from input and output edit controls.
				GetWindowText(hEditControl2, buffer, BUFFERLEN);
				int size = _tcslen(buffer2);
				ButtonPressed(hWnd, buffer2[size - 1]);						//Calculating what key was pressed to show it on the virtual keyboard.

				if (_tcslen(buffer) == 1) {											//If the input string is empty, then the player has finished typing the string.
					TCHAR statistic[BUFFERLEN];
					wsprintf(statistic, TEXT("Mistakes - %d\r\nCharacters - %d"), missesCount, characterAmount);
					PlaySoundA((LPCSTR)"questwin.wav", NULL, SND_FILENAME | SND_ASYNC);				//Plays 'victory' sound.
					MessageBox(hWnd, statistic, TEXT("VICTORY!"), MB_OK | MB_ICONINFORMATION);							//Showing message box with statistic.
					//Returning the previous states of elements.
					EnableWindow(hButtonStart, TRUE);
					EnableWindow(hEditControl3, FALSE);
					EnableWindow(hEditControl, FALSE);
					EnableWindow(hEditControl2, FALSE);
					EnableWindow(hEditControl4, FALSE);
					characterAmount = -1;
					missesCount = -1;
					SetWindowText(hEditControl4, TEXT("Mistakes - 0\r\nCharacters - 0"));
					isActive = FALSE;																					//Settings isActive to false, so Timer thread stop working.
				}
				if (_tcslen(buffer) > 0) {																				//If the last pressed key in input edit control is equal to the first symbol in the input key.
					if (buffer2[size - 1] == buffer[0]) {
						DeleteFirstCharacter();																			//Calling DeleteFirstCharacter function.
						characterAmount++;																			
					}
					else {																								//Else, it was a mistake.
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
	
	

	