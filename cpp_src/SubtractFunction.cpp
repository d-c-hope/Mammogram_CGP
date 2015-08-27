#include "subtractFunction.h"

using namespace std;


float SubtractFunction::evaluate(vector<float> inputArray) {
	vector<float>::iterator it;
	float output = 0;
	for (it=inputArray.begin(); it != inputArray.end(); it++) {
		output -= *it;
	}
	return abs(output);
}