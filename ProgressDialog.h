#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H


#include "windows.h"
#include "resource.h"
#include "commctrl.h"
#include <string>


// ----------------------------------------------------------------------------
// class CGPDialog
//
// ----------------------------------------------------------------------------
class ProgressDialog {

public:
	// the window handle for the main window in the app
	//HWND hWnd;
	

	ProgressDialog(); 

	~ProgressDialog();
	
	void updateDialog(float fractionDone);
	void createProgressDialog(HWND hWnd);
	void setupProgressBar();
	void setText(std::string text);

	void enableOK() {
		HWND buttonWnd = GetDlgItem(this->hWnd, IDOK);
		EnableWindow(buttonWnd, TRUE);
	}

	void disableOK() {
		HWND buttonWnd = GetDlgItem(this->hWnd, IDOK);
		EnableWindow(buttonWnd, FALSE);
	}

	bool getIsCancelled() {
		return isCancelled;
	}


protected:

	float currentFracDone;
	// the static one is just there as a dummy cause you can't use win32
	// message procedures with object methods, this ties the procedure to the
	// object
	INT_PTR realProgDialogProc(
		HWND hwndDlg,
		UINT uMsg,
	    WPARAM wParam,
		LPARAM lParam);


	// the message procedure for the cgp dialog procedure, a dummy procedure
	static INT_PTR CALLBACK progDialogProc(      
		HWND hwndDlg,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);
	HWND hWnd;

	bool isCancelled;

};
#endif

