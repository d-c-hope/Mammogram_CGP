#ifndef TEST_H
#define TEST_H
#include <string>
#include <vector>
#include "boost\regex.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include "CGPNetwork.h"
#include "DebugClass.h"

//#include <xercesc/parsers/XercesDOMParser.hpp>
//#include <xercesc/dom/DOM.hpp>
//#include <xercesc/sax/HandlerBase.hpp>
//#include <xercesc/util/XMLString.hpp>
//#include <xercesc/util/PlatformUtils.hpp>


// This is the basic CGP class
class CGP {
	int i;
public:

	CGP();
	CGP(std::string configFilename);

	~CGP();

	// make the CGP networks
	void initialise();

	// runs the CGP program the required number of times
	void beginCGP();

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

private:
	// number of times the program runs
	int numOfRuns;

	// number of generations i.e. times a new population is created on a single run
	int numOfGenerations;

	// size of population, i.e. number of functions
	int populationSize;

	// if mutation is being used this provides the rate for fixed rate schemes
	// Its a floating point between 0 and 1
	int mutationRate;

	// The number of columns in a CGP scheme
	int numOfColumns;

	// The number of rows in the scheme assuming this is fixed
	// It could be that in order to force some filter perhaps you
	// might want to half this each time
	int numOfRows;

	// If using a lambda + something scheme this is the lambda used
	int lambda;

	// performs lambda+1 mutation on the network
	void CGP::MutateLPlusA(int lambda, int other);

	// performs tournament selection on the network
	void CGP::TournamentSelection();

	// the array of CGP networks
	std::vector<CGPNetwork> networks; 

};

#endif
