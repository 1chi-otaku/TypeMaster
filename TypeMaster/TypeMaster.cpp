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



int size;
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

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
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

		
		return TRUE;

	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT4:
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				TCHAR buffer[512];
				GetWindowText(hEditControl2, buffer, 512);
				if (_tcslen(buffer) == 1) {
					PlaySoundA((LPCSTR)"questwin.wav", NULL, SND_FILENAME | SND_ASYNC);
					MessageBox(hWnd, TEXT("You won!"), TEXT("VICTORY!"), MB_OK | MB_ICONINFORMATION);
				}
					
				if (_tcslen(buffer) > 0) {
					TCHAR buffer2[512];
					GetWindowText(hEditControl, buffer2, 512);
					int size = _tcslen(buffer2);
					if (buffer2[size - 1] == buffer[0]) {
						//Удалить первый символ буффера.
						DeleteFirstCharacter();
					}
					else {
						missesCount++;
						wsprintf(buffer, TEXT("%d"), missesCount);
						SetWindowText(hEditControl3, buffer);
					}
				}
				


				return TRUE;
			}
			{
			default:
				break;
			}
			break;
		}
	}
	

	return FALSE;
}