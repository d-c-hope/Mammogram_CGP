#ifndef LESSFUNCTION_H
#define LESSFUNCTION_H
#include "CGPFunction.h"
#include <vector>

class LessFunction : public CGPFunction {
public:
	LessFunction() { }
	float evaluate(std::vector<float> inputArray);

};

#endif