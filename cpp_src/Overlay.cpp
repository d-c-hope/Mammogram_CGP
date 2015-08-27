#include OverlayInfo.h;


	OverlayInfo::OverlayInfo() {
		int abnormalityNumber = 0
		std::string lesionType = "";
		int assessment = 0;
		int subtlety;
		std::string pathology;
		int noOutlines;
		std::vector<int> boundary;

	}



	int OverlayInfo::getAbnormalityNumer() {
		return abnormalityNumber;
	}



	std::string OverlayInfo::getLesionType() {
		return lesionType;

	}



	int OverlayInfo::getAssessment() {
		return assessment;

	}



	int OverlayInfo::getSubtlety() {
		return subtlety;

	}
	std::string OverlayInfo::getpathology() {

		return pathology;
	}


	int OverlayInfo::getnoOutlines() {
		return noOutlines;

	}
	std::vector<int> OverlayInfo::getBoundary() {
		return boundary;

	}




	void OverlayInfo::setAbnormalityNumer(int number) {
		abnormalityNumber = number;

	}



	void OverlayInfo::setLesionType(std::string type) {
		lesionType = type;

	}



	void OverlayInfo::setAssessment(int assessmentNumber) {
		assessment = assessmentNumer;

	}



	void OverlayInfo::setSubtlety(int subtletyNumber) {
		subtlety = subtletyNumber;

	}



	void OverlayInfo::setpathology(std::string pathologyStr){
		pathology = pathologyStr;

	}



	void OverlayInfo::setnoOutlines(int outlinesNumber) {
		noOutlines = outlinesNumber;

	}



	void OverlayInfo::setBoundary(std::vector<int> boundaryVector) {
		boundary = boundaryVector;

	}

	



