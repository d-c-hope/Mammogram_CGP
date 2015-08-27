#ifndef CGPFUNCTION_H
#define CGPFUNCTION_H
#include <vector>


// ----------------------------------------------------------------------------
// class CGPFunction
//
// functions are derived from this all having at least one method evaluate
// but more might be necessary to keep things clean. the aim of encapsulating
// functions in a class is so an array of them can be used for instant access
// rather than doing if to decide what to call. note that the same could be 
// acheived using an array of function pointers but this is clearer and allows
// extensions in the future
// ----------------------------------------------------------------------------
class CGPFunction {
protected:
	// number of inputs into a function
	//const int numberOfInputs;

public:
	CGPFunction();
	virtual float evaluate(std::vector<float> inputArray) = 0;




}; // --- class CGPFunction ---------------------------------------------------



#endif