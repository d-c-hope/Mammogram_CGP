#ifndef RESULTSWRITER_H
#define RESULTSWRITER_H

#include <string>
#include <vector>
#include <fstream>

class ResultsWriter {
public:
	ResultsWriter(std::string filename);
	void addToMainText(std::string toWrite);
	void writeToFile();


private:
	std::vector<std::string> strVec;
	std::string filename;

};

#endif