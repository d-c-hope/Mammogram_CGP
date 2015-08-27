#ifndef CGP_NETWORK
#define CGP_NETWORK
#include "CGPFunction.h"
#include "MultiplyFunction.h"
#include <cstdlib>
#include <ctime>
#include "CGPNode.h"
#include "Math.h"


// ----------------------------------------------------------------------------
// class CGPNetwork
//
// encapsulates a single network of functions
// ----------------------------------------------------------------------------
class CGPNetwork {
private:
	// variables

	// a two dimensional array of pointers to CGPFunction objects
	CGPNode** funcArray;

	// number of rows
	const int numOfRows;

	// number of columns
	const int numOfColumns;

	//number of rows time number of columns
	int funcArraySize;

	// number of functions available to use
	int numOfFunctions;

	// how far back a connection can be made
	const int levelsBack;

	// number of inputs to the network
	const int numOfInputs;
	
	// number of outputs
	const int numOfOutputs;

	// number of inputs to a node in the CGP graph
	const int numOfNodeInputs;

	// total number of genes including connections and
	// functions
	float numOfGenes;

	// on the output do we take the raw number or do we use a threshold
	// to make an output of 0 or 1
	bool isThreshold;

	// if is threshold is true we use this, a number greater than or equal 
	// to the threshold gives a 1 as the output, less than a 0
	float binaryOutputThreshold;

	// functions
	std::vector<CGPFunction*> functions;

	// returns a function number
	int CGPNetwork::getRandomFunction();

	// returns a number for an output node to connect to
	int CGPNetwork::getRandomConnection(int row, int column);

	// the network output
	std::vector<float> outputs;

	// the actual number not the diagnosis, useful for roc
	std::vector<float> realOutputs;

	// the connections from the output nodes
	std::vector<int> outputConnections;

	// the inputs to the network
	std::vector<CGPNode> inputs;


	// the mutation rate, i.e. percentage of genes mutated
	float mutationRate;

public:
	// functions

	// constructor makes the two dimensional array
	CGPNetwork(const int _numOfColumns, const int _numOfRows,
		const std::vector<CGPFunction*> _functions, const int _levelsBack,
				const int _numOfInputs, const int _numOfNodeInputs,
				const int _numberOfOutputs = 1);
	
	// constructor to make a new from from one already there
	//CGPNetwork(CGPNetwork* net);

	// copy constructor to make a new from from one already there
	CGPNetwork(const CGPNetwork& net);

	// overloaded assignment
	CGPNetwork& operator= (const CGPNetwork& net);

	// get the fitness
	int getFitness();

	// causes the network to mutate
	void mutate(float mutationRate);
	
	// destructor, cleans up the function array
	~CGPNetwork();

	// fills the array with functions
	void initialise();

	// evaluates the network
	void evaluate();

	// used to recursively process the tree
	void processTree(CGPNode* node);

	// resets the output in each node to -1, otherwise evaluation is not valid
	void resetNodeOutputs();

	std::vector<float> getOutputs() {
		return outputs;
	}

	std::vector<float> getRealOutputs() {
		return realOutputs;
	}

	void setInputs(std::vector<CGPNode> inputs) {
		this->inputs = inputs;
	}

	void setThreshold(bool isThreshold, float binaryOutputThreshold) {
		this->isThreshold = isThreshold;
		this->binaryOutputThreshold = binaryOutputThreshold;
	}



}; // --- class CGPNetwork ----------------------------------------------------

#endif