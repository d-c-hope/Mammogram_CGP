#include "MultiplyFunction.h"

using namespace std;


float MultiplyFunction::evaluate(vector<float> inputArray) {
	vector<float>::iterator it;
	float output = 1;
	for (it=inputArray.begin(); it != inputArray.end(); it++) {
		output *= *it;
	}
	return output;
}
