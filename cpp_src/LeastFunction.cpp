#include "LeastFunction.h"

using namespace std;


float LeastFunction::evaluate(vector<float> inputArray) {
	
	vector<float>::iterator it;
	float output = inputArray[0];
	for (it=inputArray.begin(); it != inputArray.end(); it++) {
		if (*it > output) output = *it;
	}
	
	return output;
}