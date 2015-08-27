#include "OverlayInfo.h"

using namespace std;

OverlayInfo::OverlayInfo() {
		int abnormalityNumber = 0;
		std::string lesionType = "";
		int assessment = 0;
		int subtlety = 0;
		std::string pathology = "";
		int noOutlines = 0;
		//std::vector<int> boundary;

}

// ----------------------------------------------------------------------------
// selfSet
//
// this sets up all the class variables based on an overlay file
// note that some breast have more than 1 overlay so since we are
// going to treat each one individually then this must be provided
// seperately so the correct information in the file can be extracted
// ----------------------------------------------------------------------------
void OverlayInfo::selfSet(std::string Filename, int abnormalityNumber) {
	    std::ifstream in(Filename.c_str());
		std::string s;
		//int info;
		//char space;
		const boost::regex divideBySpace("\\s+");
		
		//lineIter++;
		int noToMoveForward = ((abnormalityNumber - 1) * 8)+ 1;
		for (int i = 0; i < noToMoveForward; i++) {
			getline(in, s);
		}
		for (int i = 0; i < 7; i++) {
			getline(in, s);
			
			boost::sregex_token_iterator lineIter(s.begin(), s.end(), divideBySpace, -1);
			if (s.find("BOUNDARY") == std::string::npos) {
				toPrintVec.push_back(s);
				if (s.find("PATHOLOGY") != std::string::npos) {
					if (s.find("MALIGNANT") != std::string::npos) 
						pathology = string("MALIGNANT");
					if (s.find("BENIGN") != std::string::npos) 
						pathology = string("BENIGN");
					if (s.find("BENIGN_WITHOUT_CALLBACK")!= std::string::npos) 
						pathology = string("BENIGN_WITHOUT_CALLBACK");
				}
			}
			else
			{
				
				getline(in, s);
				//boost::sregex_token_iterator pointsIter(s.begin(), s.end(), divideBySpace, -1);
				//boost::sregex_token_iterator end;
				//std::string x;
				//std::string y;
				std::stringstream sStream(s);
				int x;
				int y;
				sStream >> x;
				sStream >> y;
				char current;
				int endLoop = false;
				while ((sStream >> current) && (endLoop == false)) {				
				if (current == '#') endLoop = true;
					switch (current) {
						case '0': 
							y--;
						break;
					    case '1': 
							x++;
							y--;
						break;
						case '2': 
							x++;
						break;
						case '3': 
							x++;
							y++;
						break;
						case '4': 
							y++;
						break;
						case '5': 
							x--;
							y++;
						break;
						case '6': 
							x--;
						break;
						case '7': 
							x--;
							y--;
						break;
					}
					boundary.push_back(x);
					boundary.push_back(y);
				}
				
			}
			if (s.find("ABNORMALITY") != std::string::npos) {
				lineIter++;
				std::string abnor = *lineIter;
				abnormalityNumber = atoi(abnor.c_str()); 
			}
			if (s.find("ASSESSMENT")!= std::string::npos) {
				lineIter++;
				std::string abnor = *lineIter;
				abnormalityNumber = atoi(abnor.c_str()); 
			}
			if (s.find("SUBTLETY")!= std::string::npos) {
				lineIter++;
				std::string abnor = *lineIter;
				abnormalityNumber = atoi(abnor.c_str()); 
			}

		}
	//	boost::sregex_token_iterator lineIter(s.begin(), s.end(), divideBySpace, -1);
	//	iter++;
	//	abnormalityNumber = atoi((*iter).c_str())
	//	getLine(in, s);
	//	boost::sregex_token_iterator lineIter(s.begin(), s.end(), divideBySpace, -1);
	//	iter++;
	//	abnormalityNumber = atoi((*iter).c_str())
		



} // --- selfSet --------------------------------------------------------------




std::vector<std::string> OverlayInfo::getToPrintVector() {
	return toPrintVec;
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
		assessment = assessmentNumber;

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


	



