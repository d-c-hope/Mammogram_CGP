#ifndef GREATESTFUNCTION_H
#define GREATESTFUNCTION_H
#include "CGPFunction.h"
#include <vector>

class GreatestFunction : public CGPFunction {
public:
	GreatestFunction() { }
	float evaluate(std::vector<float> inputArray);

};

#endif