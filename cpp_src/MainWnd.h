#ifndef MAIN_WND_H
#define MAIN_WND_H
// needed for the coinitialize method later
//#define _WIN32_WINNT 0x0400
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <windowsx.h>
#include <gdiplus.h>
#include <commctrl.h>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "OverlayInfo.h"
#include "DebugClass.h"
#include "ZoomInfo.h"
#include <shlobj.h>
#include <shlwapi.h>
// needed for the coinitialize method later
#include <ole2.h>
#include <objBase.h>

#include "MammoviewSettings.h"
#include "CGP.h"
#include "CGPDialog.h"
#include "PixelArray.h"



//#include "DebugClass.h"

//---------------------------------------------------------------------------
// class MainWnd
//
// This is the central class in the program and efectively represents a window
// most processing starts here as everything is a response to user choices
// in the window
// ----------------------------------------------------------------------------
class MainWnd
{
public:
	
	// Any initialisation
	MainWnd();

	// Cleanup
	~MainWnd();

	// The Create() method wil be used to initialize a window
	HWND Create(HINSTANCE hinst,                        // application instance
		        LPCTSTR clsname,						// the name of the window class
     		    LPCTSTR wndname,						// the name of the window
	            HWND parent   = NULL,					// the parent window reference
	            DWORD dStyle  = WS_OVERLAPPEDWINDOW,	// the window style
				DWORD dXStyle = 0,						// extended window style
		        int x         = 10,			// x position of the window
                int y         = 20,			// y position of the window
		        int width     = 1200,			// width of the window
                int height    = 960);			// height of the window

	// This method will be used to display the window
	bool Show(int dCmdShow = SW_SHOWNORMAL);

	// Because each window is of type HWND, we will need a way
	// to recognize the window handle when used in our application
	operator HWND();

	// the window procedure has been moved into this class so it
	// can be useful!
	LRESULT CALLBACK MainWnd::WndProc(HWND hWnd, UINT Msg,
                             WPARAM wParam, LPARAM lParam);

	
   
protected:
	// This will be a global handle available to
	// this and other windows
	HWND hWnd;


	static DWORD WINAPI ThrdFunc(LPVOID n);

	//HINSTANCE hinst
	void MainWnd::changeCurrentCursor(LPCTSTR cursor, bool isPredefined);

	// switches between normal image and one with an overlay
	void MainWnd::switchImage();


	// creates the toolbar that is part of the window
	void MainWnd::createToolbar(HINSTANCE hinst);

	// called from an on paint message, calls all drawing methods
	void draw(HWND hWnd);

	// Loads in the initial image
	bool MainWnd::loadImage(const char * image);

	// returns an overlay filename
	std::string MainWnd::getOverlayFileName(std::string imageFileName);

	// returns a scaled version of an image
	Gdiplus::Bitmap* MainWnd::ScaleByPercent(Gdiplus::Bitmap * origMammo, int Percent);

	// opens a file dialog and get the appropiate information
	bool openFile();

	// after getting a filename from a dialog or whatever this does the bulk of the work
	bool openAndProcessImage(const char* imageFileName);

	// puts information on the screen about the mammogram 
	bool drawText(HWND hWnd, HDC hDc, Gdiplus::Graphics* graphics, long lfHeight);

	// draws an ellipse
	void drawEllipse(HDC hDc, int startX, int startY, int endX, int endY);

	// used in order to get the ics name from the image name
	std::string MainWnd::getInfoFileName(std::string imageFileName);

	// used to get information about the image, uses the ics file
	std::vector<std::string*> getFileInformation(std::string infoFile);

	// draws the title when the program begins
	void drawTitle(HWND hWnd, HDC hDc, Gdiplus::Graphics* graphics, long lfHeight);

	// zooms in on a portion of an image
	void zoomIn(int x, int y);

	// zooms out from the selected portion of the image
	void zoomOut();

	// opens up a directory full of sub directories that are cases
	bool openCaseDirectory();

	// gets the next image in a case directory or one viewed earlier
	// if we have previously gone back
	void getNextImage();

	// gets and shows the previous image that was viewed
	void getPreviousImage();

	// gets the pixels that are to have their features extracted
	PixelArray<unsigned short> getHighlightedPixels();

	void openCGPLocation();


	// the bitmap which is currently displayed
	Gdiplus::Bitmap *smaller;

	// the bitmap which is being used
	Gdiplus::Bitmap *mammogram;

	// the mammogram with overlays drawn over it
	Gdiplus::Bitmap *overlayMammogram;

	// a vector of coordinates in mammogram representing the zoom levels
	std::vector<ZoomInfo> zoomInfoVector;
	

	



	// a class that encapsulats some of the basic settings and info
	// that are required
	MammoviewSettings mamSets;

	// the CGP program
	CGP cgp;


	// the toolbar
	HWND windowToolbar;

	// a class for dialogs used for CGP
	CGPDialog cgpDialog;

	// button to move back
	HWND forwardButton;

	// button to move forward
	HWND backButton;

	//bool shouldPaint;

}; //--- class MainWnd --------------------------------------------------------


#endif