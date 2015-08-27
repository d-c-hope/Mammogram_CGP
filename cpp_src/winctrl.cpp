#include "winctrl.h"

//---------------------------------------------------------------------------
WControl::WControl()
	: hwnd(0)    // initialise window handle to null
{
}



//---------------------------------------------------------------------------
//WControl
//
// constructor that does nothing
// --------------------------------------------------------------------------
WControl::~WControl()
{
}



//---------------------------------------------------------------------------
WControl::operator HWND()
{
	return hwnd;
}



//---------------------------------------------------------------------------
HWND WControl::Create(HINSTANCE hinst,  // the application instance
					  LPCTSTR clsname,  // the window class name
		              LPCTSTR wndname,  // the window name
					  HWND parent,      // the parents handle
					  DWORD dStyle,     // style associated with the window
		              int x,            // the x position
					  int y,            // the y position
		              int width,        // the window width
					  int height)       // the window height
{
	hwnd = CreateWindow(clsname,		// a name for  our window class
						wndname,		// a name for our individual window which is displayed
						dStyle,			// things like is there a border
		                x,				// x position on monitor from left
						y,				// y position on monitor from top
						width,			// window width
						height,			// window height
						parent,			// the parent window handle
						NULL,			//  either a menu handle (this can be in windwo class anyay)
						                //   or a child window identifier used to notify parents of events
						hinst,			// the application reference needed to associate and
										//   register this window
						NULL);			// msdn:"Pointer to a value to be passed to the window through 
	                                    // the CREATESTRUCT structure"

	return hwnd;
}



//---------------------------------------------------------------------------
BOOL WControl::Show(int dCmdShow)
{
	BOOL CanShow = ::ShowWindow(hwnd, dCmdShow);

	if( CanShow )
		return TRUE;
	return FALSE;
}



//---------------------------------------------------------------------------
HINSTANCE WControl::GetInstance()
{
	return mhInst;
}
//---------------------------------------------------------------------------