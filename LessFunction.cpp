#include "LessFunction.h"

using namespace std;


float LessFunction::evaluate(vector<float> inputArray) {
	
	float output = 0;
	if (inputArray.size() >= 2 ) {
		if (inputArray[0] < inputArray[1]) {
			output = 1; 
		}
		else {
			output = 0.5;
		}

	}
	
	return output;
}