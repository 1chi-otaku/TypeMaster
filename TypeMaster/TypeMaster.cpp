#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"
#include <time.h>


#pragma comment(lib,"comctl32")

#pragma warning(disable : 4996)




BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}


HANDLE hMutex;

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG: {
		hMutex = CreateMutex(NULL, FALSE, TEXT("{D99CD3E0-670D-4def-9B74-99FD7E793DFB}"));
		DWORD dwAnswer = WaitForSingleObject(hMutex, 0);
		if (dwAnswer == WAIT_TIMEOUT)
		{
			MessageBox(hWnd, TEXT("You cannot run this application twice."), TEXT("ERROR"), MB_OK | MB_ICONERROR);
			EndDialog(hWnd, 0);
		}
		return TRUE;

	}
	case WM_COMMAND: {
		
	}

	}
	return FALSE;
}