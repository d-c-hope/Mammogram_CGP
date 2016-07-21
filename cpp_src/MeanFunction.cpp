#include "MeanFunction.h"

using namespace std;


float MeanFunction::evaluate(vector<float> inputArray) {
	vector<float>::iterator it;
	float divider = inputArray.size();
	float output = 0;
	for (it=inputArray.begin(); it != inputArray.end(); it++) {
		output += *it;
	}
	output = output / divider;
	return output;
}