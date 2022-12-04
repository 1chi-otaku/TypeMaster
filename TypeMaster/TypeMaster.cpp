#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"
#include <time.h>
#include <vector>
#include <string>
#include <array>

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



int size;
TCHAR* str = new TCHAR[_tcslen(TEXT("Hello!"))+1];

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
		
		TCHAR buffer[32] = TEXT("Hello!");
		wsprintf(str, buffer);
		
		hEditControl = GetDlgItem(hWnd, IDC_EDIT4);
		hEditControl2 = GetDlgItem(hWnd, IDC_EDIT2);
		SetWindowText(hEditControl2, str);

		
		return TRUE;

	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT4:
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				TCHAR buffer[32];
				TCHAR buffer2[32];
				GetWindowText(hEditControl, buffer2, 32);
				GetWindowText(hEditControl2, buffer, 32);
				int size = _tcslen(buffer2);

				if (buffer2[size-1] == buffer[0]) {
					//Удалить первый символ буффера.
					DeleteFirstCharacter();

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