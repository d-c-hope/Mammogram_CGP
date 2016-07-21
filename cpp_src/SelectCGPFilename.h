#ifndef SELECTCGPFILENAME_H
#define SELECTCGPFILENAME_H


#include "windows.h"
#include "resource.h"
#include "commctrl.h"
#include <string>


// ----------------------------------------------------------------------------
// class CGPDialog
//
// ----------------------------------------------------------------------------
class SelectCGPFilename {

public:
	// the window handle for the main window in the app
	//HWND hWnd;
	

	SelectCGPFilename() : filename("") {

	}

	//~ProgressDialog();
	
	//void updateDialog(float fractionDone);
	void createFilenameDialog(HWND hWnd);
	//void setupProgressBar();
	std::string getText();

	//void enableOK() {
	//	HWND buttonWnd = GetDlgItem(this->hWnd, IDOK);
	//	EnableWindow(buttonWnd, TRUE);
	//}

	//void disableOK() {
	//	HWND buttonWnd = GetDlgItem(this->hWnd, IDOK);
	//	EnableWindow(buttonWnd, FALSE);
	//}


protected:

	std::string filename;
	//float currentFracDone;
	// the static one is just there as a dummy cause you can't use win32
	// message procedures with object methods, this ties the procedure to the
	// object
	INT_PTR realCGPFilenameDialogProc(
		HWND hwndDlg,
		UINT uMsg,
	    WPARAM wParam,
		LPARAM lParam);


	// the message procedure for the cgp dialog procedure, a dummy procedure
	static INT_PTR CALLBACK CGPFilenameDialogProc(      
		HWND hwndDlg,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);
	HWND hWnd;

};
#endif