#ifndef WINAPP_H
#define WINAPP_H

#include <windows.h>

//-----------------------------------------------------------------------------
// class WApplication
//
//
// ----------------------------------------------------------------------------
class WApplication
{
public:
	// This constructor will initialize the application
	WApplication(HINSTANCE hInst,  // pass application instance
		         char *ClasName,   // pass window class name
		         WNDPROC WndPrc,   // pass function pointer to message handler
				 int MenuName = 0);

	// Register the WNDCLASSEX structure with windows
	void Register();

protected:
	// Class variable that holds the window details and application
	// instance
	WNDCLASSEX WndClsEx;
};
//---------------------------------------------------------------------------

#endif
