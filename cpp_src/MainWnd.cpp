#include "MainWnd.h"
#include "resource.h"
#include <iostream>
#include "boost\regex.hpp"
#include <AtlConv.h>


using namespace Gdiplus;



//-----------------------------------------------------------------------------
// MainWnd
//
// the constructor, gives class variables safe initial values
// ----------------------------------------------------------------------------
MainWnd::MainWnd() : mamSets(), cgp(std::string("CGPSettings.xml"), true) {

	//CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	// the window handle only means anything once we create a window
	hWnd = NULL;
	// this displayed image does nt exist till the user finds one
	smaller = NULL;
	mammogram = NULL;
	overlayMammogram = NULL;

	// set the position of the mammogram image
	mamSets.setITopLeftX(10);
	mamSets.setITopLeftY(40);

	// give default so clear not done yet
	mamSets.setMouseEndX(-1);

	
	
	
} // --- MainWnd --------------------------------------------------------------



// ----------------------------------------------------------------------------
// ~MainWnd
//
// removes the images
// ----------------------------------------------------------------------------
MainWnd::~MainWnd() {
	// these appear to be invalid here, probably cause windows resources released
	// when the message loop ends
/*	if (mammogram != NULL) {
		delete mammogram;
		mammogram = NULL;
		
	}
	if (smaller != NULL) {
		delete smaller;
		smaller = NULL;
	}
	if (overlayMammogram != NULL) {
		delete overlayMammogram;
		overlayMammogram = NULL;
	} */
//	delete selectedPixelArray;
	
}





//-----------------------------------------------------------------------------
// Create
//
// this is used to create a window
// ----------------------------------------------------------------------------
HWND MainWnd::Create(HINSTANCE hinst,   // the application instance
    				 LPCTSTR clsname,   // the window class name
	    			 LPCTSTR wndname,   // the window title
	  	    		 HWND parent,       // parent window
			    	 DWORD dStyle,      // standard styles
					 DWORD dXStyle,     // specifies extra styles
				     int x,             // the x position of the window
     				 int y,             // the y position of the window
	     			 int width,         // the window width
		    		 int height)        // the window height
{
	// When call the Create() method, we can use it to create a new window
	hWnd = CreateWindowEx(dXStyle,    // extra style properties
		                   clsname,    // window class name
						   wndname,    // individual window name
						   dStyle,     // basic window style
						   x,          // window x coordinate
						   y,          // window y coordinate
						   width,     // window width
		                   height,    // window height
						   parent,    // reference to window parent
						   NULL,      // reference to menu
						   hinst,     // application instance
						   this);     // something to add to 
									  //CREATESTRUCT for MDI windows

	// This is some standard initialisation code so that toolbars can be used in this window
	INITCOMMONCONTROLSEX InitCtrlEx;
	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC  = ICC_BAR_CLASSES;
	InitCommonControlsEx(&InitCtrlEx);
	// call the objects method for making a toolbar
	createToolbar(hinst);

	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);


	backButton = CreateWindow( 
    "BUTTON",   // predefined class 
    "Back",       // button text 
    WS_CHILD | BS_DEFPUSHBUTTON,  // styles 
 
    // Size and position values are given explicitly, because 
    // the CW_USEDEFAULT constant gives zero values for buttons. 
    550,         // starting x position 
    640,         // starting y position 
    90,        // button width 
    50,        // button height 
    hWnd,       // parent window 
    (HMENU) IDM_BUTTON1,       // No menu 
    (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE), 
    NULL);      // pointer not needed 
	ShowWindow(forwardButton, SW_HIDE);

	forwardButton = CreateWindow( 
    "BUTTON",   // predefined class 
    "Forward",       // button text 
     WS_CHILD | BS_DEFPUSHBUTTON,  // styles 
    670,         // starting x position 
    640,         // starting y position 
    90,        // button width 
    50,        // button height 
    hWnd,       // parent window 
    (HMENU) IDM_BUTTON2,       // No menu 
    (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE), 
    NULL);      // pointer not needed 
	ShowWindow(backButton, SW_HIDE);

//	shouldPaint = true;

	// We hope everything went alright and the window was created
	if( hWnd != NULL ) {
		return hWnd;
	}

	
	//

	// If something went wrong, for example if the window could not
	// be created, return a null pointer, i.e. 0
	return NULL;
} // --- MainWnd::Create ------------------------------------------------------




//-----------------------------------------------------------------------------
// MainWnd::Show
//
// ----------------------------------------------------------------------------
bool MainWnd::Show(int dCmdShow)
{
	// We will display the main window as a regular object and update it
	if(	ShowWindow(hWnd, dCmdShow)) //&& UpdateWindow(hWnd) )
		return true;
	return false;
}


// ----------------------------------------------------------------------------
// MainWnd::createToolbar
//
// the main window has a toolbar and this creates it adding zoom, and an
// oadd overlay button
// ----------------------------------------------------------------------------
void MainWnd::createToolbar(HINSTANCE hinst) {
	// make a toolbar with 3 buttons
	TBBUTTON tbrButtons[5];
	
	// make each one without extra data or a string
	tbrButtons[0].iBitmap   = 0;
	tbrButtons[0].idCommand = IDM_OVERLAY;
	tbrButtons[0].fsState   = TBSTATE_ENABLED;
	tbrButtons[0].fsStyle   = TBSTYLE_BUTTON;
	tbrButtons[0].dwData    = 0L;
	tbrButtons[0].iString   = 0;
	
	tbrButtons[1].iBitmap   = 1;
	tbrButtons[1].idCommand = IDM_ZOOMIN;
	tbrButtons[1].fsState   = TBSTATE_ENABLED;
	tbrButtons[1].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP
							  | TBSTYLE_CHECK;;
	tbrButtons[1].dwData    = 0L;
	tbrButtons[1].iString   = 0;

	tbrButtons[2].iBitmap   = 2;
	tbrButtons[2].idCommand = IDM_ZOOMOUT;
	tbrButtons[2].fsState   = TBSTATE_ENABLED;
	tbrButtons[2].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP 
		                       | TBSTYLE_CHECK;;
	tbrButtons[2].dwData    = 0L;
	tbrButtons[2].iString   = 0;

	tbrButtons[3].iBitmap   = 3;
	tbrButtons[3].idCommand = IDM_ARROW;
	tbrButtons[3].fsState   = TBSTATE_ENABLED;
	tbrButtons[3].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP
		                      | TBSTYLE_CHECK;;
	tbrButtons[3].dwData    = 0L;
	tbrButtons[3].iString   = 0;

	tbrButtons[4].iBitmap   = 4;
	tbrButtons[4].idCommand = IDM_HIGHLIGHT;
	tbrButtons[4].fsState   = TBSTATE_ENABLED;
	tbrButtons[4].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP 
		                      | TBSTYLE_CHECK;;
	tbrButtons[4].dwData    = 0L;
	tbrButtons[4].iString   = 0;

	// note we use the same  identifier for the toolbar and bitmap since
	// they refer to the same thing as far as this is concerned
	windowToolbar = CreateToolbarEx(hWnd,
		            WS_VISIBLE | WS_CHILD | WS_BORDER,
	                IDB_BITMAP1,
	                5,
				    hinst,
			        IDB_BITMAP1,
				    tbrButtons,
				    5,
				    16, 16, 16, 16,     // this refers to the 
					             //distance between items in the toolbar
										
				    sizeof(TBBUTTON));

} // --- createToolbar --------------------------------------------------------



//-----------------------------------------------------------------------------
// operator HWND
//
// used for automatic type conversion if type HWND is required
// ----------------------------------------------------------------------------
MainWnd::operator HWND()
{
	return hWnd;
} // --- MainWnd::Operator HWND -----------------------------------------------



// ----------------------------------------------------------------------------
// changeCurrentCursor
//
// changes the cursor seen to whatever wanted like magnify
// ----------------------------------------------------------------------------
void MainWnd::changeCurrentCursor(LPCTSTR cursor, bool isPredefined)
{
	HCURSOR crsCross;
	if (isPredefined == false) {
		
		HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd,
											GWL_HINSTANCE);
		crsCross = LoadCursor(hInst, cursor);
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)crsCross);
	}
	else {
		crsCross = LoadCursor(NULL, cursor);
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)crsCross);

	}
} //--- changeCurrentCursor ---------------------------------------------------



//-----------------------------------------------------------------------------
// MainWnd::loadImage
//
// loads a mammogram
// ----------------------------------------------------------------------------
bool MainWnd::loadImage(const char * image) {
    // this is needed in order to enable the a2w command
	USES_CONVERSION; 
	if (mammogram != NULL) {
		delete mammogram;
		mammogram = NULL;
	}
	if (smaller != NULL) {
		delete smaller;
		smaller = NULL;
	}
	if (overlayMammogram != NULL) {
		delete overlayMammogram;
		overlayMammogram = NULL;
	}
	// make a bitmap passing it a filename as a wchar_t not char
	if ( (std::string(image)).find(".png") != std::string::npos ) {
		mammogram = new Bitmap(A2W(image));
		int width = mammogram->GetWidth();
		float scale;
		if (width > 2800) {
			scale = (int)(16 * ((float)2800 / (float)width));
			std::stringstream s;
			s << scale << "\n";
			DebugClass::write(s.str());
		}
		else {
			scale = 16;
		}

		// the actual image is massive so scale it so that it fits sensibly
		smaller = ScaleByPercent(mammogram, scale);
		zoomInfoVector.clear();
		zoomInfoVector.push_back(ZoomInfo(0, 0, mammogram->GetWidth(),
								mammogram->GetHeight()));

		// give default so clear not done yet
		mamSets.setMouseEndX(-1);
	}
	else {
		InvalidateRect(hWnd, NULL, TRUE); 
	    UpdateWindow(hWnd);
	}
		if (mammogram != NULL) return true;
		else return false;
	// We want an immediate update without waiting for other message to be processed
	// note that update only sends paint message if aware the client area is now invalid
	//InvalidateRect(hWnd, NULL, TRUE); 
	//UpdateWindow(hWnd);


} // --- MainWnd::loadImage ---------------------------------------------------


// ----------------------------------------------------------------------------
// MainWnd::switchImage
//
// switches between the display of an overlay image and a normal one
// ----------------------------------------------------------------------------
void MainWnd::switchImage() {
	// if we are displaying the non overlay display the overlay and vice versa
	bool isOverlay = mamSets.getIsOverlay();

	int width = mammogram->GetWidth();
	float scale;
	if (width > 2800) {
		scale = (int)(16 * ((float)2800 / (float)width));
		std::stringstream s;
		s << scale << "\n";
		DebugClass::write(s.str());
	}
	else {
		scale = 16;
	}

	if (isOverlay == true) {
		
		smaller = ScaleByPercent(overlayMammogram, scale);

	}
	else {
		smaller = ScaleByPercent(mammogram, scale);

	}
	zoomInfoVector.clear();
	zoomInfoVector.push_back(ZoomInfo(0, 0, mammogram->GetWidth(),
								mammogram->GetHeight()));


} // --- MainWnd::switchImage -------------------------------------------------



// ----------------------------------------------------------------------------
// MainWnd::ScaleByPercent 
//
// This scales an image by a given percent returning the scaled image
// ----------------------------------------------------------------------------
Bitmap* MainWnd::ScaleByPercent(Bitmap * origMammo, int Percent)
{
	// convert to between 0 and 1
    float nPercent = ((float)Percent/100);

	// get the width of the original image
    int sourceWidth = origMammo->GetWidth();
	// get the height of the original image
    int sourceHeight = origMammo->GetHeight();
	// start at the top left corner of the image
    int sourceX = 0;
    int sourceY = 0;

	// start at top left
    int destX = 0;
    int destY = 0; 
	// scale width and height according to percent
    int destWidth  = (int)(sourceWidth * nPercent);
    int destHeight = (int)(sourceHeight * nPercent);
	// shove the information in a rect structure
	Rect Dest(destX,destY,destWidth,destHeight);

	// make a new bitmap of the new size
    Bitmap *newMammo = new Bitmap(destWidth, destHeight,
                             PixelFormat24bppRGB);
    
	// keeps the resolution in dots per inch the same
    newMammo->SetResolution(origMammo->GetHorizontalResolution(), 
                            origMammo->GetVerticalResolution());

	// get a graphics object for the new bitmap
	Graphics *grMammo = Graphics::FromImage(newMammo);

	// ensure that scaling is high quality
    grMammo->SetInterpolationMode(InterpolationModeHighQualityBicubic);
    
    // draw the old image onto the new one
    grMammo->DrawImage(origMammo, Dest, sourceX,
		                   sourceY, sourceWidth, sourceHeight,
						   UnitPixel, NULL, NULL, NULL);

	// delete the graphics structure
	delete grMammo;
    return newMammo;
} // --- MainWnd::ScaleByPercent ----------------------------------------------


// ----------------------------------------------------------------------------
// zoomIn
//
// zooms in on a prtion of the image
// ----------------------------------------------------------------------------
void MainWnd::zoomIn(int x, int y) {
	
	int zoomLevel = 60;

	if (smaller != NULL) {
		// get a graphics object for the new bitmap
		Graphics *smGraphics = Graphics::FromImage(smaller);
		
		// get the width of the full mammogram
		//int origImageWidth = mammogram->GetWidth();
		//int origImageHeight = mammogram->GetHeight();

		// get the coordinates in the big original mammogram that
		// are currently being displayed
		int zoomArraySize = zoomInfoVector.size();
		ZoomInfo lastZoomInfo = zoomInfoVector[zoomArraySize -1];

		// get the currently displayed width from the original mammogram
		// and the other coordinates
		int lastOrigImageWidth = lastZoomInfo.getWidth();
		int lastOrigImageHeight = lastZoomInfo.getHeight();
		int lastOrigImageX = lastZoomInfo.getTopLeftX();
		int lastOrigImageY = lastZoomInfo.getTopLeftY();

		// get the width of the smaller mammogram
		int imageWidth = smaller->GetWidth();
		int imageHeight = smaller->GetHeight();
		int imageX = mamSets.getITopLeftX();
		int imageY = mamSets.getITopLeftY();
		// check whether the selected point is part of the displayed mammogram and not
		// something else in the window (we only zoom if clicked on the mammogram)
		if ( (x >= imageX) && (x < (imageX + imageWidth) ) 
			&& (y >= imageY) && (y < (imageY + imageHeight) ) ) {
			//int percentageX = (x / imageWidth);
			//int percentageY = (y / imageHeight);

			// used so we can move from the middle of the zoom box to the top left
			int halfZoomLevel = zoomLevel / 2;

			// the x passed in is where the user clicks. if scaling is say 20% then we
			// should take 10% of the image from this for the top left X since passed x
			// is the middle. beyond this we must take away the distance before the start
			// of the picture. i.e. white space before the image is displayed since the
			// x passed in is for the image as a whole
			int startX = x - (halfZoomLevel * 0.01 * imageWidth) - mamSets.getITopLeftX();
			int startY = y - (halfZoomLevel * 0.01 * imageHeight)  - mamSets.getITopLeftY();
			int rectWidth = zoomLevel * 0.01 * imageWidth;
			int rectHeight = zoomLevel * 0.01 * imageHeight;

			// we must check to ensure out rectangle is not going to head out of the picture
			if (startX < imageX) 
				startX = 0;
			if (startY < imageY) 
				startY = 0;
			if ( (startX + rectWidth) > (imageX + imageWidth) ) 
				startX = imageWidth - rectWidth;
			if ( (startY + rectHeight) > (imageY + imageHeight) ) 
				startY = imageHeight - rectHeight;


			float fractionX = (startX / static_cast<float>(imageWidth));
			float fractionY = (startY / static_cast<float>(imageHeight));



			int newActualX = lastOrigImageX + 
							static_cast<int>(lastOrigImageWidth * fractionX); 
			int newActualY = lastOrigImageY + 
							static_cast<int>(lastOrigImageHeight * fractionY); 
			int newSourceWidth = lastOrigImageWidth * 0.01 * zoomLevel;
			int newSourceHeight = lastOrigImageHeight * 0.01 * zoomLevel;


			// shove the information in a rect structure
			Rect Dest(0,0,imageWidth,imageHeight);

			// ensure that scaling is high quality
			smGraphics->SetInterpolationMode(InterpolationModeHighQualityBicubic);
    
			Bitmap * mammo;
			bool isOverlay = mamSets.getIsOverlay();
			if (isOverlay == true) 
				mammo = overlayMammogram;
			else 
				mammo = mammogram; 
			// draw the old image onto the new one
			smGraphics->DrawImage(mammo, Dest, newActualX,
		                   newActualY, newSourceWidth, newSourceHeight,
						   UnitPixel, NULL, NULL, NULL);
			zoomInfoVector.push_back(ZoomInfo(newActualX, newActualY,
									newSourceWidth,newSourceHeight));
			InvalidateRect(hWnd, NULL, TRUE); 
			UpdateWindow(hWnd);
		}
	
		//Rect compressionRect(10, 40, smaller->GetWidth(), smaller->GetHeight());
		//graphics->DrawImage(smaller, compressionRect);

		delete smGraphics;

			
	}


} // --- zoomIn ---------------------------------------------------------------



// ----------------------------------------------------------------------------
// zoomOut
//
// zooms out from the zoomed portion of the image
// ----------------------------------------------------------------------------
void MainWnd::zoomOut() {
	
	if (smaller != NULL) {
		// get a graphics object for the new bitmap
		Graphics *smGraphics = Graphics::FromImage(smaller);

		// shove the information in a rect structure
		Rect Dest(0,0,smaller->GetWidth(),smaller->GetHeight());
		
		int vectSize = zoomInfoVector.size();
		if (vectSize > 1)
		{
			zoomInfoVector.pop_back();
			int vectSize2 = zoomInfoVector.size();
			ZoomInfo lastRect = zoomInfoVector[vectSize - 2];

			int originalX = lastRect.getTopLeftX();
			int originalY = lastRect.getTopLeftY();
			int originalWidth = lastRect.getWidth();
			int originalHeight = lastRect.getHeight();

		
			// ensure that scaling is high quality
			smGraphics->SetInterpolationMode(InterpolationModeHighQualityBicubic);
    
			Bitmap * mammo;
			bool isOverlay = mamSets.getIsOverlay();
			if (isOverlay == true) 
				mammo = overlayMammogram;
			else 
				mammo = mammogram; 

			// draw the old image onto the new one
			smGraphics->DrawImage(mammo, Dest, originalX,
					               originalY, originalWidth, originalHeight,
								   UnitPixel, NULL, NULL, NULL);

			InvalidateRect(hWnd, NULL, TRUE); 
			UpdateWindow(hWnd);
			delete smGraphics;
		}
	}


} // --- zoomOut --------------------------------------------------------------


// ----------------------------------------------------------------------------
// MainWnd::drawText
//
// A function to draw the text that goes by the side of the image
// ----------------------------------------------------------------------------
bool MainWnd::drawText(HWND hWnd, HDC hDc, Graphics* graphics, long lfHeight) {
	// we take a font size and a device context on which to draw

	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 14, FontStyleRegular, UnitPixel);
	//PointF      pointF(270, 350);
	//SolidBrush  blackBrush(Color(255, 0, 0, 0));
	//graphics->FillRectangle(&blackBrush, 170, 100, 820, 530);
	SolidBrush  textBrush(Color(255, 0, 0, 0));
	//graphics->DrawString(L"WELCOME TO MAMMOGRAM VIEWER",
	//-1, &font, pointF, &transBrush);	 	

	USES_CONVERSION; 
	// a handle to a logical font in memory
	HFONT hf;
	// have black text
	COLORREF g_rgbText = RGB(0, 0, 0);
	// have a white background
	COLORREF g_rgbBackground = RGB(255, 255, 255);
    // anything behind the text is not seen
	SetBkMode(hDc, OPAQUE);

	// make a font non italic of times new roman
    hf = CreateFont(lfHeight, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
	// select a font to use for the device context, i.e. that we will draw with
	SelectObject(hDc, hf);

	// apply the two colours to the text
	SetBkColor(hDc, g_rgbBackground);
	SetTextColor(hDc, g_rgbText);
	
	// the text is in a vector of strings so get an iterator to move through it
	// with an iterator this is implementation independent
	std::vector<std::string*>::iterator iter;

	// this rect defines where we draw the text and so we define a starting rectangle
	RECT prc;
	prc.left = 530;
	prc.right = 900;
	prc.top = 30;
	prc.bottom = 60;

	// declare a regular expression 
	boost::regex correctFileDetails;
	// define one to look for one of the four strings
	const boost::regex fileDetails("LEFT_CC|LEFT_MLO|RIGHT_CC|RIGHT_MLO");
	// make another one that looks for whitespace
	const boost::regex divideBySpace("\\s+");
	boost::smatch wordMatch;
	// if the assignfails this code can't be executed
	try {
			// assign to the reg exp
			correctFileDetails.assign(mamSets.getFileType().c_str());
			
	}

	catch(boost::bad_expression) {
			return false;
	}

	
	//int i = 0;
	std::vector<std::string*> fileInfoVector  = mamSets.getFileInfoVector();	

	RectF rectF(530, 30, 260, 30);

	// loop through the info vector printing the information
	for (iter = fileInfoVector.begin(); iter != fileInfoVector.end(); iter++) {
	//	i++;
			
		// if we are in the section with file information then ensure its information
		// about the right file before printing (it also has stuff for the other 3 views
		if (boost::regex_search(**iter, fileDetails) == true) {
			if(boost::regex_search(**iter, correctFileDetails) == true) {
				// move down the rectangle we draw in
				//prc.top += 30;
				//prc.bottom += 30;
				rectF.Offset(0, 30);
						
				// get the string from the iterator
				std::string toDivide = **iter;
						
				// tokenise the string using whitespace
				boost::sregex_token_iterator lineIter(toDivide.begin(), 
					toDivide.end(), divideBySpace, -1);
					    
				// draw on the screen the first thing in the string and move the text
				// region down
				std::string tes = *lineIter;
				//DrawText(hDc, tes.c_str(), -1, &prc, DT_WORDBREAK);
				graphics->DrawString(A2W(tes.c_str()), -1, &font, rectF,NULL, &textBrush);	 	
				//prc.top += 30;
				//prc.bottom += 30;
				rectF.Offset(0, 30);

				// now get the dimensions from the string and draw
				std::string dimensions("DIMENSIONS ");
				// we have to move over a couple of words to get the fisr dimension
				lineIter ++; lineIter ++;
				std::string x = *lineIter;
				// move another couple for the second
				lineIter ++;lineIter ++;
				std::string y = *lineIter;
						
				std::string toPrint = dimensions + x + " x " + y;
				//DrawText(hDc, toPrint.c_str(), -1, &prc, DT_WORDBREAK);
				graphics->DrawString(A2W(toPrint.c_str()), -1, &font,
					                  rectF,NULL, &textBrush);	 	

				// at the end of the string we have whether there is an overlay
				// it mgiht be advantageous to overload += to simplify this
				lineIter ++; lineIter ++; lineIter ++; lineIter ++; lineIter ++;
						
				//prc.top += 30;
				//prc.bottom += 30;
				rectF.Offset(0, 30);
						
				// set hasOverlay according to this
				std::string overlayStatus = *lineIter;
				if (overlayStatus.find("NON") != std::string::npos) {
					//mamSets.setHasOverlay(false);
					//DrawText(hDc, "HAS NO OVERLAY", -1, &prc, DT_WORDBREAK);
					graphics->DrawString(L"HAS NO OVERLAY", -1, &font,
						rectF,NULL, &textBrush);	 	
				}
				else {
					//mamSets.setHasOverlay(true);
					//DrawText(hDc, "HAS OVERLAY", -1, &prc, DT_WORDBREAK);
					graphics->DrawString(L"HAS OVERLAY", -1, &font, 
						rectF,NULL, &textBrush);	 	
				}

				//prc.top += 30;
				//prc.bottom += 30;
				rectF.Offset(0, 30);

						
				}
				

			}
			else {
				// if its not the line with extra information just print as it is
				//prc.top += 30;
				//prc.bottom += 30;
				rectF.Offset(0, 30);
				//DrawText(hDc, (**iter).c_str(), -1, &prc, DT_WORDBREAK);
				graphics->DrawString(A2W((**iter).c_str()), 
					              -1, &font, rectF,NULL, &textBrush);	 	
			}
		}
		
        // if there was an overlay then display this extra information  
		int currentY = 80;
		if (mamSets.getIsOverlay() == true) {
			//int currentY = 80;
			int stringLength;
			int maxLength = 35;
			int height;
		//	RectF overlayRectF(850, 30, 290, 30);
			// the overlay information class has a vector of strings ready
			// for printing so get that
			OverlayInfo* overlay = mamSets.getOverlay();
			std::vector<std::string> overlayV = overlay->getToPrintVector();
			std::vector<std::string>::iterator vecIt;
			std::string overInfo;
			prc.left+= 320;
			prc.right += 320;
			prc.top -= 400;
			prc.bottom -= 380;
			Font        font(&fontFamily, 16, FontStyleRegular, UnitPixel);
			for (vecIt = overlayV.begin(); vecIt != overlayV.end(); vecIt++) {
				prc.top += 60;
				prc.bottom += 60;
				//overlayRectF.Offset(0, 30);
				overInfo = *vecIt;
				stringLength = overInfo.size();
				height = ((stringLength / maxLength) + 1) * 30;
				RectF overlayRectF(850, currentY, 290, height);
				currentY = currentY + height + 15;
				//DrawText(hDc, overInfo.c_str(), -1, &prc, DT_WORDBREAK);
				graphics->DrawString(A2W(overInfo.c_str()), -1, 
					&font, overlayRectF,NULL, &textBrush);

			}
		}
		// get a graphics object for drawing things
	     //Graphics* graphics = Graphics::FromHWND(hWnd);
		 // here a background is added to the text 
		int startX = 500;
		int width = 300;
		int startY = 50;
		int height = 450;
			Pen blackPen(Color(255, 0, 0, 0), 3);
			SolidBrush brush(Color(100, 55,55,0));
			LinearGradientBrush linGrBrush(Point(startX, startY),
							Point(startX + width, startY + height),
							Color(80, 250, 250, 250), Color(80, 0, 0, 50)); 
			graphics->FillRectangle(&linGrBrush, 500, 50, 300, 450);
			graphics->DrawRectangle(&blackPen, startX, startY, width, height);
			//MoveToEx(hDc, 500, 50, NULL);
			//LineTo(hDc, 800, 50);
			//LineTo(hDc, 800, 500);
			//LineTo(hDc, 500, 500);
			//LineTo(hDc, 500, 50);

			// if we give overlay information then draw a box round that too
			if (mamSets.getIsOverlay() == true) {
				SolidBrush brush(Color(100,102,204,255));
			    startX = 840;
				width = 320;
				startY = 50;
				height = currentY;
				LinearGradientBrush linGrBrushB(Point(startX, startY),
							Point(startX + width, startY + height),
							Color(80, 250, 250, 250), Color(80, 0, 0, 50)); 
				graphics->FillRectangle(&linGrBrushB, startX, startY, width, height);
				graphics->DrawRectangle(&blackPen, startX, startY, width, height);
				//graphics->DrawRectangle(
			//	MoveToEx(hDc, startX, startY, NULL);
			//	LineTo(hDc, startX + width, startY);
			//	LineTo(hDc, startX + width, height);
			//	LineTo(hDc, startX, height);
			//	LineTo(hDc, startX, startY);
			}

	
        DeleteObject(hf);
		//delete graphics;
		return true;

} // --- MainWnd::drawText ----------------------------------------------------



// ----------------------------------------------------------------------------
// drawTitle
//
// draws the title when starting the program
// ----------------------------------------------------------------------------
void MainWnd::drawTitle(HWND hWnd, HDC hDc,Graphics* graphics, long lfHeight) {
	
	// set fonts and colors, see drawText for more information, this
	// is the same
	//HFONT hf;
	//COLORREF g_rgbText = RGB(0, 0, 0);
	//COLORREF g_rgbBackground = RGB(255, 255, 255);
         //long lfHeight;
	//SetBkMode(hDc, OPAQUE);
    //hf = CreateFont(30, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
	//SelectObject(hDc, hf);
	//SetBkColor(hDc, g_rgbBackground);
	//SetTextColor(hDc, g_rgbText);
		 	
	//RECT prc;
	//prc.left = 350;
	//prc.right = 750;
	//prc.top = 110;
	//prc.bottom = 140;
			
	//DrawText(hDc, "Welcome to mammogram viewer", -1, &prc, DT_WORDBREAK);
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 34, FontStyleBold, UnitPixel);
	PointF      pointF(270, 350);
	//SolidBrush  blackBrush(Color(255, 0, 0, 0));
	//graphics->FillRectangle(&blackBrush, 170, 100, 820, 530);
	SolidBrush  transBrush(Color(125, 0, 0, 0));
	graphics->DrawString(L"WELCOME TO MAMMOGRAM VIEWER", -1, &font, pointF, &transBrush);	 	
    //DeleteObject(hf);

	//SolidBrush brush(Color(100, 55,55,0));
	//graphics->FillRectangle(&brush, 500, 50, 300, 450);


} // --- drawTitle -------------------------------------------------------------




// -----------------------------------------------------------------------------
// drawEllipse
//
// draws an ellipse
// ----------------------------------------------------------------------------
void MainWnd::drawEllipse(HDC hDc, int startX, int startY, int endX, int endY) {
	//Brush brush(Color(100, 55,55,0));
	//SolidBrush
	// the values passed in are the bounding rectangle but it may be end X is actually
	// higher than start X etc. we must sort this so that we know which two coordinates are top
	// left
	// get the width of the smaller mammogram
		
	int topLeftX;
	int topLeftY;
	int bottomRightX;
	int bottomRightY;
	//if (startX <= endX) {
		topLeftX = startX;
		bottomRightX = endX;
	//}
	//else {
	//	topLeftX = endX;
	//	bottomRightX = startX;
	//}
	//if (startY <= endY) {
		topLeftY = startY;
		bottomRightY = endY;
	//}
	//else {
	//	topLeftY = endY;
	//	bottomRightY = startY;
	//}
	int width = bottomRightX - topLeftX;
	int height = bottomRightY - topLeftY;
	const Pen pen(Color(255, 0,0,180), 1);
	Ellipse(hDc, startX, startY, endX, endY);
	Graphics* g = Graphics::FromHWND(hWnd);
	// redraw the image as we go don't want lots of blue lines over it
	// we want to draw all the mammogram so get its full size and position 40 pixels down
	Rect compressionRect(mamSets.getITopLeftX(), mamSets.getITopLeftY(),
		smaller->GetWidth(), smaller->GetHeight());
	g->DrawImage(smaller, compressionRect);
	g->DrawEllipse(&pen, topLeftX, topLeftY, width, height);
	delete g;
	//Graphics::DrawEllipse();
	
} // --- drawEllipse ----------------------------------------------------------



// ----------------------------------------------------------------------------
// draw
//
// where all drawing is done from
// ----------------------------------------------------------------------------
void MainWnd::draw(HWND hWnd) {
    // a device context onto which we draw     
	HDC hDc;

    PAINTSTRUCT Ps;

	// since most things are done in one font there is a variable here for its size
	long lfHeight;
		 
      
		 // here we just check the font size is ok, note this is not a normal
		 // point size its related to the device
		 hDc = GetDC(NULL);
		lfHeight = -MulDiv(12, GetDeviceCaps(hDc, LOGPIXELSY), 72);
		ReleaseDC(NULL, hDc);

		 // now we begin graphics drawing
		 hDc = BeginPaint(hWnd, &Ps);
		 
		 // get a graphics object for drawing things
	     Graphics* graphics = new Graphics(hDc);
		// hDc = graphics->GetHDC();

	     // draw stuff so long as there is a mammogram
		 if (smaller != NULL) {
		//	 LinearGradientBrush linGrBrush(Point(0, 0),Point(1280, 1024),
		//	Color(100, 255, 255, 255), Color(100, 0, 0, 0)); 
		//	graphics->FillRectangle(&linGrBrush, 0, 0, 1280,1024);
			// we want to draw all the mammogram so get its full size and position 40 pixels down
			 Rect compressionRect(mamSets.getITopLeftX(), 
				 mamSets.getITopLeftY(), smaller->GetWidth(), smaller->GetHeight());
			graphics->DrawImage(smaller, compressionRect);
			
			
			if (mamSets.getIconType() == MammoviewSettings::drawing) {
				if (mamSets.getMouseEndX()!= -1) {
					drawEllipse(hDc, mamSets.getMouseStartX(), mamSets.getMouseStartY(),
						mamSets.getMouseEndX(), mamSets.getMouseEndY());
				}
			}
			

			// now call the drawText method for all mammogram information
			drawText(hWnd, hDc, graphics, lfHeight);
			//Graphics::g
			
		 }
		 // otherwise draw the title
		 else {
			 drawTitle(hWnd, hDc, graphics, lfHeight);
		 }
		 
		 //ReleaseDC(hWnd, hDc);
		 delete graphics;
         EndPaint(hWnd, &Ps);
		 


	}


VOID OnPaint(HDC hdc)
{
   Graphics graphics(hdc);
   Pen      pen(Color(255, 0, 0, 255));
   graphics.DrawLine(&pen, 0, 0, 200, 100);
   SolidBrush brush(Color(100, 55,55,0));
   graphics.FillRectangle(&brush, 500, 50, 300, 450);
}




bool MainWnd::openAndProcessImage(const char* imageFileName) {
	// load the mammogram
		 bool hasOpened;
		 hasOpened = loadImage(imageFileName);
		 if (hasOpened == false) return false;
	
		std::string imageName(imageFileName);
		// get a file name for the ics file
		mamSets.setInfoFileName(getInfoFileName(imageName));
		std::vector<std::string*> fInfoVec = getFileInformation(mamSets.getInfoFileName());
		mamSets.setFileInfoVector(fInfoVec);

		if (mamSets.getHasOverlay() == true) {
			std::string overlayFileName = getOverlayFileName(imageFileName);
			// get an overlay class to construct itself (could use set methods)
			OverlayInfo* overlay = new OverlayInfo();
			overlay->selfSet(overlayFileName, 1);
			mamSets.setOverlay(overlay);
		
			RectF origRect;
			Unit unit;
			PixelFormat pixFormat = mammogram->GetPixelFormat();
			mammogram->GetBounds(&origRect, &unit);
			// make a new mammogram with an overlay drawn on it
			// images are about 50 megs so memory impact should be ok
			overlayMammogram = mammogram->Clone(origRect, pixFormat);
			int width = overlayMammogram->GetWidth();
	
			// get the vector of overlay pixels and draw them on the image
			std::vector<int> overlayVec = overlay->getBoundary();
			std::vector<int>::iterator pixelIt;
			int x;
			int y;
			//Color color
			for (pixelIt = overlayVec.begin(); pixelIt < overlayVec.end(); pixelIt++) {
				x = *pixelIt;
				pixelIt++;
				y = *pixelIt;
				overlayMammogram->SetPixel(x,y, Color(255,0,0));
			}
			// we need to reset the coordinates for the user selected area
			mamSets.setMouseStartX(0);
			mamSets.setMouseStartY(0);
			mamSets.setMouseEndX(0);
			mamSets.setMouseEndY(0);
		}
		InvalidateRect(hWnd, NULL, TRUE); 
		UpdateWindow(hWnd);
		// redraw everything
		//InvalidateRect(hWnd, NULL, TRUE); 
		//UpdateWindow(hWnd);
		return hasOpened;
	
}



void MainWnd::openCGPLocation() {
	// A struct that represents a file dialog
	OPENFILENAME ofn;
	// an array of chars for the file name
	char cgpDataFilename[MAX_PATH] = "";
    // set all the memory to zero
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = cgpDataFilename;
	// a windows costant for file name size
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "txt";

	bool hasLoaded = false;
	// provided we got a filename then carry on
	if(GetOpenFileName(&ofn))
	{
	
		hasLoaded = cgp.loadInputs(cgpDataFilename);
		
	}
	if (hasLoaded == false) {
		MessageBox(NULL, "File not found or contains wrong information", NULL, NULL);
	}




}



// ----------------------------------------------------------------------------
// MainWnd::openFile
//
// brings up a fle dialog and then does processing to extract the file
// and its related files
// ----------------------------------------------------------------------------
bool MainWnd::openFile() {
	// A struct that represents a file dialog
	OPENFILENAME ofn;
	// an array of chars for the file name
	char imageFileName[MAX_PATH] = "";
    // set all the memory to zero
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = "Png Files (*.png)\0*.png\0Bitmap Files (*.bmp)\0*.bmp\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = imageFileName;
	// a windows costant for file name size
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "txt";
	bool isLoaded = false;
	// provided we got a filename then carry on
	if(GetOpenFileName(&ofn))
	{
		mamSets.setIsOverlay(false);
		isLoaded = openAndProcessImage(imageFileName);
		if (isLoaded == true) {
			std::vector<std::string> filenameVect = mamSets.getImagePathVector();
			filenameVect.push_back(imageFileName);
			mamSets.setImagePathVector(filenameVect);
			mamSets.setCurrentImageIndex(mamSets.getCurrentImageIndex() + 1);
		}
		/*
		// load the mammogram
		loadImage(imageFileName);
		
	
		std::string imageName(imageFileName);
		// get a file name for the ics file
		mamSets.setInfoFileName(getInfoFileName(imageName));
		std::vector<std::string*> fInfoVec = getFileInformation(mamSets.getInfoFileName());
		mamSets.setFileInfoVector(fInfoVec);
		std::string overlayFileName = getOverlayFileName(imageFileName);
		// get an overlay class to construct itself (could use set methods)
		OverlayInfo* overlay = new OverlayInfo();
		overlay->selfSet(overlayFileName, 1);
		mamSets.setOverlay(overlay);
		
		RectF origRect;
		Unit unit;
		PixelFormat pixFormat = mammogram->GetPixelFormat();
		mammogram->GetBounds(&origRect, &unit);
		// make a new mammogram with an overlay drawn on it
		// images are about 50 megs so memory impact should be ok
		overlayMammogram = mammogram->Clone(origRect, pixFormat);
		int width = overlayMammogram->GetWidth();
	
		// get the vector of overlay pixels and draw them on the image
		std::vector<int> overlayVec = overlay->getBoundary();
		std::vector<int>::iterator pixelIt;
		int x;
		int y;
		//Color color
		for (pixelIt = overlayVec.begin(); pixelIt < overlayVec.end(); pixelIt++) {
		x = *pixelIt;
		pixelIt++;
		y = *pixelIt;
		overlayMammogram->SetPixel(x,y, Color(255,0,0));
		}*/

		//InvalidateRect(hWnd, NULL, TRUE); 
		//UpdateWindow(hWnd);
	}
	// redraw everything
	return isLoaded;
	
} // --- setUpFileDialog ------------------------------------------------------




// ---------------------------------------------------------------------------
// openCaseDirectory
//
// allows the user to choose and open a directory of cases
// ---------------------------------------------------------------------------
bool MainWnd::openCaseDirectory() {

	// signals that file was opened successfully
	bool isOpened = false;

	TCHAR selectedName[MAX_PATH];

	// make a structure for browsing for directories
	BROWSEINFO bi = {0};
	ZeroMemory(&bi, sizeof(BROWSEINFO)); 
	bi.hwndOwner = hWnd;
	bi.pidlRoot = CSIDL_DESKTOP;
	bi.pszDisplayName = selectedName;
	bi.lpszTitle = NULL;
	bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_USENEWUI;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	// now we call the function that allows the user to browse for a folder
	// this returns the directory as some sort of id in the windows namespace
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	// some random variable to which information is later written
	ULONG celtFetched;

	// each itdividual item is placed into this, i.e. its particular id
	LPITEMIDLIST pidlItems = NULL;

	// the folder object used to represent the selected folder
	IShellFolder *databaseFolders = NULL;


	// the temporary root folder object used to get sub folder object
	IShellFolder *psfDeskTop = NULL;
	
	// used to get everything within our folder
	LPENUMIDLIST ppenum = NULL;
	
	// an array of chars to put the file / folder name
	TCHAR pszDisplayName[MAX_PATH];
	
	// a string into which to place the file/folder name
	STRRET strDispName;

	// used to check results of each stage
	HRESULT hr;
	// check we got a valid id
	if( pidl ) {
		// make a char array into which the path is to be written
        TCHAR folderPath[MAX_PATH];

		// now get the path to this item from the id
		if( SHGetPathFromIDList( pidl, folderPath ) ) { 
			DebugClass::write(std::string("the root is") + std::string(folderPath) + "\n");

			// now in order to work with folders we need an IShellFolder object and we start
			// by getting the root which is desktop, then we can use this one to make
			// one for the id we have
			hr = SHGetDesktopFolder(&psfDeskTop);
			hr = psfDeskTop->BindToObject(pidl, NULL, 
			IID_IShellFolder, (LPVOID *) &databaseFolders);
			psfDeskTop->Release();
			mamSets.setDatabaseFolder(databaseFolders);
			// now we create the enum object which is used to get everything thats in out folder
			hr = databaseFolders->EnumObjects(NULL,SHCONTF_FOLDERS , 
					&ppenum);
			mamSets.setFolderEnum(ppenum);
			// now we get each item putting it into pidlitems
			
				if (ppenum->Next(1,&pidlItems, &celtFetched)
					== S_OK && (celtFetched) == 1) {
					// now we get the file name and turn into a string with the total path
					databaseFolders->GetDisplayNameOf(pidlItems, 
						SHGDN_INFOLDER, &strDispName);
					StrRetToBuf(&strDispName, pidlItems, pszDisplayName, MAX_PATH);
					std::string totalPath(std::string(folderPath) + "\\" + 
						std::string(pszDisplayName));
					
					// used to get everything within our folder
					LPENUMIDLIST fileEnum = NULL;

					// each itdividual item is placed into this, i.e. its particular id
					LPITEMIDLIST fileItems = NULL;

					// the folder object used to represent the selected folder
					IShellFolder *caseFolders = NULL;
				//	hr = SHGetDesktopFolder(&psfDeskTop);
					hr = databaseFolders->BindToObject(pidlItems, NULL, 
						IID_IShellFolder, (LPVOID *) &caseFolders);
				//	psfDeskTop->Release();
					mamSets.setCaseFolder(caseFolders);
					hr = caseFolders->EnumObjects(NULL,
						SHCONTF_FOLDERS | SHCONTF_NONFOLDERS , &fileEnum);
					mamSets.setCaseEnum(fileEnum);

					while (fileEnum->Next(1,&fileItems, &celtFetched)
						== S_OK && (celtFetched) == 1) {
						// now we get the file name and turn into a string with the total path
						caseFolders->GetDisplayNameOf(fileItems, SHGDN_FORPARSING, 
							&strDispName);
						StrRetToBuf(&strDispName, fileItems,
							pszDisplayName, MAX_PATH);
						//std::string file(std::string(totalPath) + "\\" + std::string(pszDisplayName));
						std::string currentFile(pszDisplayName);
						if (currentFile.find(".png") != std::string::npos) {
							mamSets.setIsOverlay(false);
							isOpened = openAndProcessImage(currentFile.c_str());
							if (isOpened == true) {
								std::vector<std::string> filenameVect 
									= mamSets.getImagePathVector();
								filenameVect.push_back(currentFile);
								mamSets.setImagePathVector(filenameVect);
								mamSets.setCurrentImageIndex(mamSets.getCurrentImageIndex()
														+ 1);
								// turn off overlay
							//isOpened = true;
							}
							break;
						}

						//std::string firstFile(totalPath + "\\" + 
						DebugClass::write(std::string("First file found is: ") 
							+ std::string(pszDisplayName) + "\n");
					}
				}
          }
            else
            {
				return false;
               
            }
		}

	
			return isOpened;
		
} // --- openCaseDirectory


// ----------------------------------------------------------------------------
// MainWnd::getInfoFileName
//
// get the name of the ics file
// ----------------------------------------------------------------------------
std::string MainWnd::getInfoFileName(std::string imageFileName) {
	//boost::regex re("\\s+");

	const boost::regex e("(.+)_(\\w+)_(\\w+)\\.");	
	const std::string info_format("\\1-\\2-\\3");
	// no copy means we don't grab what does not match the reg exp, otherwise we replace
	// what is matched in the whole expression ie the whole lot up to the . and replace it
	// with whats pretty much the same string since its grabbed with \\ but with - not _
	std::string returnS = 
	boost::regex_replace(imageFileName, e, info_format, boost::format_no_copy | boost::format_perl);
	returnS += ".ics";

	// some extra code to set which image it is out of the 4
	const boost::regex searchE("LEFT_CC|LEFT_MLO|RIGHT_CC|RIGHT_MLO");
	boost::smatch mResults;
	boost::regex_search(imageFileName, mResults, searchE);  
	boost::smatch::iterator iter = mResults.begin();
	mamSets.setFileType(*iter);
	

	  return returnS;
} // --- MainWnd::ProcessFileName ---------------------------------------------


// ----------------------------------------------------------------------------
// getOverlayFileName
//
// note this is just a hacked versio of the avoe method and should be rewritten
// when i have more time so it does a search with match_results
// ----------------------------------------------------------------------------
std::string MainWnd::getOverlayFileName(std::string imageFileName) {
	//boost::regex re("\\s+");

	const boost::regex e("(.+)_(\\w+)_(\\w+)\\.(LEFT_CC|LEFT_MLO|RIGHT_CC|RIGHT_MLO)");	
	const std::string info_format("\\1_\\2_\\3\\.\\4");
	// no copy means we don't grab what does not match the reg exp, otherwise we replace
	// what is matched in the whole expression ie the whole lot up to the . and replace it
	// with whats pretty much the same string since its grabbed with \\ but with - not _
	std::string returnS = 
	boost::regex_replace(imageFileName, e, info_format,
	             boost::format_no_copy | boost::format_perl);
	returnS += ".OVERLAY";

	  return returnS;
} // --- MainWnd::getOverlayFileName


// ----------------------------------------------------------------------------
// MainWnd::getFileInformation
//
// ----------------------------------------------------------------------------
std::vector<std::string*> MainWnd::getFileInformation(std::string infoFile) {
//	std::fstream in(fileName);
	std::vector<std::string*> strVector;
	std::string* fileDataItem;
	char buf[120];
	std::ifstream in(infoFile.c_str());
	while(in.getline(buf , 120)) {
		fileDataItem = new std::string(buf);
		if ( (fileDataItem->find("OVERLAY") != std::string::npos) 
			&& (fileDataItem->find(mamSets.getFileType()) != std::string::npos) ) {
			if (fileDataItem->find("NON") != std::string::npos)
			{
				mamSets.setHasOverlay(false);
			}
			else {
				mamSets.setHasOverlay(true);
			}
		}
		strVector.push_back(fileDataItem);
	}

	return strVector;
} // MainWnd::getFileInformation


// ----------------------------------------------------------------------------
// getNextImage
//
// finds the next image in the case directory
// ----------------------------------------------------------------------------
void MainWnd::getNextImage() {
	
	// now we call the function that allows the user to browse for a folder
	// this returns the directory as some sort of id in the windows namespace
	//LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	// some random variable to which information is later written
	ULONG celtFetched;
	
	// an array of chars to put the file / folder name
	TCHAR pszDisplayName[MAX_PATH];
	
	// a string into which to place the file/folder name
	STRRET strDispName;

	HRESULT hr;

	// used to check results of each stage
	//HRESULT hr;
	int	currentImageIndex = mamSets.getCurrentImageIndex();
	std::vector<std::string> stringVector = mamSets.getImagePathVector();
	if (currentImageIndex == (stringVector.size() - 1)) {
		if (std::string("RIGHT_MLO") == mamSets.getFileType()) {
			// each itdividual item is placed into this, i.e. its particular id
			LPITEMIDLIST pidlItems = NULL;
			IShellFolder* databaseFolder = mamSets.getDatabaseFolder();
			LPENUMIDLIST folderEnum = mamSets.getFolderEnum();

			if (folderEnum->Next(1,&pidlItems, &celtFetched)
				== S_OK && (celtFetched) == 1) {
					// now we get the file name and turn into a string with the total path
					databaseFolder->GetDisplayNameOf(pidlItems,
						SHGDN_INFOLDER, &strDispName);
					StrRetToBuf(&strDispName, pidlItems, pszDisplayName,
						       MAX_PATH);
					//std::string totalPath(std::string(folderPath) 
					//+ "\\" + std::string(pszDisplayName));
					
					// used to get everything within our folder
					LPENUMIDLIST fileEnum = NULL;

					// each itdividual item is placed into this, i.e. its particular id
					LPITEMIDLIST fileItems = NULL;

					// the folder object used to represent the selected folder
					IShellFolder *caseFolder = NULL;
				//	hr = SHGetDesktopFolder(&psfDeskTop);
					hr = databaseFolder->BindToObject(pidlItems, NULL,
						IID_IShellFolder, (LPVOID *) &caseFolder);
				//	psfDeskTop->Release();
					mamSets.setCaseFolder(caseFolder);
					hr = caseFolder->EnumObjects(NULL,
						SHCONTF_FOLDERS | SHCONTF_NONFOLDERS , &fileEnum);
					mamSets.setCaseEnum(fileEnum);

					while (fileEnum->Next(1,&fileItems, &celtFetched) == S_OK && (celtFetched) == 1) {
						// now we get the file name and turn into a string with the total path
						caseFolder->GetDisplayNameOf(fileItems, SHGDN_FORPARSING, &strDispName);
						StrRetToBuf(&strDispName, fileItems, pszDisplayName, MAX_PATH);
						//std::string file(std::string(totalPath) + "\\" + std::string(pszDisplayName));
						std::string currentFile(pszDisplayName);
						if (currentFile.find(".png") != std::string::npos) {
							mamSets.setIsOverlay(false);
							openAndProcessImage(currentFile.c_str());
							std::vector<std::string> filenameVect = mamSets.getImagePathVector();
							filenameVect.push_back(currentFile);
							mamSets.setImagePathVector(filenameVect);
							mamSets.setCurrentImageIndex(mamSets.getCurrentImageIndex() + 1);
							// turn off overlay
							
							break;
						} //if

						//std::string firstFile(totalPath + "\\" + 
						DebugClass::write(std::string("First file found is: ") +
							         std::string(pszDisplayName) + "\n");
					} //while
				} //if



			}//if
		else {
		

			// each itdividual item is placed into this, i.e. its particular id
			//LPITEMIDLIST pidlItems = NULL;

			// the folder object used to represent the selected folder
			IShellFolder *caseFolders = NULL;


			// the temporary rool folder object used to get sub folder object
			IShellFolder *psfDeskTop = NULL;
			SHGetDesktopFolder(&psfDeskTop);
	
			// used to get everything within our folder
			LPENUMIDLIST fileEnum = mamSets.getCaseEnum();
	
		

			// each itdividual item is placed into this, i.e. its particular id
			LPITEMIDLIST fileItems = NULL;

			//psfDeskTop->BindToObject(fileItems, NULL, IID_IShellFolder, (LPVOID *) &caseFolders);
			//		psfDeskTop->Release();

			caseFolders = mamSets.getCaseFolder();

			while (fileEnum->Next(1,&fileItems, &celtFetched) == S_OK && (celtFetched) == 1) {
				// now we get the file name and turn into a string with the total path
				caseFolders->GetDisplayNameOf(fileItems, SHGDN_FORPARSING, &strDispName);
				StrRetToBuf(&strDispName, fileItems, pszDisplayName, MAX_PATH);
				//std::string file(std::string(totalPath) + "\\" + std::string(pszDisplayName));
				std::string currentFile(pszDisplayName);
				if (currentFile.find(".png") != std::string::npos) {
					mamSets.setIsOverlay(false);
					openAndProcessImage(currentFile.c_str());
					std::vector<std::string> filenameVect = mamSets.getImagePathVector();
					filenameVect.push_back(currentFile);
					mamSets.setImagePathVector(filenameVect);
					mamSets.setCurrentImageIndex(mamSets.getCurrentImageIndex() + 1);
					// turn off overlay
							
					break;
				}

				//std::string firstFile(totalPath + "\\" + 
				DebugClass::write(std::string("First file found is: ") + 
					std::string(pszDisplayName) + "\n");
			}
		}
	}
	else {
		currentImageIndex++;
		std::string filename(stringVector[currentImageIndex]);
		mamSets.setIsOverlay(false);
		openAndProcessImage(filename.c_str());
		mamSets.setCurrentImageIndex(currentImageIndex);
	}

	


} // --- getNextImage ---------------------------------------------------------




// ----------------------------------------------------------------------------
// getPreviousImage
//
// we have the opportunity to go forwards and backwards through images,this goes
// back
// ----------------------------------------------------------------------------
void MainWnd::getPreviousImage() {
	std::vector<std::string> filenameVect = mamSets.getImagePathVector();
	
	int vectIndex = mamSets.getCurrentImageIndex();
	if (vectIndex > 0) {
		vectIndex--;
		std::string imagePath = filenameVect[vectIndex];
		openAndProcessImage(imagePath.c_str());
		mamSets.setCurrentImageIndex(vectIndex);
	}
					

} // --- getPreviousImage -----------------------------------------------------



// ----------------------------------------------------------------------------
// getHighlightedPixels
//
// ----------------------------------------------------------------------------
PixelArray<unsigned short> MainWnd::getHighlightedPixels() {

	// first of all get all all the data about the selected area in the client area
	// note that although an ellipse was selected we shall use for rectangle for now
	// for simplicity (the ellipse can be found from this)
	int mouseImageX1 = mamSets.getMouseStartX() - mamSets.getITopLeftX();
	int mouseImageY1 = mamSets.getMouseStartY() - mamSets.getITopLeftY();
	int mouseImageX2 = mamSets.getMouseEndX() - mamSets.getITopLeftX();
	int mouseImageY2 = mamSets.getMouseEndY() - mamSets.getITopLeftY();

	int startX;
	int startY;
	int endX;
	int endY;
	if (mouseImageX1 > mouseImageX2) {
		startX = mouseImageX2;
		endX = mouseImageX1;
	}
	else {
		startX = mouseImageX1;
		endX = mouseImageX2;
	}
	if (mouseImageY1 > mouseImageY2) {
		startY = mouseImageY2;
		endY = mouseImageY1;
	}
	else {
		startY = mouseImageY1;
		endY = mouseImageY2;
	}

	
	//int width = mamSets.getMouseStartX() - mamSets.getMouseEndX();
	//int height = mamSets.getMouseStartY() - mamSets.getMouseEndY();
	int width = endX - startX;
	int height = endY - startY;
	

	// now we need to convert these to fractions ready to convert into the full image (mammogram)
	float startXFrac = static_cast<float>(startX) / static_cast<float>(smaller->GetWidth());
	float startYFrac = static_cast<float>(startY) / static_cast<float>(smaller->GetHeight());
	float widthFrac = static_cast<float>(width) / static_cast<float>(smaller->GetWidth());
	float heightFrac = static_cast<float>(height) / static_cast<float>(smaller->GetHeight());

	// at this point we need to find out what portion of the full mammogram was on the screen
	// when the user selected the ellipse as it can only be a portion of this
	int vectSize = zoomInfoVector.size();
	ZoomInfo currentZoom = zoomInfoVector[vectSize - 1];
	int zoomStartX = currentZoom.getTopLeftX();
	int zoomStartY = currentZoom.getTopLeftY();
	int zoomWidth = currentZoom.getWidth();
	int zoomHeight = currentZoom.getHeight();

	// finally we map the selected ellipse to the original mammogram
	int actualX = static_cast<int>( static_cast<float>(zoomStartX) + 
		(startXFrac * static_cast<float>(zoomWidth)) );
	int actualY = static_cast<int>( static_cast<float>(zoomStartY) + 
		(startYFrac * static_cast<float>(zoomHeight)) );
	int actualWidth = static_cast<int>( widthFrac * static_cast<float>(zoomWidth));
	int actualHeight = static_cast<int>( heightFrac * static_cast<float>(zoomHeight));

	// at this point we now know what has been selected in terms of the original
	// mammogram. however we are not going to read from the gdi bitmap called
	// "mammogram" as windows has dificulties with 16 and 12 bit grayscale, its not 
	// supported (although you can select 16 as an option, perhaps for in future)
	// thus we open the .1 file which has the raw bytes and to avoid using anymore
	// memory we manipulate the file pointer to get what we need

	// then get the filename for the current image which ends png
	std::vector<std::string> pathVector = mamSets.getImagePathVector();
	int pathVectorIndex = mamSets.getCurrentImageIndex();

	// define an array into which pixels are to be written
	unsigned short* selectedPixelArray = NULL;
	selectedPixelArray = new unsigned short[actualWidth * actualHeight];

	if (pathVectorIndex != -1) {
		std::string pngFilePath = pathVector[pathVectorIndex];
		// provided there was a file open (image displayed) we find where in the 
		// filename .png occurs and replace this with .LJPEG.1 which is the raw byte
		// version created by the jpeg conversion program
		int startPos = pngFilePath.find(".png");
		std::string rawDataPath = pngFilePath.replace(startPos, 4, ".LJPEG.1");
		// now it is time to open up the file and get the bytes
		std::ifstream in(rawDataPath.c_str());
		int mammogramWidth = mammogram->GetWidth();

		// this is where we are to start if we view the pixels as a linear array
		int pixelArrayStart = (actualY * mammogramWidth) + actualX;
		int currentIndex;
		int lineIndex;
		// since pixels are 2 bytes in this 12 bit grayscale use 2 pixels for them
		unsigned char byteA;
		unsigned char byteB;
		unsigned short mask = 0x0F00;
		unsigned short currentVal;

		//float thetestone = 5.88;
		//int gg = static_cast<int>(thetestone);
		//std::stringstream atoPrint;
		//atoPrint << "int: " << gg << "\n";
		//DebugClass::write(atoPrint.str());
		int fillArrayIndex;

		std::stringstream toPrint;
		toPrint << "width: " << actualWidth << "height " << actualHeight;
		DebugClass::write(toPrint.str());

		// loop over the number of vertical pixels in the selected area
		for (int i = 0; i < actualHeight; i++) {
			// each iteration of this loop we jump to the start of a width row
			// in the image (starting where the user clicked not the beginning of the row
			// necessarly. we must multipl by 2 since there are 2 bytes per pixel
			lineIndex = (pixelArrayStart + (i * mammogramWidth)) * 2;
			in.seekg(lineIndex, std::ios::beg);

			// loop over the number of horizontal pixels in the selected area
			for (int j = 0; j < actualWidth; j++) {
				in.read( (char*)&byteA, 1); 
				in.read((char*)&byteB, 1);
				currentVal = byteA;
				currentVal = currentVal << 8;
				currentVal = currentVal & mask;
				currentVal += byteB;

				fillArrayIndex = (i * actualWidth) + j;
				selectedPixelArray[fillArrayIndex] = currentVal;
				std::stringstream toPrintEx;
				toPrintEx << "index: " << fillArrayIndex << " i: "
					<< i << " j: " << j << "\n";
				DebugClass::write(toPrintEx.str());
			}

		}

		in.close();

	}
	PixelArray<unsigned short> pixArray(width, height, selectedPixelArray);
	pixArray.setArray(selectedPixelArray);
	pixArray.setWidth(actualWidth);
	pixArray.setHeight(actualHeight);

	//int aa = 1;

	return pixArray;
} // --- getHighLightedPixels -------------------------------------------------



DWORD    WINAPI MainWnd::ThrdFunc(LPVOID param) {
	CGP* cgp = static_cast<CGP*>(param);
//	cgp->beginTrainingCGP(hWnd);
	return 0;

}



//-----------------------------------------------------------------------------
// MainWndProc
//
// The window procedure for the main window, deals with the different types
// of messages received
// ----------------------------------------------------------------------------
LRESULT CALLBACK MainWnd::WndProc(HWND hWnd, UINT Msg,
                             WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
    PAINTSTRUCT  ps;
	
	// depending on the type of message process it
	switch(Msg)
	{
	// does all drawing on the window
    case WM_PAINT:
//		if (shouldPaint == true) {
			//hdc = BeginPaint(hWnd, &ps);
			//SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
			//OnPaint(hdc);
			draw(hWnd);
			//EndPaint(hWnd, &ps);
//		}
//		else shouldPaint = true;
	//	LockWindowUpdate(NULL);
	   // draw(hWnd);
	//	LockWindowUpdate(hWnd);
		
	break;
	
	// this message can come from a variety of sources so we must switch on lparam
    case WM_COMMAND:
		
        switch(LOWORD(wParam))
		{
			case IDM_BUTTON1:
				{
					getPreviousImage();
				}
			break;
			case IDM_BUTTON2:
				{
					getNextImage();
				}
				break;
			// if the used wishes to end then post something to exit the message loop
			case ID_FILE_EXIT:
				PostQuitMessage(WM_QUIT);
			break;
			// if the user wishes to load an image then call the open dialog function
			case ID_FILE_LOAD:
				if (openFile() != true) {
					MessageBox(NULL, "Invalid file", NULL, NULL);
				}
			break;
			case ID_CGP_CHOOSEDIRECTORY:
				bool isOpened;
				isOpened = openCaseDirectory();
				if (isOpened == true) {
					ShowWindow(forwardButton, SW_SHOW);
					ShowWindow(backButton, SW_SHOW);
				}
				else MessageBox(NULL, "Invalid folder", NULL, NULL);
			break;
			case ID_CGP_ADDTOINPUTS:
			{
				if (mamSets.getMouseEndX() != -1) {
					changeCurrentCursor(IDC_WAIT, true);
					PixelArray<unsigned short> pixArray = getHighlightedPixels();
					int pixWidth = pixArray.getWidth();
					int pixHeight = pixArray.getHeight();
					unsigned short* pixels = pixArray.getArray();
					//unsigned short* a = getHighlightedPixels();
					cgpDialog.createCGPIOAddDialog(hWnd,mamSets.getOverlay(),
						cgp, pixels, pixWidth, pixHeight);
					delete pixels;
					changeCurrentCursor(IDC_ARROW, true);
				}
				else {
					MessageBox(NULL, "There is no input currently selected", NULL, NULL);
				}
			}
			break;
			case ID_CGP_TRAINNETWORK:
			{
				//unsigned short* a = getHighlightedPixels();
				//cgpDialog.createCGPUsageDialog(hWnd,mamSets.getOverlay(), cgp, a, 1, 1);
				//HANDLE    hThrd;
				DWORD    Id;
				cgp.initialise();
				//hThrd    =    CreateThread ( NULL , 0 , 
				//	(LPTHREAD_START_ROUTINE)ThrdFunc ,
				//	(LPVOID)0 , 0 , &Id);
				cgp.startCGPTraining(hWnd, true);
				Id = 5;
				//MessageBox(NULL, "The network has completed training", "Complete", NULL);
			}
			break;
			case ID_CGP_EVALUATENETWORK:
			{
				cgp.startCGPTesting(hWnd, true);
			}
			break;
			case ID_CGP_SAVEINPUTS:
			{
				SelectCGPFilename sCGPFilename;
				sCGPFilename.createFilenameDialog(hWnd);
				std::string chosenFilename;
				chosenFilename = sCGPFilename.getText();
				if (chosenFilename.size() > 0) {
					bool hasLoaded;
					hasLoaded = cgp.saveInputs(chosenFilename);
					if (hasLoaded == false) {
						MessageBox(NULL, "IO Exception", NULL, NULL);
					}
				}
			}
			break;
			case ID_CGP_LOADINPUTS:
			{
				openCGPLocation();
			}
			break;
			// if the user has pressed the overlay button then provided there is an
			// overlay make it appear or disappear 
			case IDM_OVERLAY:
				if (smaller != NULL) {
					bool hasOverlay = mamSets.getHasOverlay();
					bool isOverlay = mamSets.getIsOverlay();
					if (hasOverlay == true) {
						if (isOverlay == false) mamSets.setIsOverlay(true);
						else mamSets.setIsOverlay(false);
						switchImage();
						// to update it must first be declared invalid
						InvalidateRect(hWnd, NULL, TRUE); 
						UpdateWindow(hWnd);
					}
				}
			break;
			
			// change the icon if the user wishes to zoom
			case IDM_ZOOMOUT:
				if (smaller != NULL) {
					//changeCurrentCursor(MAKEINTRESOURCE(IDC_CURSOR2));
					MammoviewSettings::IconType iType = MammoviewSettings::zoomOut;
					mamSets.setIconType(iType);
				}
			break;
			case IDM_ZOOMIN:
				if (smaller != NULL) {
					//changeCurrentCursor(MAKEINTRESOURCE(IDC_CURSOR1));
					MammoviewSettings::IconType iType = MammoviewSettings::zoomIn;
					mamSets.setIconType(iType);
				}
			break;
			case IDM_ARROW:
				if (smaller != NULL) {
					//changeCurrentCursor(MAKEINTRESOURCE(IDC_ARROW));
					SendMessage(windowToolbar, TB_SETSTATE, 
						IDM_ARROW, TBSTATE_CHECKED | TBSTATE_ENABLED);
				

					MammoviewSettings::IconType iType = MammoviewSettings::arrow;
					mamSets.setIconType(iType);
				}
			break;
			case IDM_HIGHLIGHT:
				if (smaller != NULL) {
					//changeCurrentCursor(MAKEINTRESOURCE(IDC_CURSOR3));
					SendMessage(windowToolbar, TB_SETSTATE, 
						IDM_HIGHLIGHT, TBSTATE_CHECKED | TBSTATE_ENABLED);
				

					MammoviewSettings::IconType iType = MammoviewSettings::drawing;
					mamSets.setIconType(iType);
				}
			break;
		}
		
    break;

	case WM_LBUTTONDOWN: 
		if (mamSets.getIconType() == MammoviewSettings::zoomIn) {
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = HIWORD(lParam); 
			zoomIn(xPos,yPos);
			std::stringstream printStream(" ");
			printStream << xPos << std::string(" ") << yPos << std::string("\n");
			DebugClass::write(std::string("x and y coordinates: ") + printStream.str());
		}
		if (mamSets.getIconType() == MammoviewSettings::zoomOut) {
			zoomOut();
		}
		if (mamSets.getIconType() == MammoviewSettings::drawing) {
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			mamSets.setMouseStartX(xPos);
			mamSets.setMouseStartY(yPos);
			mamSets.setIsDrawing(true);
		}
	break;

	case WM_LBUTTONUP:
		
		if (mamSets.getIsDrawing() == true) {
			int startX = mamSets.getMouseStartX();
			int startY = mamSets.getMouseStartY();
			int endX = GET_X_LPARAM(lParam); 
			int endY = GET_Y_LPARAM(lParam); 

			int imageWidth = smaller->GetWidth();
			int imageHeight = smaller->GetHeight();
			int imageX = mamSets.getITopLeftX();
			int imageY = mamSets.getITopLeftY();
		
			if ( (endX >= imageX) && (endX < (imageX + imageWidth) ) 
				&& (endY >= imageY) && (endY < (imageY + imageHeight) ) ) {

			
				// strictly we should  place everything to draw in one method called from the paint message
				// however in this case we can get away with painting over from here to make things easier
				// as the user has left clicked and dragging there is no danger of them doing anything else
				PAINTSTRUCT paintStruct;
				HDC hDc = BeginPaint(hWnd, &paintStruct);
			
				drawEllipse(hDc, startX, startY, endX, endY);
				EndPaint(hWnd, &paintStruct);
				mamSets.setMouseEndX(endX);
				mamSets.setMouseEndY(endY);
			}
				
				mamSets.setIsDrawing(false);
		}
		
	break;

	case WM_MOUSEMOVE: 
		if (smaller != NULL) {
		if (mamSets.getIsDrawing() == true) {
			int startX = mamSets.getMouseStartX();
			int startY = mamSets.getMouseStartY();
			int endX = GET_X_LPARAM(lParam); 
			int endY = GET_Y_LPARAM(lParam); 

			int imageWidth = smaller->GetWidth();
			int imageHeight = smaller->GetHeight();
			int imageX = mamSets.getITopLeftX();
			int imageY = mamSets.getITopLeftY();
		
			if ( (endX >= imageX) && (endX < (imageX + imageWidth) ) 
				&& (endY >= imageY) && (endY < (imageY + imageHeight) ) ) {

			
				// strictly we should  place everything to draw in one method called from the paint message
				// however in this case we can get away with painting over from here to make things easier
				// as the user has left clicked and dragging there is no danger of them doing anything else
				PAINTSTRUCT paintStruct;
				HDC hDc = BeginPaint(hWnd, &paintStruct);
			
				drawEllipse(hDc, startX, startY, endX, endY);
				EndPaint(hWnd, &paintStruct);
				mamSets.setMouseEndX(endX);
				mamSets.setMouseEndY(endY);
			}

		}
		else {
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam); 
			int imageWidth = smaller->GetWidth();
			int imageHeight = smaller->GetHeight();
			int imageX = mamSets.getITopLeftX();
			int imageY = mamSets.getITopLeftY();
		
			if ( (xPos >= imageX) && (xPos < (imageX + imageWidth) ) 
				&& (yPos >= imageY) && (yPos < (imageY + imageHeight) ) ) {
				
					if (mamSets.getActualIconType() != mamSets.getIconType()) {
						
						MammoviewSettings::IconType iType;
						if (mamSets.getIconType() == MammoviewSettings::zoomOut) {
							changeCurrentCursor(MAKEINTRESOURCE(IDC_CURSOR2), false);
							iType = MammoviewSettings::zoomOut;
							mamSets.setActualIconType(iType);
						}
						if (mamSets.getIconType() == MammoviewSettings::zoomIn) {
							changeCurrentCursor(MAKEINTRESOURCE(IDC_CURSOR1), false);
							iType = MammoviewSettings::zoomIn;
							mamSets.setActualIconType(iType);
						}
						if (mamSets.getIconType() == MammoviewSettings::drawing) {
							changeCurrentCursor(MAKEINTRESOURCE(IDC_CURSOR3), false);
							iType = MammoviewSettings::drawing;
							mamSets.setActualIconType(iType);
						}
					}
						
			}
			else {
				if(mamSets.getActualIconType() != MammoviewSettings::arrow) {
					changeCurrentCursor(IDC_ARROW, true);
					MammoviewSettings::IconType iType = MammoviewSettings::arrow;
					mamSets.setActualIconType(iType);
				}


			}
		}
		}
	break;
	case WM_ENTERSIZEMOVE:
	   SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_OVERLAPPEDWINDOW
		   |WS_EX_COMPOSITED |WS_EX_LAYERED);
	   //LockWindowUpdate(hWnd);
	//SetWindowRedraw(hWnd, FALSE);
   break;
   case WM_EXITSIZEMOVE:
	  // SetWindowLong(hWnd, GWL_EXSTYLE,WS_EX_LAYERED | WS_EX_OVERLAPPEDWINDOW);
	   SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_OVERLAPPEDWINDOW |WS_EX_LAYERED);
	//   shouldPaint = false;
	   //SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_OVERLAPPEDWINDOW |WS_EX_LAYERED);
	   SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
	   //InvalidateRect(hWnd, NULL, TRUE);
	  // BringWindowToTop(hWnd);
	   //UpdateWindow(hWnd);
	   //LockWindowUpdate(0); 
   break;
	// when the user bringsfocus back make sure eveyrthing gets drawn properly
   // case WM_ACTIVATE:
	//	if(LOWORD(wParam) != WA_INACTIVE) {
			//InvalidateRect(hWnd, NULL, TRUE); 
			//UpdateWindow(hWnd);
	//	}
	//break;
	// when moved redraw
	//case WM_MOVE: 
		//InvalidateRect(hWnd, NULL, TRUE); 
		//UpdateWindow(hWnd);
    //break;
	

//	 if a message is posted to kill the window like hitting the x then
//	 kill the window
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		return 0;
	
	default:
	// if we did nothing with the message then this can process it
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
} // --- MainWndProc ----------------------------------------------------------


