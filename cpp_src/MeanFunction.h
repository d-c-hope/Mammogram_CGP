#ifndef MEANFUNCTION_H
#define MEANFUNCTION_H
#include "CGPFunction.h"
#include <vector>

class MeanFunction : public CGPFunction {
public:
	MeanFunction() { }
	float evaluate(std::vector<float> inputArray);

};

#endif