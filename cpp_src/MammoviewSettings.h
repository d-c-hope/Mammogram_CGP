#ifndef MAMMOVIEWSETTINGS_H
#define MAMMOVIEWSETTINGS_H
#include <string>
#include <fstream>
#include <vector>



// ----------------------------------------------------------------------------
// class MamoviewSettings
//
// there are a number of setting in mammoview that affects lot of methods
// for instance if the user selects to have an overlay then eveytime things
// are drawn this has to be known. such global variables are kept in here
// ----------------------------------------------------------------------------
class MammoviewSettings {

// note no  destructors specified, this is a simple set/ get class

public: enum IconType {
		zoomIn,
		zoomOut,
		arrow,
		drawing
};

private:
	
	// the file name for the file which is used for the ics file
	std::string infoFileName;

	// a vector of all information on the file which is displayed
	std::vector<std::string*> fileInfoVector;

	// one of leftmlo leftcc rightmlo rightcc
	std::string fileType;

	// has the user clicked the option to see the overlay
	bool isOverlay;

	// has mammogram actually got an overlay
	bool hasOverlay;

	// temp should later be removed from global
	std::string overlayFileName;

	// an object which contains all overlay info
	OverlayInfo* overlay;

	// the level of zoom on the picture
	int zoomLevel;

	// the icon type
	IconType iconType;

	//InnerIconType
	IconType innerIconType;

	//InnerIconType
	IconType actualIconType;

	// top left of the mammogram
	int iTopLeftX;

	// top left y of the mammogram
	int iTopLeftY;

	// when the user tries to make a circle for example this will
	// store where they start on the x axis
	int mouseStartX;

	// when the user tries to make a circle for example this will
	// store where they start on the x axis
	int mouseStartY;

	// when the user tries to make a circle for example this will
	// store where they start on the x axis
	int mouseEndX;

	// when the user tries to make a circle for example this will
	// store where they start on the x axis
	int mouseEndY;

	// when the user chooses to left click with the drawing icon
	// so long as the mouse is held down this is true
	bool isDrawing;

	IShellFolder* databaseFolder;

	// used to move through all the folders in a folder
	LPENUMIDLIST foldersEnum;


	IShellFolder* caseFolder;

	// used to move through all the images in a folder
	LPENUMIDLIST caseEnum;


	// when moving through all sub files/folders in a directory
	// we use foldersEnum to get the names. we must add the full 
	// path to these names though
	std::string pathToDatabaseFolder;

	// so you can go forward and back through images we remember the
	// paths to all ones previously looked at
	std::vector<std::string> imagePathVector;

	int currentImageIndex;


	// this is effectively whether or not it is cancer
	float diagnosis; 


public:

	MammoviewSettings() {
		
		// the name of the file with mammogram information in it
		infoFileName = "";

		// the file type, one of LEFTCC,RIGHT_CC, LEFT_MLO, RIGHT_MLO
		fileType = "";
	
		// if the user has selected to view the overlay
		isOverlay = false;
	
		// if the mammogram has an overlay(when using CGP functions it should)
		hasOverlay = false;
	
		//name of the file containing the current mamograms overlay
		overlayFileName = "";

		// initially we can see the whole mamogram
		zoomLevel = 0;

		// initially we use an arrow icon
		iconType = arrow;

		actualIconType = arrow;

		// initially the user is not drawing
		isDrawing = false;

		// nothing there initially so index nothing
		currentImageIndex = -1;

	}


	// the file name for the file which is used for the ics file
	void setInfoFileName(std::string infoFileName) {
		this->infoFileName = infoFileName;
	}

	// a vector of all information on the file which is displayed
	void setFileInfoVector(std::vector<std::string*> fileInfoVector) {
		this->fileInfoVector = fileInfoVector;
	}

	// one of leftmlo leftcc rightmlo rightcc
	void setFileType(std::string fileType) {
		this->fileType = fileType;
	}

	// has the user clicked the option to see the overlay
	void setIsOverlay(bool isOverlay) {
		this->isOverlay = isOverlay;
	}

	// has mammogram actually got an overlay
	void setHasOverlay(bool hasOverlay) {
		this->hasOverlay = hasOverlay;
	}

	// temp should later be removed from global
	void setOverlayFileName(std::string overlayFileName) {
		this->overlayFileName = overlayFileName;
	}

	// an object which contains all overlay info
	void setOverlay(OverlayInfo* overlay) {
		this->overlay = overlay;
	}

	// set the icon type currently selected
	void setIconType(IconType iconType) {
		this->iconType = iconType;
	}

	// set the icon type currently selected
	void setInnerIconType(IconType InnerIconType) {
		this->innerIconType = innerIconType;
	}

	// set the icon type currently selected
	void setActualIconType(IconType actualIconType) {
		this->actualIconType = actualIconType;
	}

	// set the top left mammogram coordinate
	void setITopLeftX(int iTopLeftX) {
		this->iTopLeftX = iTopLeftX;
	}

	// set the top left mammogram coordinate
	void setITopLeftY(int iTopLeftY) {
		this->iTopLeftY = iTopLeftY;
	}

	// set where the mouse starts when its dragged
	void setMouseStartX(int mouseStartX) {
		this->mouseStartX = mouseStartX;
	}

	// set where the mouse starts when its dragged
	void setMouseStartY(int mouseStartY) {
		this->mouseStartY = mouseStartY;
	}

	// set where the mouse ends when its dragged
	void setMouseEndX(int mouseEndX) {
		this->mouseEndX = mouseEndX;
	}

	// set where the mouse ends when its dragged
	void setMouseEndY(int mouseEndY) {
		this->mouseEndY = mouseEndY;
	}

	// set when the user clicks and holds to draw a shape
	void setIsDrawing(bool isDrawing) {
		this->isDrawing = isDrawing;
	}	


	
	// sets the enum object used to move through folders
	void setFolderEnum(LPENUMIDLIST foldersEnum) {
		this->foldersEnum = foldersEnum;
	}

	// sets the enum object used to move through images in a case
	void setCaseEnum(LPENUMIDLIST caseEnum) {
		this->caseEnum = caseEnum;
	}


	
	void setDatabaseFolderString(std::string pathToDatabaseFolder) {
		this->pathToDatabaseFolder = pathToDatabaseFolder;

	}

	void setDatabaseFolder(IShellFolder* databaseFolder) {
		this->databaseFolder = databaseFolder;
	}

	void setCaseFolder(IShellFolder* caseFolder) {
		this->caseFolder = caseFolder;
	}

	void setImagePathVector(std::vector<std::string> imagePathVector) {
		this->imagePathVector = imagePathVector;
	}

	void setCurrentImageIndex(int currentImageIndex) {
		this->currentImageIndex = currentImageIndex;
	}

    
	// the file name for the file which is used for the ics file
	std::string getInfoFileName() {
		return infoFileName;
	}

	// a vector of all information on the file which is displayed
	std::vector<std::string*> getFileInfoVector() {
		return fileInfoVector;
	}

	// one of leftmlo leftcc rightmlo rightcc
	std::string getFileType() {
		return fileType;
	}

	// has the user clicked the option to see the overlay
	bool getIsOverlay() {
		return isOverlay;
	}

	// has mammogram actually got an overlay
	bool getHasOverlay() {
		return hasOverlay;
	}

	// temp should later be removed from global
	std::string getOverlayFileName() {
		return overlayFileName;
	}

	// an object which contains all overlay info
	OverlayInfo* getOverlay() {
		return overlay;
	}

	// gets the icon type currently selected
	IconType getIconType() {
		return iconType;
	}

	// gets the icon type currently selected
	IconType getInnerIconType() {
		return innerIconType;
	}

	// gets the icon type currently selected
	IconType getActualIconType() {
		return actualIconType;
	}

	// get the top left mammogram coordinate
	int getITopLeftX() {
		return iTopLeftX;
	}

	// get the top left mammogram coordinate
	int getITopLeftY() {
		return iTopLeftY;
	}

	// gets where the mouse starts when its dragged
	int getMouseStartX() {
		return mouseStartX;
	}

	// gets where the mouse starts when its dragged
	int getMouseStartY() {
		return mouseStartY;
	}

	// gets where the mouse finishes when its dragged
	int getMouseEndX() {
		return mouseEndX;
	}

	// gets where the mouse finishes when its dragged
	int getMouseEndY() {
		return mouseEndY;
	}

	// gets if the user is currently drawing
	bool getIsDrawing() {
		return isDrawing;
	}


	// gets the enum object used to move through folders
	LPENUMIDLIST getFolderEnum() {
		return foldersEnum;
	}

	// gets the enum object used to move through folders
	LPENUMIDLIST getCaseEnum() {
		return caseEnum;
	}

	// get path to database folder
	std::string getDatabaseFolderString() {
		return pathToDatabaseFolder;
	}

	IShellFolder* getDatabaseFolder() {
		return databaseFolder;
	}

	IShellFolder* getCaseFolder() {
		return caseFolder;
	}

	std::vector<std::string> getImagePathVector() {
		return imagePathVector;
	}

	// gets the enum object used to move through folders
	int getCurrentImageIndex() {
		return currentImageIndex;
	}


} ; // --- class mammoviewSettings --------------------------------------------


#endif