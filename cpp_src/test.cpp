#include "test.h"

using namespace std;

CGP::CGP() {


}



CGP::CGP(string configFilename) {
	/*XERCES_CPP_NAMESPACE_USE

	XercesDOMParser* parser = new XercesDOMParser();
        //parser->setValidationScheme(XercesDOMParser::Val_Always);    // optional.
        //parser->setDoNamespaces(true);    // optional

        ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
        parser->setErrorHandler(errHandler);

        char* xmlFile = "configFilename";

        try {
            parser->parse(xmlFile);
        }
        catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
//            return -1;
        }
        catch (const DOMException& toCatch) {
            char* message = XMLString::transcode(toCatch.msg);
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            //return -1;
        }
        catch (...) {
            cout << "Unexpected Exception \n" ;
//            return -1;
        }

        delete parser;
        delete errHandler;*/
      //  return 0;


}

CGP::~CGP() {

}


// runs the CGP program the required number of times
void beginCGP() {

}



void CGP::initialise() {



}


void CGP::MutateLPlusA(int lambda, int other) {



}

void CGP::TournamentSelection() {



}


// number of times the program runs
void CGP::setNumOfRuns(int numOfRuns){
	this->numOfRuns = numOfRuns;
}

	// number of generations i.e. times a new population is created on a single run
void CGP::setNumOfGenerations(int numOfGenerations){
	this->numOfGenerations = numOfGenerations;
}

	// size of population, i.e. number of functions
void CGP::setPopulationSize(int populationSize){
	this->populationSize = populationSize;
}

	// if mutation is being used this provides the rate for fixed rate schemes
	// Its a floating point between 0 and 1
void CGP::setMutationRate(int mutationRate) {
	this->mutationRate = mutationRate;
}

	// The number of columns in a CGP scheme
void CGP::setNumOfColumns(int numOfColumns) {
	this->numOfColumns = numOfColumns;
}

	// The number of rows in the scheme assuming this is fixed
	// It could be that in order to force some filter perhaps you
	// might want to half this each time
void CGP::setNumOfRows(int numOfRows) {
	this->numOfRows = numOfRows;
}

	// If using a lambda + something scheme this is the lambda used
void CGP::setLambda(int lambda) {
	this->lambda = lambda;
}



	// number of times the program runs
int CGP::getNumOfRuns() {
	return numOfColumns;
}

	// number of generations i.e. times a new population is created on a single run
int CGP::getNumOfGenerations() {
	return numOfGenerations;
}

	// size of population, i.e. number of functions
int CGP::getPopulationSize() {
	return populationSize;
}

	// if mutation is being used this provides the rate for fixed rate schemes
	// Its a floating point between 0 and 1
int CGP::getMutationRate() {
	return mutationRate;
}

	// The number of columns in a CGP scheme
int CGP::getNumOfColumns() {
	return numOfColumns;
}

	// The number of rows in the scheme assuming this is fixed
	// It could be that in order to force some filter perhaps you
	// might want to half this each time
int CGP::getNumOfRows() {
	return numOfRows;
}

	// If using a lambda + something scheme this is the lambda used
int CGP::getLambda() {
	return lambda;
}