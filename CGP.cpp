#include "CGP.h"


using namespace std;

// ----------------------------------------------------------------------------
// CGP
//
// if constructing using set and get methods from elsewhere
// ----------------------------------------------------------------------------
CGP::CGP() {


} // --- CGP ------------------------------------------------------------------





// ----------------------------------------------------------------------------
// CGP
//
// if we are to construct the class from a file use this constructor
// ----------------------------------------------------------------------------
CGP::CGP(string configFilename, bool isWindows) {
	loadFromXML(configFilename, isWindows);
		

} // --- CGP ------------------------------------------------------------------


// ----------------------------------------------------------------------------
// loadFromXML
//
//
// ----------------------------------------------------------------------------
int CGP::loadFromXML(string configFilename, bool isWindows) {
	XERCES_CPP_NAMESPACE_USE
		
		XercesDOMParser* parser = new XercesDOMParser();
        parser->setValidationScheme(XercesDOMParser::Val_Always);    // optional.
        parser->setDoNamespaces(true);    // optional

        ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
        parser->setErrorHandler(errHandler);


        try {
            parser->parse(configFilename.c_str());
        
			xercesc_2_7::DOMDocument* dDoc = parser->getDocument();
			DOMElement* dEl = dDoc->getDocumentElement();
			int length;
		
			DOMNodeList* children = dEl->getChildNodes() ;

			const XMLSize_t nodeCount = children->getLength() ;
        
			for( XMLSize_t ix = 0 ; ix < nodeCount ; ++ix ){
				//DebugClass::write(string("Loop ") + "\n");

				DOMNode* currentNode = children->item( ix ) ;

			
				if( DOMNode::ELEMENT_NODE != currentNode->getNodeType() ){
					// not an element node so ignore
			
					continue ;
				}
			
			
				// we should be fine to dynamic cast but for some reason this raises an exception
				// so we'll call this and must ensure there is the check above
				DOMElement* currentElement = static_cast<DOMElement*>(currentNode) ;

				if (XMLString::equals(XMLString::transcode("NumberOfColumns"),
					currentElement->getTagName() ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("NumberOfColumns: "+ string(XMLString::transcode(ch))+"\n");
					numOfColumns = atoi(XMLString::transcode(ch));
				}

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("NumberOfRows") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("NumberOfRows: "+ string(XMLString::transcode(ch))+"\n");
					numOfRows = atoi(XMLString::transcode(ch));
				}

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("LevelsBack") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("LevelsBack: "+ string(XMLString::transcode(ch))+"\n");
					levelsBack = atoi(XMLString::transcode(ch));
				}

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("NumberOfInputs") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("NumberOfInputs: "+ string(XMLString::transcode(ch))+"\n");
					numOfInputs = atoi(XMLString::transcode(ch));
				}

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("NumberOfOutputs") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("NumberOfOutputs: "+ string(XMLString::transcode(ch))+"\n");
					numOfOutputs = atoi(XMLString::transcode(ch));
				}
			
				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("NumberOfNodeInputs") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("NumberOfNodeInputs: "+ string(XMLString::transcode(ch))+"\n");
					numOfNodeInputs = atoi(XMLString::transcode(ch));
				}

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("NodeFunctions") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					//DebugClass::write("NumberOfNodeInputs: "+ string(XMLString::transcode(ch))+"\n");
					DOMNodeList * dNodeList = 
						currentElement->getElementsByTagName(XMLString::transcode("Function"));
					length = dNodeList->getLength();
				
					int function;
					for (int i = 0; i < length; i++) {
						DOMNode* n = dNodeList->item(i);
						const XMLCh* ch;
						ch = n->getTextContent();
						//DebugClass::write("Function: "+ string(XMLString::transcode(ch))+"\n");
						function = atoi(XMLString::transcode(ch));
						switch (function) {
							case 0:
								DebugClass::write("Function: "+ 
									string(XMLString::transcode(ch))+"\n");
								functions.push_back(new AddFunction());
							break;
							case 1:
								DebugClass::write("Function: "+ 
									string(XMLString::transcode(ch))+"\n");
								functions.push_back(new SubtractFunction());
							break;
							case 2:
								DebugClass::write("Function: "+ 
									string(XMLString::transcode(ch))+"\n");
								functions.push_back(new MultiplyFunction());
							break;
							case 3:
								DebugClass::write("Function: "+ 
									string(XMLString::transcode(ch))+"\n");
								functions.push_back(new LeastFunction());
							break;
							case 4:
								DebugClass::write("Function: "+ 
									string(XMLString::transcode(ch))+"\n");
								functions.push_back(new LessFunction());
							break;
							case 5:
								DebugClass::write("Function: "+ 
									string(XMLString::transcode(ch))+"\n");
								functions.push_back(new GreaterFunction());
							break;
							case 6:
								DebugClass::write("Function: "+ 
									string(XMLString::transcode(ch))+"\n");
								functions.push_back(new GreatestFunction());
							break;
							case 7:
								DebugClass::write("Function: "+ 
									string(XMLString::transcode(ch))+"\n");
								functions.push_back(new MeanFunction());
							break;
							case 8: 
								DebugClass::write("Function: "+ 
									string(XMLString::transcode(ch))+"\n");
								functions.push_back(new DivideFunction());
							break;

						} // switch
					} //for
				} //if

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("MutationRate") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("MutationRate: "+ 
						string(XMLString::transcode(ch))+"\n");
					mutationRate = atof(XMLString::transcode(ch));

				} //if

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("PopulationSize") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("PopulationSize: "+ 
						string(XMLString::transcode(ch))+"\n");
					populationSize = atoi(XMLString::transcode(ch));
				}

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("NumOfGenerations") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("NumOfGenerations: "+ 
						string(XMLString::transcode(ch))+"\n");
					numOfGenerations = atoi(XMLString::transcode(ch));
				}

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("NumOfRuns") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("NumOfGenerations: "+ 
						string(XMLString::transcode(ch))+"\n");
					numOfRuns = atoi(XMLString::transcode(ch));
				}

				if (XMLString::equals(currentElement->getTagName(),
					XMLString::transcode("RandomNumberSeed") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("RandomNumberSeed: "+ 
						string(XMLString::transcode(ch))+"\n");
					randomNumberSeed = atoi(XMLString::transcode(ch));
				}

				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("BinaryOutputThreshold") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("BinaryOutputThreshold: "+ 
						string(XMLString::transcode(ch))+"\n");
					binaryOutputThreshold = atof(XMLString::transcode(ch));
				}
				if (XMLString::equals(currentElement->getTagName(), 
					XMLString::transcode("isThreshold") ) )
				{
					const XMLCh* ch = currentElement->getTextContent();
					DebugClass::write("isThreshold: "+ string(XMLString::transcode(ch))+"\n");
					int thresh = atoi(XMLString::transcode(ch));
					if (thresh == 0) isThreshold = false;
					else isThreshold = true;
				}

			} //for
		
	
		} // try
		
        catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
			const char Caption[] = "XML error";
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
			DebugClass::write(string("Exception A") + "\n");
			if (isWindows == true)
			MessageBox(NULL, message, Caption, NULL);
            return -1;
        } //catch
        catch (const DOMException& toCatch) {
            char* message = XMLString::transcode(toCatch.msg);
			const char Caption[] = "XML error";
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
			DebugClass::write(string("Exception B") + "\n");
			if (isWindows == true)
			MessageBox(NULL, message, Caption, NULL);
            return -1;
        } //catch
        catch (...) {
            cout << "Unexpected Exception \n" ;
			const char Caption[] = "XML error";
			DebugClass::write(string("Exception C") + "\n");
			if (isWindows == true)
			MessageBox(NULL, "unexpected exception", Caption, NULL);
            return -1;
        } //catch
		
        delete parser;
        delete errHandler;

		// seed the random number generator
		if (randomNumberSeed == 0)
			srand( (unsigned)time( NULL ) );
		else 
			srand(randomNumberSeed);

		return 1;

} // --- loadFromXML ----------------------------------------------------------



// ----------------------------------------------------------------------------
// ~CGP
//
// ----------------------------------------------------------------------------
CGP::~CGP() {
//	CloseHandle ( hThrd );
	//CGPNetwork net;
	//for (int i = 0; i < populationSize; i++) {
		//net = new CGPNetwork(numOfColumns, numOfRows, functions,
		//	                 levelsBack, numOfInputs, numOfNodeInputs, 
		//					 numOfOutputs);
	//	net = networks.pop_back();
	//	delete net;
	//}
} // --- ~CGP -----------------------------------------------------------------


// must be static for win32 threads
DWORD WINAPI CGP::statBeginTraining(LPVOID param) {
	CGP* cgp = static_cast<CGP*>(param);
	cgp->beginTrainingCGP();
	return 0;
}


void CGP::startCGPTraining(HWND hWnd, bool isThreaded) {
	this->hWnd = hWnd;
	if (hWnd != NULL) {
		progressDialog.createProgressDialog(hWnd);
		progressDialog.disableOK();
		//HWND buttonWnd = GetDlgItem(this->hWnd, IDOK);
		//EnableWindow(buttonWnd, FALSE);
		//SendMessage(hWnd, WM_ENABLE, FALSE,0L);
		//EnableWindow(hWnd,FALSE);
	}
	if (isThreaded == true) {
		HANDLE  hThrd;
		DWORD   Id;
		hThrd    =    CreateThread ( NULL , 0 , 
					(LPTHREAD_START_ROUTINE)statBeginTraining ,
					(LPVOID)this , 0 , NULL);

	}
	else {
		beginTrainingCGP();
	}
}




// must be static for win32 threads
DWORD WINAPI CGP::statBeginTesting(LPVOID param) {
	CGP* cgp = static_cast<CGP*>(param);
	cgp->testNetwork();
	return 0;
}


void CGP::startCGPTesting(HWND hWnd, bool isThreaded) {
	this->hWnd = hWnd;
	if (hWnd != NULL) {
		progressDialog.createProgressDialog(hWnd);
		progressDialog.disableOK();
		//SendMessage(hWnd, WM_ENABLE, FALSE,0L);
		//EnableWindow(hWnd,FALSE);
	}
	if (isThreaded == true) {
		HANDLE  hThrd;
		DWORD   Id;
		hThrd    =    CreateThread ( NULL , 0 , 
					(LPTHREAD_START_ROUTINE)statBeginTesting ,
					(LPVOID)this , 0 , NULL);

	}
	else {
		testNetwork();
	}
}


// ----------------------------------------------------------------------------
// beginCGP
//
// runs the CGP program the required number of times
// ----------------------------------------------------------------------------
bool CGP::beginTrainingCGP() {
	// We are going to write results to a file, we could add a window for
	// this but so the CGP can be used on multiple platforms a text file is ideal
	ResultsWriter resWrit(string("C:\\TrainingResults.txt"));
	
	// if during construction a valid window is passed in we can update
	// a progress bar and first we make it appear
	if (hWnd != NULL) {
//		progressDialog.createProgressDialog(hWnd);
		//SendMessage(hWnd, WM_ENABLE, FALSE,0L);
		EnableWindow(hWnd,FALSE);
	}
	
	// a pointer to our fittest network
	CGPNetwork* fittest;

	// we have lots of input sets and this will be the current one
	std::vector<CGPNode> curInputs;

	// we have outputs sets and this will be the currnet one
	std::vector<float> curOutputs;

	// the fitness of a network in evealuating a single data set
	float currentFitness;

	// this is the max fitness in a generation
	float maxCurrentFitness;

	// used for progress bars, how far out we are
	float fracDone;

	// initialise this value so that we can loop over the data sets
	numOfDataSets = trainInputs.size();

	// loop over all runs
	for (int i = 0; i < numOfRuns; i++) { 
		// loop over all generations and reinitialise the network each time
		if (i != 0) initialise();
		for (int j = 0; j < numOfGenerations; j++) {
			// if there is a progress dialog and its cancel button has been hit
			// the leave this
			if (progressDialog.getIsCancelled() == true) {
				progressDialog.enableOK();
				EnableWindow(hWnd,TRUE);
				return false;
			}
			// work out the fraction done for the progress dialog, note
			// this might slow things a bit
			fracDone = (i / static_cast<float>(numOfRuns)) + 
				        (((j + 1) / static_cast<float>(numOfGenerations)) * 
						                 (1 / static_cast<float>(numOfRuns)));
			// update the progress bar
			progressDialog.updateDialog(fracDone);
			
			// reset the progress bar each new generation
			maxCurrentFitness = -1;

			// loop over population
			for (int k = 0; k < populationSize; k++) {
				// first of all find the fittest, this must be done using
				// all the training images so we add the fitness each time
				currentFitness = 0;

				// loop over the data sets, e.g. data for each image
				for (int l = 0; l < numOfDataSets; l++) {
					// get the inputs to apply
					curInputs = trainInputs[l];

					// get the real outputs we want to get
					curOutputs = desiredTrainOutputs[l];
					networks[k].setInputs(curInputs);

					// evaluate the network
					networks[k].evaluate();

					// now get the networks actual outputs for this input set
					std::vector<float> actualOutputs = networks[k].getOutputs();

					// add to current fitness
					currentFitness += calculateFitness(actualOutputs, curOutputs);
					networks[k].resetNodeOutputs();
				}

				// make a stringstream so we can write the data to it
				//stringstream sToPrint;
				//sToPrint << "current fitness: " << currentFitness << endl;
				// now add the stream to text to be printed
				//resWrit.addToMainText(sToPrint.str());


				if (currentFitness > maxCurrentFitness) {
					maxCurrentFitness = currentFitness;
					fittest = &(networks[k]);
				} //if
				
			} //for
			stringstream sToPrint;
			sToPrint << "Max fitness: " << maxCurrentFitness << endl;
			resWrit.addToMainText(sToPrint.str());
			// before evaluation its essential that the network is reset
			// this is done here do its only done once to fittest to save computation
			// time. 
			fittest->resetNodeOutputs();
			// once the fittest has been established it is time to generate a
			// new population
			generateLambdaPlusOne(fittest);

		} //for
		// this one does not get mutated
		//CGPNetwork* runFittest = new runFit(networks[populationSize - 1]);
		fittestArray.push_back(networks[populationSize - 1]);

	} //for
	resWrit.writeToFile();
	if (hWnd != NULL) {
		EnableWindow(hWnd,TRUE);
		progressDialog.setText(string("CGP has now completed"));
		progressDialog.enableOK();
	//	HWND buttonWnd = GetDlgItem(this->hWnd, IDOK);
	//	EnableWindow(buttonWnd, FALSE);
	}
	return true;
} // --- beginCGP -------------------------------------------------------------



float CGP::testNetwork() {

	std::vector<CGPNode> curInputs;
	std::vector<float> curOutputs;
	float currentFitness = 0;
	numOfDataSets = testInputs.size();
	ResultsWriter resWrit(string("C:\\TestingResults.txt"));
	if (hWnd != NULL) {
		EnableWindow(hWnd,FALSE);
		progressDialog.setText(string("Please wait currently testing the CGP network"));
	}
	float fracDone;
	// note that populationSize -1 is the one thats not been mutated, maybe its better to have
	// a seperate CGP network for this for other evolutionary stragegies(this is just for my
	// implementation of lambda+1
	for (int i = 0; i < numOfRuns; i++) {
		currentFitness = 0;
		stringstream sToPrint;
		sToPrint << "Run number: " << i << endl;
		for (int l = 0; l < numOfDataSets; l++) {
			curInputs = testInputs[l];
			curOutputs = desiredTestOutputs[l];
			// after a run all networks are fittest
			//networks[populationSize - 1].setInputs(curInputs);
			//networks[populationSize - 1].evaluate();
			fittestArray[i].setInputs(curInputs);
			fittestArray[i].evaluate();
			std::vector<float> actualOutputs = fittestArray[i].getOutputs();
			currentFitness += calculateFitness(actualOutputs, curOutputs);

			fracDone = ((l+1) / static_cast<float>(numOfDataSets));
				        
			progressDialog.updateDialog(fracDone);


			std::vector<float> floatOuts = fittestArray[i].getRealOutputs();
			float curFloatOut;
			float realDiagnosis;
			for (int k = 0; k < floatOuts.size(); k++) {
				curFloatOut = floatOuts[k];
				realDiagnosis = curOutputs[k];
				sToPrint << "Output: " << curFloatOut << "  Desired Out: " << realDiagnosis; 
				sToPrint << " Actual: " << actualOutputs[k] << endl;
			}
			fittestArray[i].resetNodeOutputs();
		}
		
		
	
		
		sToPrint << "final fitness: " << currentFitness << endl;
		resWrit.addToMainText(sToPrint.str());
		resWrit.writeToFile();
	}

	if (hWnd != NULL) {
		EnableWindow(hWnd,TRUE);
		progressDialog.setText(
			string("CGP testing has now completed, see the output files for results"));
		progressDialog.enableOK();
	}

	return currentFitness;
}




// ----------------------------------------------------------------------------
// calculateFitness
//
// ----------------------------------------------------------------------------
float CGP::calculateFitness(std::vector<float> desOut, std::vector<float> realOut)
{
	std::vector<float>::iterator itDes;
	std::vector<float>::iterator itReal;
	float fitness = 0;
	itReal = realOut.begin();
	for (itDes = desOut.begin(); itDes != desOut.end(); itDes++) {
		if (*itReal == *itDes) fitness++;
		itReal++;

	}
	return fitness;

} // --- calculateFitness -----------------------------------------------------




// ----------------------------------------------------------------------------
// initialise
//
//
// ----------------------------------------------------------------------------
void CGP::initialise() {
	// first ensure that the vector is cleared
	networks.clear();
	// initiate as many networks as specified by population
	CGPNetwork * net;
	for (int i = 0; i < populationSize; i++) {
		net = new CGPNetwork(numOfColumns, numOfRows, functions,
			                 levelsBack, numOfInputs, numOfNodeInputs, 
							 numOfOutputs);
		if (isThreshold = true) {
			net->setThreshold(isThreshold, binaryOutputThreshold);
		}
		networks.push_back(*net);
		delete net;
	}



} // --- initialise -----------------------------------------------------------



bool CGP::saveInputs(string filename) {
	
	ofstream out(filename.c_str());
	out.exceptions(ios::badbit);
	try {
	for (int i = 0; i < trainInputs.size(); i++) {
		std::vector<CGPNode> trainInputSet = trainInputs[i];
		out << "TRAININGINPUTS ";
		float toWrite; 
		for (int j = 0; j < trainInputSet.size(); j++) {
			toWrite = trainInputSet[j].getOutput();
			out << toWrite << " ";
		}
		out << endl;

	}


	for (int i = 0; i < testInputs.size(); i++) {
		std::vector<CGPNode> testInputSet = testInputs[i];
		out << "TESTINGINPUTS ";
		float toWrite; 
		for (int j = 0; j < testInputSet.size(); j++) {
			toWrite = testInputSet[j].getOutput();
			out << toWrite << " ";
		}
		out << endl;

	}


	for (int i = 0; i < desiredTrainOutputs.size(); i++) {
		std::vector<float> trainOutputSet = desiredTrainOutputs[i];
		out << "TRAININGOUTPUTS ";
		float toWrite; 
		for (int j = 0; j < trainOutputSet.size(); j++) {
			toWrite = trainOutputSet[j];
			out << toWrite << " ";
		}
		out << endl;

	}


	for (int i = 0; i < desiredTestOutputs.size(); i++) {
		std::vector<float> testOutputSet = desiredTestOutputs[i];
		out << "TESTINGOUTPUTS ";
		float toWrite; 
		for (int j = 0; j < testOutputSet.size(); j++) {
			toWrite = testOutputSet[j];
			out << toWrite << " ";
		}
		out << endl;

	}
	}
	catch (ofstream::failure e) {
		return false;
	}

	return true;

}


bool CGP::loadInputs(string filename) {
	int hasTrainIn = 0;
	int hasTrainOut = 0;
	int hasTestIn = 0;
	int hasTestOut = 0;
	trainInputs.clear();
	testInputs.clear();
	desiredTrainOutputs.clear();
	desiredTestOutputs.clear();
	
	ifstream in(filename.c_str());
	in.exceptions(ios::badbit);
	//in,exceptions
	std::string s;
	stringstream sstream;
	float value;
	CGPNode* cgpNode;
	try {
	while (std::getline(in, s)) {
		if (s.find("TRAININGINPUTS") != string::npos) {
			hasTrainIn++;
			stringstream sstream(s);
			char start[20];
			sstream >> start;
			std::vector<CGPNode> inputArray;
			while (sstream >> value) {
				cgpNode = new CGPNode();
				cgpNode->setOutput(value);
				inputArray.push_back(*cgpNode);
			}
			trainInputs.push_back(inputArray);
		}
		if (s.find("TESTINGINPUTS") != string::npos) {
			hasTestIn++;		
			stringstream sstream(s);
			std::vector<CGPNode> inputArray;
			char start[20];
			sstream >> start;
			while (sstream >> value) {
				cgpNode = new CGPNode();
				cgpNode->setOutput(value);
				inputArray.push_back(*cgpNode);
			}
			testInputs.push_back(inputArray);
		}
		if (s.find("TRAININGOUTPUTS") != string::npos) {
			hasTrainOut++;
			stringstream sstream(s);
			std::vector<float> outputArray;
			char start[20];
			sstream >> start;
			while (sstream >> value) {
				outputArray.push_back(value);
			}
			desiredTrainOutputs.push_back(outputArray);
		}
		if (s.find("TESTINGOUTPUTS") != string::npos) {
			hasTestOut++;
			stringstream sstream(s);
			std::vector<float> outputArray;
			char start[20];
			sstream >> start;
			while (sstream >> value) {
				outputArray.push_back(value);
			}
			desiredTestOutputs.push_back(outputArray);
		}


	}
	}
	catch (ofstream::failure e) {
		trainInputs.clear();
		testInputs.clear();
		desiredTrainOutputs.clear();
		desiredTestOutputs.clear();
		return false;
	}
	if ((hasTrainIn >= 0) && (hasTrainOut >= 0) && 
		(hasTestIn >= 0) && (hasTestOut >= 0) ) 
		return true;
	else return false;


}



void CGP::generateNewPopulation(CGPNetwork* fittest) {
	generateLambdaPlusOne(fittest);

}


// ----------------------------------------------------------------------------
// generateLambdaPlusOne
//
// ----------------------------------------------------------------------------
void CGP::generateLambdaPlusOne(CGPNetwork* fittest) {
	// replicate the fittest for all the population
	for (int i = 0; i < populationSize; i++) {
		networks[i] = *fittest;

	}
	for (int i = 0; i < (populationSize - 1); i++) {
		networks[i].mutate(mutationRate);
	}



} // --- generateLambdaPlusOne ------------------------------------------------




void CGP::TournamentSelection() {



}



void CGP::addTrainingInputs(std::vector<float> trainInputs) {
	//int i = 0;
	CGPNode* newNode;
	std::vector<CGPNode> convertedInput;
	for (int i = 0; i < trainInputs.size(); i++) {
		newNode = new CGPNode();
		newNode->setOutput(trainInputs[i]);
		convertedInput.push_back(*newNode);

	}
	this->trainInputs.push_back(convertedInput);
	int it = this->trainInputs.size();
	//it++;

}



void CGP::addTrainingOutputs(std::vector<float> trainOutputs) {
	desiredTrainOutputs.push_back(trainOutputs);
}


void CGP::addTestingInputs(std::vector<float> testInputs) {
	//int i = 0;
	CGPNode* newNode;
	std::vector<CGPNode> convertedInput;
	for (int i = 0; i < testInputs.size(); i++) {
		newNode = new CGPNode();
		newNode->setOutput(testInputs[i]);
		convertedInput.push_back(*newNode);

	}
	this->testInputs.push_back(convertedInput);
}

void CGP::addTestingOutputs(std::vector<float> testOutputs) {
	desiredTestOutputs.push_back(testOutputs);
}


// number of times the program runs
inline void CGP::setNumOfRuns(int numOfRuns){
	this->numOfRuns = numOfRuns;
}

	// number of generations i.e. times a new population is created on a single run
inline void CGP::setNumOfGenerations(int numOfGenerations){
	this->numOfGenerations = numOfGenerations;
}

	// size of population, i.e. number of functions
inline void CGP::setPopulationSize(int populationSize){
	this->populationSize = populationSize;
}

	// if mutation is being used this provides the rate for fixed rate schemes
	// Its a floating point between 0 and 1
inline void CGP::setMutationRate(int mutationRate) {
	this->mutationRate = mutationRate;
}

	// The number of columns in a CGP scheme
inline void CGP::setNumOfColumns(int numOfColumns) {
	this->numOfColumns = numOfColumns;
}

	// The number of rows in the scheme assuming this is fixed
	// It could be that in order to force some filter perhaps you
	// might want to half this each time
inline void CGP::setNumOfRows(int numOfRows) {
	this->numOfRows = numOfRows;
}


void CGP::setNumOfInputs(int numOfInputs) {
	this->numOfInputs = numOfInputs;
}

void CGP::setNumOfOutputs(int numOfOutputs) {
	this->numOfOutputs = numOfOutputs;
}

//inline void CGP::setNumOfDataSets(int numOfDataSets) {
//	this->numOfDataSets = numOfDataSets;
//}


	// If using a lambda + something scheme this is the lambda used
inline void CGP::setLambda(int lambda) {
	this->lambda = lambda;
}



	// number of times the program runs
inline int CGP::getNumOfRuns() {
	return numOfColumns;
}

	// number of generations i.e. times a new population is created on a single run
inline int CGP::getNumOfGenerations() {
	return numOfGenerations;
}

	// size of population, i.e. number of functions
inline int CGP::getPopulationSize() {
	return populationSize;
}

	// if mutation is being used this provides the rate for fixed rate schemes
	// Its a floating point between 0 and 1
inline int CGP::getMutationRate() {
	return mutationRate;
}

	// The number of columns in a CGP scheme
inline int CGP::getNumOfColumns() {
	return numOfColumns;
}

	// The number of rows in the scheme assuming this is fixed
	// It could be that in order to force some filter perhaps you
	// might want to half this each time
inline int CGP::getNumOfRows() {
	return numOfRows;
}

	// If using a lambda + something scheme this is the lambda used
inline int CGP::getLambda() {
	return lambda;
}




