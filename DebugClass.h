#ifndef DEBUGCLASS_H
#define DEBUGCLASS_H
#include <string>
#include <fstream>

class DebugClass {

private:
	static std::ofstream out;//("C:\\Documents and Settings\\David\\My Documents\\outLog.txt");
	// DebugClass() {
		//std::ofstream out_("C:\\Documents and Settings\\David\\My Documents\\outLog.txt");
		//&out = &out_;
	//}

	
public:
	static write(std::string s) {
		out << s;	

	}


};


#endif

