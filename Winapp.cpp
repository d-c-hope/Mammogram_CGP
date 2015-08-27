#include "WinApp.h"
#include "resource.h"
#include "MainWnd.h"

//-----------------------------------------------------------------------------
// constructor WApplication
//
// Sets all the variables in the WndClsEx structure
// ----------------------------------------------------------------------------
WApplication::WApplication(HINSTANCE hInst, char *ClsName,
			   WNDPROC WndPrc, int MenuName)
{
	// Initializing the application using the application member variable

	// set the size that needs to be allocated for the structure
	WndClsEx.cbSize        = sizeof(WNDCLASSEX);
	// set the class style like horizontal redraw for example
	WndClsEx.style         = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	// set the pointer to the window procedure
	WndClsEx.lpfnWndProc   = WndPrc;
	// define any extra storage for this class
	WndClsEx.cbClsExtra    = 0;
	// define any extra storage for the window, this is needed for referencing
	// the class window procedure
	WndClsEx.cbWndExtra    = sizeof(MainWnd *);
	// pass in the application instance
	WndClsEx.hInstance     = hInst;
	// set the application icon
	WndClsEx.hIcon         = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	// set the cursor
	WndClsEx.hCursor       = LoadCursor(NULL, IDC_ARROW);
    // set background colour
	WndClsEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	// specifies the menu
	WndClsEx.lpszMenuName  =  MAKEINTRESOURCE(MenuName);
	// name of this structure
	WndClsEx.lpszClassName = ClsName;
	// small icon for the app
	WndClsEx.hIconSm       = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
}
//-----------------------------------------------------------------------------




// ----------------------------------------------------------------------------
// Register
//
// just calls the function to register the class with windows
// ----------------------------------------------------------------------------
void WApplication::Register()
{
	RegisterClassEx(&WndClsEx);
} // --- Register -------------------------------------------------------------


//-----------------------------------------------------------------------------

// --- class WApplication -----------------------------------------------------