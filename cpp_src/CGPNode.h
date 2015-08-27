#ifndef CGPNODE_H
#define CGPNODE_H
#include <vector>


// ----------------------------------------------------------------------------
// class CGPFunction
//
// features input connections to a function block and the function itself
// ----------------------------------------------------------------------------
class CGPNode {

protected:
	// this is used to check whether a node has its value already
	bool isValid;

	// something that can be used for placing in the network according to shape
	int bindingNumber;

	// how many levels back a connection can be made
	int levelsBack;


	// an int representing the function
	int function;

	// an array of inputs
	std::vector<int> inputs;

	

public:

	// the output of this node
	float output;

	// standard constructor
	CGPNode();
	// copy constructor
	CGPNode(const CGPNode& node);

	// returns a binding number
	int getBindingNumber() {
		return bindingNumber;
	}

	// just returns the output if its already calculated
	// or -1 otherwise
	float getOutput() {
		return output;
	}

	// sets the output to the given value (done once
	// function is evaluated)
	void setOutput(float output) {
		this->output = output;
	}

	// sets the nodes function
	void setFunction(int function) {
		this->function = function;
	}

	// returns an int representing the node function
	int getFunction() {
		return function;
	}
	
	// this can be used to set all inputs at once
	void setInputs(std::vector<int> inputs) {
		this->inputs = inputs;
	}

	// returns a list of input connections
	std::vector<int> getInputs() {
		return inputs;
	}

	// sets the selected node input to the value
	void setInput(int index, int value) {
		inputs[index] = value;
	}

	// declares the output invalid (this is otherwise done using
	// output as -1 unless negative outputs are to be used
	void makeInvalid() {
		isValid = false;
	}

	bool getIsValid() {
		return isValid;
	}

	

	CGPNode& operator= (const CGPNode& node); //{
		//inputs = node.inputs;
//		function = node.function;
//		isValid = node.isValid;
//		output = node.output;
	//	return *this;

	//}
	



}; // --- class CGPFunction ---------------------------------------------------



#endif