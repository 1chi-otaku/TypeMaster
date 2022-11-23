#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"
#include <time.h>


#pragma comment(lib,"comctl32")

#pragma warning(disable : 4996)




int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}



BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	
	srand(time(NULL));
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case  WM_INITDIALOG: {
		SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);

		return TRUE;
	}

	case WM_COMMAND: {


		return TRUE;
	}
	}

	return FALSE;
}