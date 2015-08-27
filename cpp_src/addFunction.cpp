#include "addFunction.h"

using namespace std;


float AddFunction::evaluate(vector<float> inputArray) {
	vector<float>::iterator it;
	float output = 0;
	for (it=inputArray.begin(); it != inputArray.end(); it++) {
		output += *it;
	}
	return output;
}