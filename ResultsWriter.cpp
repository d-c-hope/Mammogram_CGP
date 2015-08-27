#include "ResultsWriter.h"

using namespace std;

ResultsWriter::ResultsWriter(string filename) {
	this->filename = filename;
}




void ResultsWriter::addToMainText(std::string toWrite) {
	strVec.push_back(toWrite);


}

void ResultsWriter::writeToFile() {
	std::vector<string>::iterator it;
	ofstream out(filename.c_str());
	for (it = strVec.begin(); it < strVec.end(); it++) {
		
		out << *it;
		
	}
}