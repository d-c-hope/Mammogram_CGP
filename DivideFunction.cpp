#include "DivideFunction.h"

using namespace std;


float DivideFunction::evaluate(vector<float> inputArray) {
	vector<float>::iterator it;
	float output = 0;
	for (it=inputArray.begin(); it != inputArray.end(); it++) {
		if (it == inputArray.begin()) {
			output = *it;
		}
		else {
			if (*it != 0)
			{
				output = output / *it;
			}
		}
		
	}
	return output;
}