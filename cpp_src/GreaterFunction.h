#ifndef GREATERFUNCTION_H
#define GREATERFUNCTION_H
#include "CGPFunction.h"
#include <vector>

class GreaterFunction : public CGPFunction {
public:
	GreaterFunction() { }
	float evaluate(std::vector<float> inputArray);

};

#endif