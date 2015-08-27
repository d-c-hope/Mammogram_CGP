#ifndef WINCTRLS_H
#define WINCTRLS_H

#include <windows.h>

//-----------------------------------------------------------------------------
// class WControl
//
//
// ----------------------------------------------------------------------------
class WControl
{
public:
	WControl();
	virtual ~WControl();
		
	     // creates a window and returns a handle to it
         HWND Create( HINSTANCE hinst,   // the application instance
					  LPCTSTR clsname,  // the window class name
		              LPCTSTR wndname,  // the window name
					  HWND parent,      // the parents handle
					  DWORD dStyle,     // style associated with the window
		              int x,            // the x position
					  int y,            // the y position
		              int width,        // the window width
					  int height);       // the window height


    
	
    // shows the window
	BOOL Show(int dCmdShow = SW_SHOWNORMAL);
	operator HWND();
protected:
	// this class must contain a handle to the window
	HWND hwnd;
	HINSTANCE mhInst;

public:
	HINSTANCE GetInstance();

private:
};
//---------------------------------------------------------------------------

#endif	// WINCTRLS_H