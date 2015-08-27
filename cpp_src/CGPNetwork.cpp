#include "CGPNetwork.h"

using namespace std;


// ----------------------------------------------------------------------------
// CGPNetwork
//
//  initialises the 2d array of pointers to CGP nodes
// ----------------------------------------------------------------------------
CGPNetwork::CGPNetwork(const int _numOfColumns, const int _numOfRows,
					   const vector<CGPFunction*> _functions,
					   const int _levelsBack,
					   const int _numOfInputs, const int _numOfNodeInputs,
					   const int _numOfOutputs
					   ) :
						numOfColumns(_numOfColumns),
						numOfRows(_numOfRows),
						functions(_functions),
						levelsBack(_levelsBack),
						numOfInputs(_numOfInputs),
						numOfOutputs(_numOfOutputs),
						numOfNodeInputs(_numOfNodeInputs)
						{


	numOfFunctions = functions.size();

	// we could be mutating any node and within that node it could be 
	// a connection or the function. Getting a random number up to this
	// size affects what we are to mutate
	numOfGenes = ((numOfColumns * numOfRows) * (numOfNodeInputs 
		+ 1)) + numOfOutputs;

	isThreshold = false;

	binaryOutputThreshold = 0;

	// seed the random number generator
	//srand( (unsigned)time( NULL ) );

	// since we are using a linear array for speed we must calculate its size
	int funcArraySize = numOfRows * numOfColumns;

	// declare the array of pointers
	funcArray = new CGPNode*[funcArraySize];

	funcArray[0] = NULL;
	// now allocate memory for these nodes
	initialise();
	

	//}	
} // --- CGPNetwork -----------------------------------------------------------



// ----------------------------------------------------------------------------
// CGPNetwork
//
//  copy constructs
// ----------------------------------------------------------------------------
CGPNetwork::CGPNetwork(const CGPNetwork& net) :
	numOfColumns(net.numOfColumns),
	numOfRows(net.numOfRows),
	functions(net.functions),
	levelsBack(net.levelsBack),
	numOfInputs(net.numOfInputs),
	numOfOutputs(net.numOfOutputs),
	numOfNodeInputs(net.numOfNodeInputs),
	outputs(net.outputs),
	realOutputs(net.realOutputs),
	outputConnections(net.outputConnections),
	inputs(net.inputs),
	numOfGenes(net.numOfGenes),
	isThreshold(net.isThreshold),
	binaryOutputThreshold(net.binaryOutputThreshold)
	{
		
				
		numOfFunctions = functions.size();
		// we could be mutating any node and within that node it could be 
		// a connection or the function. Getting a random number up to this
		// size affects what we are to mutate
	//	numOfGenes = ((numOfColumns * numOfRows) * (numOfNodeInputs 
	//		+ 1)) + numOfOutputs;
		
		// since we are using a linear array for speed we must calculate its size
		funcArraySize = numOfRows * numOfColumns;

		// declare an array of pointers
		funcArray = new CGPNode*[funcArraySize];

		//only copy something that exists
		if (net.funcArray[0] != NULL) {
			for (int i = 0; i < funcArraySize; i++) {
				//CGPNode node(*funcArray[i]);
				funcArray[i] = new CGPNode();
				//CGPNode* n = (net.funcArray[i]);
				*(funcArray[i]) = *(net.funcArray[i]);

			}
		}
		else funcArray[0] = NULL;

		//outputs = net.outputs;
		//outputConnections = net.outputConnections;
		//inputs = net.inputs;
		//numOfGenes = net.numOfGenes;

}


// ----------------------------------------------------------------------------
// resetOutputs
//
// sets all outputs to -1
// ---------------------------------------------------------------------------
void CGPNetwork::resetNodeOutputs() {
	for (int i = 0; i < funcArraySize; i++) {
	
		funcArray[i]->setOutput(-1);

	}

}


// ----------------------------------------------------------------------------
// operator=
//
//  equality in CGP has meaning purely in saying that its wired up the same
// and this is reflected in this
// ----------------------------------------------------------------------------
	CGPNetwork& CGPNetwork::operator= (const CGPNetwork& net) {

	if ( (funcArray[0] != NULL) && (net.funcArray[0] != NULL)) {
		for (int i = 0; i < funcArraySize; i++) {
			*funcArray[i] = *(net.funcArray[i]);

		}
	}
	outputConnections = net.outputConnections;

		
	return *this;

}



// ----------------------------------------------------------------------------
// ~CGPNetwork
//
//  destroys the 2d array of functions
// ----------------------------------------------------------------------------
CGPNetwork::~CGPNetwork() {
	for (int i = 0; i < funcArraySize; i ++) {
		delete funcArray[i];

	}
	delete funcArray;
} // --- ~CGPNetwork ----------------------------------------------------------


// ----------------------------------------------------------------------------
//
//
// ----------------------------------------------------------------------------
int CGPNetwork::getFitness() {
	
	return 1;
} // --- getFitness -----------------------------------------------------------



// ----------------------------------------------------------------------------
// initialises
//
//  this makes the pointers actually point to nodes
// ----------------------------------------------------------------------------
void CGPNetwork::initialise() {
	
	// used for node inputs
	vector<int>* inputs;
	numOfGenes = ((numOfColumns * numOfRows) * (numOfNodeInputs 
		+ 1)) + numOfOutputs;

	funcArraySize = numOfRows * numOfColumns;
	// loop over all nodes giving them a random function and
	// connections to their inputs
	for (int i = 0; i < numOfRows; i++) {
		for (int j = 0; j < numOfColumns; j++)
		{
			// size of grid up to this point plus stuff in final column
			int index = ((j * numOfRows) + i);
			funcArray[index] = new CGPNode();
			funcArray[index]->setFunction(getRandomFunction()); 
			inputs = new vector<int>();
			for (int k = 0; k < numOfNodeInputs; k++) {
				inputs->push_back(getRandomConnection(i,j));
			}
			funcArray[index]->setInputs(*inputs); 
			delete inputs;
		}

	}
	// now connect the output to a node
	//vector<int>::iterator it;
	//for (it = outputConnections.begin(); it != outputConnections.end(); i++)
	//{
	//	*it = getRandomConnection(0, numOfColumns);
	//}
	for (int i = 0; i < numOfOutputs; i++) {
		int connection = getRandomConnection(0, numOfColumns);
		outputConnections.push_back(connection);
	}

	for (int i = 0; i < numOfOutputs; i++) {
		outputs.push_back(-1);
	}
	for (int i = 0; i < numOfOutputs; i++) {
		realOutputs.push_back(-1);
	}

} // ---  initialise ----------------------------------------------------------



// ----------------------------------------------------------------------------
// evaluates the network for a given input
//
// evaluates 
// ----------------------------------------------------------------------------
void CGPNetwork::evaluate() {
	for (int i = 0; i < numOfOutputs; i++) {
		
		// set this to the current output connection
		int outputCon = outputConnections[i];
		
		
		// if we are connecting straight to an input we are done
		if(outputCon < numOfInputs) {
			//done = true;
			outputs[i] = inputs[i].getOutput();
		}
		// otherwise use process tree to work down any nodes and get an answer
		else {
			int index = outputCon - numOfInputs;
			CGPNode* rootNode = funcArray[index];
			
				processTree(rootNode);
				//CGPNode output = 
			float actualOut = rootNode->getOutput();
			
			if (isThreshold  == true) {
				if (actualOut >= binaryOutputThreshold) {
					realOutputs[i] = actualOut;
					actualOut = 1;
				}
				else {
					realOutputs[i] = actualOut;
					actualOut = 0;
				}
			}
			
			outputs[i] = actualOut;

		}
	}

} // --- evaluate ----------------------------------------------------



// ----------------------------------------------------------------------------
// processTree
//
// the aim here is to take a node and get a value from it, i.e. apply its 
// function to all its sub nodes. A brute force technique could be applied
// to the network evaluating everything from the inputs upwards but that is
// inefficent since many nodes have no effect on the output. Thus we treat
// the network as almost a tree originating from the output and we move down
// each of nodes then back up recursively, i.e. go down to the inputs and 
// then once we have these vales work back up
// ----------------------------------------------------------------------------
void CGPNetwork::processTree(CGPNode* node) {
	// the inputs to a node
	vector<int> inputConnections = node->getInputs();

	// these are plugged into the functions
	vector<float> functionValues;

	vector<int>::iterator iter;
	for (iter = inputConnections.begin();
		iter != inputConnections.end(); iter++) {
		// if the value is one of the inputs then place it into the array of
		// values to process
		if (*iter < numOfInputs) {
			functionValues.push_back(inputs[*iter].getOutput());
		}
		// otherwise its coming from funcArray
		else {

			CGPNode* currentNode = funcArray[*iter - numOfInputs];
			float value;
			if ( (value = currentNode->getOutput() ) != -1) {
				functionValues.push_back(value);
			}
			else {
				//CGPNode processed = 
				processTree(currentNode);
				functionValues.push_back(currentNode->getOutput());
				//functionValues.push_back(processed.getOutput());
			}
		}

	}

	CGPFunction* cgpFunc = functions[node->getFunction()];
	float output = cgpFunc->evaluate(functionValues);
	node->setOutput(output);
	// functions
	//return node;

}



// ----------------------------------------------------------------------------
// getRandomfunction
//
// makes a random function number
// ----------------------------------------------------------------------------
int CGPNetwork::getRandomFunction() {

	int	N = numOfFunctions;
	int x = (int) ( N * (rand() / (RAND_MAX + 1.0)) );
	return x;
} // --- getRandomFunction ----------------------------------------------------



// ----------------------------------------------------------------------------
// getRandomConnection
//
// picks appropiate inputs at random based on the number of levels back
// ----------------------------------------------------------------------------
int CGPNetwork::getRandomConnection(int row, int column) {
	int N;
	int x;
	// depending on whether the levels back reaches the inputs or not
	// the calculation is a bit different
	// first we generate a number between which the random value must
	// lie (0 and N-1), then we convert this to an input number
	if ((column - levelsBack) >= 0) {
		N = levelsBack * numOfRows;
		x = (int) ( N * (rand() / (RAND_MAX + 1.0)) );
		// add on the bit before where we chose our number;
		x = numOfInputs + ( (column - levelsBack) * numOfRows) + x;
	}
	else {
		N = (column * numOfRows) + numOfInputs;
		x = (int) ( N * (rand() / (RAND_MAX + 1.0)) );
		
	}
	

	return x;
} // --- getRandomInputs ------------------------------------------------------



// ----------------------------------------------------------------------------
// mutate
//
// mutates the network
// mutationRate : a number between 0 and 1 to specify percentage of genes 
// mutated
// ----------------------------------------------------------------------------
void CGPNetwork::mutate(float mutationRate) {
	
	// mutation rate determines what percentage of genes get
	// mutated so mutate until this figure is met
	int numOfMutations = (int)(mutationRate * numOfGenes);
	int N = numOfGenes;
	int gene;
	//int testSize = outputConnections.size();
	for (int i = 0; i < numOfMutations; i++) {
		gene = (int) N * rand() / (RAND_MAX + 1.0);
		// having got a gene we must determine what it represents
		// before we can try and mutate it
		// if its a node
		if (gene < (numOfGenes - numOfOutputs)) {
			// if its a function
			if ( ( (gene + 1) % (numOfNodeInputs + 1)) == 0) {
				int function = getRandomFunction();
				// now convert to a node in our array
				int nodeIndex = floor( (float) (gene / (numOfNodeInputs + 1) ) );
				funcArray[nodeIndex]->setFunction(function);
			}
			// else its a connection
			else {
				
				int inputNum = floor((float)(gene % (numOfNodeInputs + 1)));
				int nodeIndex = floor( (float) (gene / (numOfNodeInputs + 1) ) );
				// we don't care about the row
				//int column = (gene - 1) / (numOfNodeInputs + 1);
				int column = floor(static_cast<float>(nodeIndex / numOfRows));
				int connection = getRandomConnection(0, column);
				
				funcArray[nodeIndex]->setInput(inputNum, connection);
			}
		}
		// else its an output
		else {
			int outputIndex = numOfGenes - gene -1;
			outputConnections[outputIndex] = getRandomConnection(0, numOfColumns); 
			
		}
	}	
	


	
} // --- mutate ---------------------------------------------------------------