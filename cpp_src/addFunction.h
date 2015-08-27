#ifndef ADDFUNCTION_H
#define ADDFUNCTION_H
#include "CGPFunction.h"
#include <vector>

class AddFunction : public CGPFunction {
public:
	AddFunction() { }
	float evaluate(std::vector<float> inputArray);

};

#endif
