#ifndef SUBTRACTFUNCTION_H
#define SUBTRACTFUNCTION_H
#include "CGPFunction.h"
#include <vector>

class SubtractFunction : public CGPFunction {
public:
	SubtractFunction() { }
	float evaluate(std::vector<float> inputArray);

};

#endif