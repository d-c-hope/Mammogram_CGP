#include "CGPDialog.h"

using namespace std;

CGPDialog::~CGPDialog() {

}

// ----------------------------------------------------------------------------
// createDialog
//
// ----------------------------------------------------------------------------
void CGPDialog::createCGPIOAddDialog(HWND hWnd, OverlayInfo* ovInfo, CGP& cgp, unsigned short* pixels, 
									 int width, int height) {
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	FeatureExtractor featureExtractor;

	int retB = -1;
	if (isCGPSetUp != true) {
		int retA = DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_FEATURECHOICE),
							      hWnd, setupDialogProc, reinterpret_cast<LPARAM>(this));
		
		if(retA == IDOK) {
	
			isCGPSetUp = true;
			retB = DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_INPUTTYPE),
							      hWnd, addDialogProc, reinterpret_cast<LPARAM>(this));
		}
	}
	else {
		retB = DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_INPUTTYPE),
							      hWnd, addDialogProc, reinterpret_cast<LPARAM>(this));
	}


	// once the dialogs have returned its time to add the inputs
	if (retB == IDOK) {
		// we shall make some vectors for the inputs and outputs
		std::vector<float> inputs;
		std::vector<float> outputs;

		// if the user wanted to enter the raw pixels
		if (isRawPixels == true) {
			int currentPixIndex;
			float currentPix;
			// we must ensure that the number of inputs is consistent
			// i.e. we are looking at a window of constant size for the cgp
			// so that when the 2d array becomes linear if its say 3x3 everytime 
			// then we know that element 3 is the first of the second row
			int newWidth = 8;
			int newHeight = 8;
			int horizIndex;
			int vertIndex;
			for (int i = 0; i < newHeight; i++) {
				for (int j = 0; j < newWidth; j++) {
					// check for no overruns, just saturate in this case
					if (i >= height) vertIndex = height - 1;
					else vertIndex = i;
					if (j >= width) horizIndex = width - 1;
					else horizIndex = j;
					currentPixIndex = (vertIndex * width) + horizIndex;
					currentPix = static_cast<float>(pixels[currentPixIndex]);
					inputs.push_back(currentPix);
				}

			}

		}

		// if the user wanted to enter the frequency transformed pixels
		if (isTPixels == true) {
			// for now no fourier transform is done, this can be added later



		}

		// if the user wanted to enter stats from the spatial gray dependence matrix
		if (isSGDM == true) {
			
			// calculate whatever matrices we need
			featureExtractor.setSpatialGrayDependenceMatrix(pixels, width, height, 0, 1, 4096);
			featureExtractor.setSpatialGrayDependenceMatrix(pixels, width, height, 1, 1, 4096);
			featureExtractor.setSpatialGrayDependenceMatrix(pixels, width, height, 1, 0, 4096);
			featureExtractor.setSpatialGrayDependenceMatrix(pixels, width, height, -1, 1, 4096);

			// then calculate the maximum feature for each of the matrices
			featureExtractor.calculateSGDMFeatures(4096);

			// then get the features we have calculated
			std::list<GrayCooccuranceMatrix*> sgdmList = featureExtractor.getGrayCoocList();
			std::list<GrayCooccuranceMatrix*>::iterator sgdmListIt;
			
			float max;
			float secondMoment;
			float thirdMoment;
			for (sgdmListIt = sgdmList.begin(); sgdmListIt != sgdmList.end(); sgdmListIt++) {
				max = (**sgdmListIt).getMax();
				secondMoment = (**sgdmListIt).getSecondMoment();
				thirdMoment = (**sgdmListIt).getThirdMoment();
				thirdMoment = abs(thirdMoment);
				inputs.push_back(max);
				inputs.push_back(secondMoment);
				inputs.push_back(thirdMoment);

			}
			
		}

		// if the user wanted to use pixel stats
		if (isStats == true) {
			
			float mean = featureExtractor.getMean(pixels, (width * height));
			// try and normalise so that max value is 1
			float normMean = mean / static_cast<float>(4095);
			inputs.push_back(normMean);
			float secondMoment = featureExtractor.getNthMomentByHistogram(pixels, width, height, 4096, 2);
			
			float maxDifA = 4095 - mean;
			float maxDifB = mean; 
			float maxDif;
			if (maxDifA > maxDifB) maxDif = maxDifA;
			else maxDif = maxDifB;
			float squared = pow(maxDif, 2);
			float secondMomentNorm = secondMoment / static_cast<float>(squared * width * height);
			secondMomentNorm = abs(secondMomentNorm);
			inputs.push_back(secondMomentNorm);

			float thirdMoment = featureExtractor.getNthMomentByHistogram(pixels, width, height, 4096, 3);
			float cubed = pow(maxDif, 3);
			float thirdMomentNorm = thirdMoment / static_cast<float>(cubed * width * height);
			thirdMomentNorm = abs(thirdMomentNorm);
			inputs.push_back(thirdMomentNorm);
		}
		
		// now we must get the desired output and put that in the array
		std::string diagnosisS = ovInfo->getpathology();
		float diagnosis;
		if (diagnosisS.find("MALIGNANT") != std::string::npos) {
			diagnosis = 0;
		}
		if (diagnosisS.find("BENIGN") != std::string::npos) {
			diagnosis = 1;
		}
		if (diagnosisS.find("BENIGN_WITHOUT_CALLBACK") != std::string::npos) {
			diagnosis = 1;
		}

		// place this diagnosis into the output vector
		outputs.push_back(diagnosis);

		// finally we must add this to either testing or training inputs
		// in addition we must set the number of inputs and outputs to
		// the correct number. whilst this is already given a value from
		// the xml file (in case someone wanted to load some raw values 
		// from a file) here we must remember to set it
		if (isTesting == true) {
			cgp.addTestingInputs(inputs);
			cgp.addTestingOutputs(outputs);
			cgp.setNumOfInputs(inputs.size());
			cgp.setNumOfOutputs(outputs.size());
		}
		else {
			cgp.addTrainingInputs(inputs);
			cgp.addTrainingOutputs(outputs);
			cgp.setNumOfInputs(inputs.size());
			cgp.setNumOfOutputs(outputs.size());
		}
		
	}

} // --- createDialog ---------------------------------------------------------


// ----------------------------------------------------------------------------
// realDialogProc
//
// the static one is just there as a dummy cause you can't use win32
// message procedures with object methods, this ties the procedure to the
// object
// ----------------------------------------------------------------------------
INT_PTR CGPDialog::realSetupDialogProc(HWND hWndDlg, UINT msg,
								  WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		
		case WM_CLOSE:
			DestroyWindow (hWndDlg);
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					//SendDlgItemMessage(hDlg,  // window handle 
                    //IDC_BOX1,             // button identifier 
                    //BM_SETCHECK,          // message 
                    //0,                    // check state unchecked) 
					//0);                   // must be zero 
					LRESULT lStateSGDM;
					LRESULT lStateStats;
					LRESULT lStateRawPixels;
					LRESULT lStateTPixels;
					lStateSGDM = SendDlgItemMessage(hWndDlg, 
						IDC_CHECK_SGDM, BM_GETSTATE, 0, 0);
					lStateStats = SendDlgItemMessage(hWndDlg, 
						IDC_CHECK_STATS, BM_GETSTATE, 0, 0);
					lStateRawPixels = SendDlgItemMessage(hWndDlg, 
						IDC_CHECK_RAWPIXELS, BM_GETSTATE, 0, 0);
					lStateTPixels = SendDlgItemMessage(hWndDlg, 
						IDC_CHECK_TPIXELS, BM_GETSTATE, 0, 0);
				
					if (lStateSGDM == BST_CHECKED) {
						isSGDM = true;
					}
					if (lStateStats == BST_CHECKED) {
						isStats = true;
					}
					if (lStateRawPixels == BST_CHECKED) {
						isRawPixels = true;
					}
					if (lStateTPixels == BST_CHECKED) {
						isTPixels = true;
					}
					
					EndDialog(hWndDlg, IDOK);
				break;
				case IDCANCEL:
					EndDialog(hWndDlg, IDCANCEL);
				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;

	
} // --- realDialogProc -------------------------------------------------------




// ----------------------------------------------------------------------------
// dialogProc
// ----------------------------------------------------------------------------
// the message procedure for the cgp dialog procedure, a dummy procedure
INT_PTR CALLBACK CGPDialog::setupDialogProc(HWND hWndDlg, UINT msg,
									   WPARAM wParam, LPARAM lParam) {
	if (msg == WM_INITDIALOG) {
		CGPDialog* cgpD = reinterpret_cast<CGPDialog*>(lParam);
		SetWindowLong(hWndDlg, GWL_USERDATA, reinterpret_cast<long>(cgpD));
	}
	// get the WWindow structure and pass the data to that
	CGPDialog* cgpD = (CGPDialog *) GetWindowLong(hWndDlg, GWL_USERDATA); 
	if (cgpD)
		return cgpD->realSetupDialogProc(hWndDlg, msg, wParam, lParam);
	
										   
	
} // --- dialogProc -----------------------------------------------------------



// ----------------------------------------------------------------------------
// realDialogProc
//
// the static one is just there as a dummy cause you can't use win32
// message procedures with object methods, this ties the procedure to the
// object
// ----------------------------------------------------------------------------
INT_PTR CGPDialog::realAddDialogProc(HWND hWndDlg, UINT msg,
								  WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		
		case WM_CLOSE:
			DestroyWindow (hWndDlg);
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					//SendDlgItemMessage(hDlg,  // window handle 
                    //IDC_BOX1,             // button identifier 
                    //BM_SETCHECK,          // message 
                    //0,                    // check state unchecked) 
					//0);                   // must be zero 
					LRESULT lState;
					lState = SendDlgItemMessage(hWndDlg, IDC_RADIO1, BM_GETSTATE, 0, 0);
					if (lState == BST_CHECKED) {
						isTesting = true;
						isTraining = false;
					}
					else {
						isTraining = true;
						isTesting = false;
					}
					//SendDlgItemMessage(hDlg, IDC_BOX3, BM_SETCHECK, 0, 0); 
					//SendDlgItemMessage(hDlg,IDC_REDBACK,BM_SETCHECK,0,0);
					//SendDlgItemMessage(hDlg,IDC_BLUEBACK,BM_SETCHECK,0,0);
					EndDialog(hWndDlg, IDOK);
				break;
				case IDCANCEL:
					EndDialog(hWndDlg, IDCANCEL);
				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;

	
} // --- realDialogProc -------------------------------------------------------




// ----------------------------------------------------------------------------
// dialogProc
// ----------------------------------------------------------------------------
// the message procedure for the cgp dialog procedure, a dummy procedure
INT_PTR CALLBACK CGPDialog::addDialogProc(HWND hWndDlg, UINT msg,
									   WPARAM wParam, LPARAM lParam) {
	if (msg == WM_INITDIALOG) {
		CGPDialog* cgpD = reinterpret_cast<CGPDialog*>(lParam);
		SetWindowLong(hWndDlg, GWL_USERDATA, reinterpret_cast<long>(cgpD));
	}
	// get the WWindow structure and pass the data to that
	CGPDialog* cgpD = (CGPDialog *) GetWindowLong(hWndDlg, GWL_USERDATA); 
	if (cgpD)
		return cgpD->realAddDialogProc(hWndDlg, msg, wParam, lParam);
	
										   
	
} // --- dialogProc -----------------------------------------------------------