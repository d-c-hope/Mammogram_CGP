#ifndef CGP_H
#define CGP_H

#include <string>
#include <sstream>
#include <vector>
#include "boost\regex.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include "CGPNetwork.h"
#include "DebugClass.h"
#include "FunctionList.h"
#include <cstdlib>
#include <ctime>
#include "ResultsWriter.h"
#include "SelectCGPFilename.h"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include "ProgressDialog.h"

// This is the basic CGP class
class CGP {

public:

	// constructor if we want to specify xml file later
	CGP();

	// copnstructor if we know where the xml is and want to do everything
	// straight off, this is perferred
	CGP(std::string configFilename, bool isWindows);

	// destructor
	~CGP();

	// this initialises most class settings using an xml config one
	int loadFromXML(std::string configFilename, bool isWindows);

	// make the CGP networks whcih are what evaluate the data
	void initialise();

	// when CGP is trained we call this specifying if we want it in another
	// thread and if we are using a window
	void startCGPTraining(HWND hWnd, bool isThreaded);

	// after training we want to test the network so call this one
	void startCGPTesting(HWND hWnd, bool isThreaded);

	

	// number of times the program runs
	void setNumOfRuns(int numOfRuns);

	// number of generations i.e. times a new population is created on a single run
	void setNumOfGenerations(int numOfGenerations);

	// size of population, i.e. number of functions
	void setPopulationSize(int populationSize);

	// if mutation is being used this provides the rate for fixed rate schemes
	// Its a floating point between 0 and 1
	void setMutationRate(int mutationRate);

	// The number of columns in a CGP scheme
	void setNumOfColumns(int numOfColumns);

	// sets the number of inputs to a network
	void setNumOfInputs(int numOfInputs);

	//void setNumOfDataSets(int numOfDataSets);

	// sets number of outputs on a network
	void setNumOfOutputs(int numOfOutputs);

	// The number of rows in the scheme assuming this is fixed
	// It could be that in order to force some filter perhaps you
	// might want to half this each time
	void setNumOfRows(int numOfRows);

	// If using a lambda + something scheme this is the lambda used
	void setLambda(int lambda);

	// number of times the program runs
	int getNumOfRuns();

	// number of generations i.e. times a new population is created on a single run
	int getNumOfGenerations();

	// size of population, i.e. number of functions
	int getPopulationSize();

	// if mutation is being used this provides the rate for fixed rate schemes
	// Its a floating point between 0 and 1
	int getMutationRate();

	// The number of columns in a CGP scheme
	int getNumOfColumns();

	// The number of rows in the scheme assuming this is fixed
	// It could be that in order to force some filter perhaps you
	// might want to half this each time
	int getNumOfRows();

	// If using a lambda + something scheme this is the lambda used
	int getLambda();

	float testNetwork();

	

	void addTrainingInputs(std::vector<float> trainInputs); 

	void addTrainingOutputs(std::vector<float> trainOutputs);


	void addTestingInputs(std::vector<float> testInputs); 

	void addTestingOutputs(std::vector<float> testOutputs);

	bool saveInputs(std::string filename);

	bool loadInputs(std::string filename);

	//void beginTestingThread(HWND hWnd);

	//oid CGP::beginTrainingThread

	static DWORD WINAPI statBeginTesting(LPVOID param);

	static DWORD WINAPI statBeginTraining(LPVOID param);

	// used for the progress bar
    HWND hWnd;

	void setHwnd(HWND hWnd) {
		this->hWnd = hWnd;
	}

private:
	// number of times the program runs
	int numOfRuns;

	// number of generations i.e. times a new population is created on a single run
	int numOfGenerations;

	// size of population, i.e. number of functions
	int populationSize;

	// if mutation is being used this provides the rate for fixed rate schemes
	// Its a floating point between 0 and 1
	float mutationRate;

	// The number of columns in a CGP scheme
	int numOfColumns;

	// The number of rows in the scheme assuming this is fixed
	// It could be that in order to force some filter perhaps you
	// might want to half this each time
	int numOfRows;

	// If using a lambda + something scheme this is the lambda used
	int lambda;

	//how far back to connect
	int levelsBack;

	// number of network inputs
	int numOfInputs;

	// the number of outputs from the network
	int numOfOutputs;

	// number of inputs to each CGP node
	int numOfNodeInputs;

	// in order to evaluate the effectiveness of CGP it needs to be tested with various
	// inputs e.g. different mammograms with their features, this would be how many
	// mammograms. for each mammogram a set of inputs is made
	int numOfDataSets;

	int randomNumberSeed;

	bool isThreshold;

	float binaryOutputThreshold;

	// functions
	std::vector<CGPFunction*> functions;

	HANDLE  hThrd;

	ProgressDialog progressDialog;

	std::vector<CGPNetwork> fittestArray;

	// runs the CGP program the required number of times
	bool beginTrainingCGP();

	// performs lambda+1 mutation on the network
	void generateLambdaPlusOne(CGPNetwork* fittest);


	// performs tournament selection on the network
	void CGP::TournamentSelection();

	// the array of CGP networks
	std::vector<CGPNetwork> networks; 

	// the desired outputs needed to evaluate fitness
	// could be a number of outputs for an input set
	std::vector< std::vector<float> > desiredTestOutputs;

	// a vector of desired outputs used to evaluate the actual performance
	// of the network
	std::vector< std::vector<float> > desiredTrainOutputs;

	// the desired inputs, will be a set for each
	// item used in training, e.g. each item in the
	// top level vector is an array of features in 
	// in image
	std::vector< std::vector<CGPNode> > trainInputs;

	// the desired inputs, will be a set for each
	// item used in testing, e.g. each item in the
	// top level vector is an array of features in 
	// in image
	std::vector< std::vector<CGPNode> > testInputs;

protected:
	// calls the method to generate new population
	virtual void generateNewPopulation(CGPNetwork* fittest);

	// gets a fitness based on comparing the two arrays
	float calculateFitness(std::vector<float> desOut, std::vector<float> realOut);
	
};

#endif


