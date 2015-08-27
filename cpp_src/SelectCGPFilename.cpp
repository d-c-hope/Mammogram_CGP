#include "SelectCGPFilename.h"

using namespace std;

//ProgressDialog::ProgressDialog() : filename("") {

//}

//ProgressDialog::~ProgressDialog() {

//}

// ----------------------------------------------------------------------------
// createDialog
//
// ----------------------------------------------------------------------------
void SelectCGPFilename::createFilenameDialog(HWND hWnd) {
	
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);	
		
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_ENTERFILENAME),
							      hWnd, CGPFilenameDialogProc, reinterpret_cast<LPARAM>(this));
//	setupProgressBar();
//	currentFracDone = 0;
	
	//SendDlgItemMessage(this->hWnd, IDOK, WM_ENABLE,(WPARAM)FALSE ,0L);



} // --- createDialog ---------------------------------------------------------





string SelectCGPFilename::getText() {
	return filename;

}



// ----------------------------------------------------------------------------
// realDialogProc
//
// the static one is just there as a dummy cause you can't use win32
// message procedures with object methods, this ties the procedure to the
// object
// ----------------------------------------------------------------------------
INT_PTR SelectCGPFilename::realCGPFilenameDialogProc(HWND hWndDlg, UINT msg,
								  WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		
		case WM_CLOSE:
			EndDialog(hWndDlg, IDCANCEL);
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					{
					char buffer[40];
					HWND hWndText;
					hWndText = GetDlgItem(hWndDlg, IDC_EDITFILENAME);
					GetWindowText(hWndText, buffer, 40);
					filename = string(buffer);
					string path("C:\\");
					filename = path + filename;
					EndDialog(hWndDlg, IDOK);
					}
				break;
				case IDCANCEL:
					//filename = "none";
					EndDialog(hWndDlg, IDCANCEL);
				break;
			}
		default:
			return FALSE;
	}
	return TRUE;

	
} // --- realDialogProc -------------------------------------------------------




// ----------------------------------------------------------------------------
// dialogProc
// ----------------------------------------------------------------------------
// the message procedure for the cgp dialog procedure, a dummy procedure
INT_PTR CALLBACK SelectCGPFilename::CGPFilenameDialogProc(HWND hWndDlg, UINT msg,
									   WPARAM wParam, LPARAM lParam) {
   //this->hWnd = hWnd;
	if (msg == WM_INITDIALOG) {
		SelectCGPFilename* filenameD = reinterpret_cast<SelectCGPFilename*>(lParam);
		SetWindowLong(hWndDlg, GWL_USERDATA, reinterpret_cast<long>(filenameD));
		
	}
	// get the WWindow structure and pass the data to that
	SelectCGPFilename* filenameD = (SelectCGPFilename *) GetWindowLong(hWndDlg, GWL_USERDATA); 
	if (filenameD)
		return filenameD->realCGPFilenameDialogProc(hWndDlg, msg, wParam, lParam);
	
										   
	
} // --- dialogProc -----------------------------------------------------------
