#include "main.h"

#include "WinApp.h"
#include "MainWnd.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include <string>
#include <gdiplus.h>
//#pragma comment(lib, "gdiplus")
//using namespace Gdiplus;

XERCES_CPP_NAMESPACE_USE

// ----------------------------------------------------------------------------
// WinMain
//
// Windows equivalent of main. 
// ----------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
				   LPSTR lpCmdLine, int nCmdShow)
{
	// the message thats collected and dispatched
	MSG   Msg;
	// the name of the class to build a window
	char *ClsName = "Main window class";
	// the name printed on an individual window
	char *WndName = "Mamoview";

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	// Some code thats necessary to initialise gdi, don;t know how it
	// works must just call some things in the dll
    Gdiplus::GdiplusStartupInput gdiplusStartupInput; 
	ULONG_PTR gdiplusToken; 
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	try {
	 XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
    // Do your failure processing here
    return 1;
	}

  // Do your actual work with Xerces-C++ here.

  


	
	// Declare and initialize the application class, which contains data needed
	// to make a window in the first place
	WApplication WinApp(hInstance, ClsName, WndProc, IDR_MENU1);
	WinApp.Register();

	// // Declare a MainWnd object which represents what is seen graphically
	// and then create it
	MainWnd Wnd;
	/*HWND Create(HINSTANCE hinst,                        // application instance
		        LPCTSTR clsname,						// the name of the window class
     		    LPCTSTR wndname,						// the name of the window
	            HWND parent   = NULL,					// the parent window reference
	            DWORD dStyle  = WS_OVERLAPPEDWINDOW,	// the window style
	            DWORD dXStyle = 0,						// extended window style
		        int x         = 10,			// x position of the window
                int y         = 10,			// y position of the window
		        int width     = 300,			// width of the window
                int height    = 300);			// height of the window*/
	Wnd.Create(hInstance, ClsName, WndName, NULL, WS_OVERLAPPEDWINDOW | 
				WS_CLIPCHILDREN,WS_EX_LAYERED | WS_EX_OVERLAPPEDWINDOW );
	// Display the main window
	Wnd.Show();
	

	//prepareGraphics();
	// Process the main window's messages
	while( GetMessage(&Msg, NULL, 0, 0) )
	{
		// convert virtual key messages to character ones and put back into message queue
		TranslateMessage(&Msg);
		// send to window procedure, of which there might be a few in 1 app
		DispatchMessage(&Msg);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken); 
	XMLPlatformUtils::Terminate();
	return 0;
} // --- WinMain --------------------------------------------------------------



//-----------------------------------------------------------------------------
// MainWndProc
//
// The window procedure for the main window, deals with the different types
// of messages received
// ----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
                             WPARAM wParam, LPARAM lParam)
{
	
	// If the message is WM_NCCREATE, associate Window pointer with this window
	// Note: WM_NCCREATE is not the first message that this WndProc will process
	// What happens here is that we assigned some extra space for the window which
	// was of size of a pointer to a MainWnd object. Now in the WM_NCREATE message the
	// lParam method is actually the class structure used to make the window i.e. 
	// CREATESTRUCT. In this stucture is a pointer to a MainWnd object. SetWindowLong in
	// this usage sets the extra window data to this which can only be done on creation
	if (msg == WM_NCCREATE) {
		
		LPCREATESTRUCT cs = (LPCREATESTRUCT) lParam;
		SetWindowLong(hWnd, GWL_USERDATA, (long) cs->lpCreateParams);
	}
	// get the MainWnd structure and pass the data to that
	MainWnd* w = (MainWnd *) GetWindowLong(hWnd, GWL_USERDATA); 
	if (w)
		return w->WndProc(hWnd, msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);
} // --- MainWndProc ----------------------------------------------------------



//---------------------------------------------------------------------------