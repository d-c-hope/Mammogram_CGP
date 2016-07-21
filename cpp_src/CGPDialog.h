#ifndef CGPDIALOG_H
#define CGPDIALOG_H

#include "windows.h"
#include "resource.h"
#include "FeatureExtractor.h"
#include "CGP.h"
#include "OverlayInfo.h"
#include "math.h"

// ----------------------------------------------------------------------------
// class CGPDialog
//
// ----------------------------------------------------------------------------
class CGPDialog {

public:
	// the window handle for the main window in the app
	//HWND hWnd;
	bool isTesting;
	bool isTraining;
	bool isSGDM;
	bool isStats;
	bool isRawPixels;
	bool isTPixels;
	bool isCGPSetUp;

	std::list<float> trainingInputs;

	std::list<float> testingInputs;
	
	// used for extracting features
	//FeatureExtractor featureExtractor;

	CGPDialog() {
		//this->hWnd = hWnd;
		isTesting = true;
		isTraining = false;
		isSGDM = false;
		isStats = false;
	    isRawPixels = false;
	    isTPixels = false;
		isCGPSetUp = false;
	}

	~CGPDialog();

	void createCGPIOAddDialog(HWND hWnd, OverlayInfo* ovInfo, CGP& cgp, 
								unsigned short* pixels, int width, int height);

	void reset() {
		isTesting = true;
		isTraining = false;
		isSGDM = false;
		isStats = false;
	    isRawPixels = false;
	    isTPixels = false;
		isCGPSetUp = false;
	}


protected:

	// the static one is just there as a dummy cause you can't use win32
	// message procedures with object methods, this ties the procedure to the
	// object
	INT_PTR realSetupDialogProc(
		HWND hwndDlg,
		UINT uMsg,
	    WPARAM wParam,
		LPARAM lParam);


	// the message procedure for the cgp dialog procedure, a dummy procedure
	static INT_PTR CALLBACK setupDialogProc(      
		HWND hwndDlg,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);


	// the static one is just there as a dummy cause you can't use win32
	// message procedures with object methods, this ties the procedure to the
	// object
	INT_PTR realAddDialogProc(
		HWND hwndDlg,
		UINT uMsg,
	    WPARAM wParam,
		LPARAM lParam);


	// the message procedure for the cgp dialog procedure, a dummy procedure
	static INT_PTR CALLBACK addDialogProc(      
		HWND hwndDlg,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

};

#endif
