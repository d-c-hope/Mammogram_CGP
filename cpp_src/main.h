#ifndef MAIN_H
#define MAIN_H
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include "xercesc\util\PlatformUtils.hpp"
//#include "boost\regex.hpp"

//---------------------------------------------------------------------------
// define a window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg,
                             WPARAM wParam, LPARAM lParam);
//-----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Windows equivalent of main. 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
				   LPSTR lpCmdLine, int nCmdShow);
// ----------------------------------------------------------------------------


#endif