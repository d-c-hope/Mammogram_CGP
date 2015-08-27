#ifndef LEASTFUNCTION_H
#define LEASTFUNCTION_H
#include "CGPFunction.h"
#include <vector>

class LeastFunction : public CGPFunction {
public:
	LeastFunction() { }
	float evaluate(std::vector<float> inputArray);

};

#endif