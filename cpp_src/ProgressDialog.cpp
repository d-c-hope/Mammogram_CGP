#include "ProgressDialog.h"

using namespace std;

ProgressDialog::ProgressDialog() {

}

ProgressDialog::~ProgressDialog() {

}

// ----------------------------------------------------------------------------
// createDialog
//
// ----------------------------------------------------------------------------
void ProgressDialog::createProgressDialog(HWND hWnd) {
	
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);	
		
	this->hWnd = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_CGPPROGRESS),
							      hWnd, progDialogProc, reinterpret_cast<LPARAM>(this));
	setupProgressBar();
	currentFracDone = 0;
	isCancelled = false;
	
	//SendDlgItemMessage(this->hWnd, IDOK, WM_ENABLE,(WPARAM)FALSE ,0L);



} // --- createDialog ---------------------------------------------------------


void ProgressDialog::updateDialog(float fractionDone) {
	//SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_STEPIT,0L,0L);
	currentFracDone = fractionDone * 200;
	SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETPOS,currentFracDone,0L);
}

void ProgressDialog::setupProgressBar() {
	SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETRANGE, 0, MAKELPARAM(0, 200)); 
	SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETSTEP,10L,0L);

}



void ProgressDialog::setText(string text) {
	SendDlgItemMessage(hWnd, IDC_PROGRESSSTATIC, WM_SETTEXT, 0, (LPARAM)text.c_str()); 

}





// ----------------------------------------------------------------------------
// realDialogProc
//
// the static one is just there as a dummy cause you can't use win32
// message procedures with object methods, this ties the procedure to the
// object
// ----------------------------------------------------------------------------
INT_PTR ProgressDialog::realProgDialogProc(HWND hWndDlg, UINT msg,
								  WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		
		case WM_CLOSE:
			DestroyWindow (hWndDlg);
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					DestroyWindow (hWndDlg);
				break;
				case IDCANCEL:
					DestroyWindow (hWndDlg);
					isCancelled = true;
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
INT_PTR CALLBACK ProgressDialog::progDialogProc(HWND hWndDlg, UINT msg,
									   WPARAM wParam, LPARAM lParam) {
   //this->hWnd = hWnd;
	if (msg == WM_INITDIALOG) {
		ProgressDialog* progD = reinterpret_cast<ProgressDialog*>(lParam);
		SetWindowLong(hWndDlg, GWL_USERDATA, reinterpret_cast<long>(progD));
		
	}
	// get the WWindow structure and pass the data to that
	ProgressDialog* progD = (ProgressDialog *) GetWindowLong(hWndDlg, GWL_USERDATA); 
	if (progD)
		return progD->realProgDialogProc(hWndDlg, msg, wParam, lParam);
	
										   
	
} // --- dialogProc -----------------------------------------------------------
