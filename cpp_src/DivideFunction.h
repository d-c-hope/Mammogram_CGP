#ifndef DIVIDEFUNCTION_H
#define DIVIDEFUNCTION_H
#include "CGPFunction.h"
#include <vector>

class DivideFunction : public CGPFunction {
public:
	DivideFunction() { }
	float evaluate(std::vector<float> inputArray);

};

#endif