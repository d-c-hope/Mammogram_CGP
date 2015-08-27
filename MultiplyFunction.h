#ifndef MULTIPLYFUNCTION_H
#define MULTIPLYFUNCTION_H
#include "CGPFunction.h"
#include <vector>

class MultiplyFunction : public CGPFunction {
public:
	MultiplyFunction() {}
	float evaluate(std::vector<float> inputArray);

};

#endif