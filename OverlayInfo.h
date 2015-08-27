#ifndef OVERLAYINFO_H
#define OVERLAYINFO_H

#include <string>
#include <vector>
#include "boost\regex.hpp"
#include <fstream>
#include <iostream>
#include <sstream>


// ----------------------------------------------------------------------------
// class OverlayInfo
//
//
// ----------------------------------------------------------------------------
class OverlayInfo {
public:
	OverlayInfo();

	void OverlayInfo::selfSet(std::string Filename, int abnormalityNumber);
	int getAbnormalityNumer();
	std::string getLesionType();
	int getAssessment();
	int getSubtlety();
	std::string getpathology();
	int getnoOutlines();
	std::vector<std::string> getToPrintVector();
	std::vector<int> getBoundary();
	

	void setAbnormalityNumer(int number);
	void setLesionType(std::string type);
	void setAssessment(int assessmentNumber);
	void setSubtlety(int subtletyNumber);
	void setpathology(std::string pathologyStr);
	void setnoOutlines(int outlinesNumber);
	void setBoundary(std::vector<int> boundaryVector);

private:
	int abnormalityNumber;
	std::string lesionType;
	int assessment;
	int subtlety;
	std::string pathology;
	int noOutlines;
	std::vector<int> boundary;
	std::vector<std::string> toPrintVec;
}; // --- class OverlayInfo ---------------------------------------------------

#endif
