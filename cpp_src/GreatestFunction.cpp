#include "GreatestFunction.h"

using namespace std;


float GreatestFunction::evaluate(vector<float> inputArray) {
	
	//float output = 0;
	vector<float>::iterator it;
	float output = inputArray[0];
	for (it=inputArray.begin(); it != inputArray.end(); it++) {
		if (*it > output) output = *it;
	}
	
	return output;
}