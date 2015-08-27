#include "FeatureExtractor.h"

using namespace std;

// ----------------------------------------------------------------------------
// setSpatialGrayDependenceMatrix
//
// ----------------------------------------------------------------------------
void FeatureExtractor::setSpatialGrayDependenceMatrix(unsigned short* pixels, short width, 
			short height, int xDist,int yDist,
		    int numOfGrayLevels) {
    float maxGrayLevel = 500;
	
	// ths first thing to do is to form a new matrix of pixels because we are making a 
    // matrix of the gray level squared which could end up very big and time consuming 
    // to work with, thus map gray levels to range 0 to 500
	float scaler = (maxGrayLevel - 1) / static_cast<float>(numOfGrayLevels - 1);

    //unsigned short* compPixelArray = new unsigned short[width * height];
	int* compPixelArray = new int[width * height];
	float currentScaledValue;
	unsigned short currentValue;
	//for (int i = 0; i < (width * height); i++) {
	//	compPixelArray[i] = static_cast<unsigned short>(static_cast<float>(pixels[i]) * scaler);
	//}
	for (int i = 0; i < (width * height); i++) {
		currentValue = pixels[i];
		currentScaledValue = (static_cast<float>(currentValue) * scaler);
		int intVal(currentScaledValue + 0.5);
		compPixelArray[i] = intVal;;
	}

	// we form the spatial gray dependence or cooccurance matrix
	float* SGDM = new float[maxGrayLevel * maxGrayLevel];
	int SGDMIndex;
	for (int y = 0; y < maxGrayLevel; y++) {
		for (int x = 0; x < maxGrayLevel; x++) {
			float numOfOccurances = findNumberOfOccurances(compPixelArray, 
											width, height, x, y, xDist, yDist);
			
			SGDMIndex = (y * maxGrayLevel) + x;
			SGDM[SGDMIndex] = numOfOccurances;
		}

	}
	// finally we want to turn this matrix into a measure of the joint probability
	float maxNumOfChances = (width - abs(xDist)) * (height - abs(yDist));
	for (int i = 0; i < (maxGrayLevel * maxGrayLevel); i++) {
		SGDM[i] = SGDM[i] / maxNumOfChances;
	}
	grayCoocList.push_back(new GrayCooccuranceMatrix(maxGrayLevel, maxGrayLevel, SGDM));

} // --- setSpatialGrayDependenceMatrix ---------------------------------------




// ----------------------------------------------------------------------------
// findNumberOfOccurances
//
// ----------------------------------------------------------------------------
int FeatureExtractor::findNumberOfOccurances(int* compPixelArray, int width, int height, int SMaX,
											 int SMaY, int xDist, int yDist) {
	
	int index;
	int secondIndex;
	int secondX;
	int secondY;
	int accumulator = 0;
	
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++) {
			index = ( (i * width) + j );
				if (SMaX == compPixelArray[index]) {
					secondX = j - xDist;
					secondY = i - yDist;
					secondIndex = (secondY * width) + secondX;
					if ((secondIndex >= 0) && (secondX >= 0) && (secondY >= 0)
						&& (secondX < width) && (secondY < height)) {
						if (compPixelArray[secondIndex] == SMaY) {
							accumulator++;
						}
					}

				}
		}
	}
	return accumulator;
} // --- findNumberOfOccurances -----------------------------------------------




// ----------------------------------------------------------------------------
// calculateSGDMax
//
// ----------------------------------------------------------------------------
void FeatureExtractor::calculateSGDMFeatures(int numOfGrayLevels) {
	list<GrayCooccuranceMatrix*>::iterator it;
	GrayCooccuranceMatrix* current;
//	int width;
//	int height;
	float secondMoment;
	float thirdMoment;
	for (it = grayCoocList.begin(); it != grayCoocList.end(); it++) {
		current = *it;
		current->calculateMax();
		secondMoment = getNthMoment(current->getMatrix(), 
			current->getWidth(), current->getHeight(),numOfGrayLevels, 2);
		current->setSecondMoment(secondMoment);
		thirdMoment = getNthMoment(current->getMatrix(), 
			current->getWidth(), current->getHeight(), numOfGrayLevels, 3);
		current->setThirdMoment(thirdMoment);
	}
}


float FeatureExtractor::getNthMomentByHistogram(unsigned short* pixels, short width, short height,
									 int numOfGrayLevels, short n) {
	float mean = getMean(pixels, width * height);
	float* histogram = getHistogram(pixels, width*height, numOfGrayLevels);
	
	float accumulator = 0;
	float poweredDifference;
	float differenceMultProb;
	for (int i = 0; i < numOfGrayLevels; i++) {
		poweredDifference = pow( static_cast<float>(i - mean) , static_cast<float>(n));
		differenceMultProb = poweredDifference * histogram[i];
		accumulator += differenceMultProb;
	}
	// normalise
	accumulator  = accumulator / 
		static_cast<float>(pow((numOfGrayLevels - 1), n));

	return accumulator;
}

float FeatureExtractor::getNthMoment(float* matrix, int width, int height,int numOfGrayLevels, short n) {
	float mean = getMean(matrix, width * height);
	//float* histogram = getHistogram(pixels, width*height, numOfGrayLevels);
	
	float accumulator = 0;
	float poweredDifference;
	float multPoweredDifference;
	// multiply each square by this so that probability is found
	float multiplier = 1 / static_cast<float>(width * height);
	//float differenceMultProb;
	for (int i = 0; i < (width * height); i++) {
		poweredDifference = pow( static_cast<float>(matrix[i] - mean) ,
			static_cast<float>(n));
		multPoweredDifference = poweredDifference / multiplier;
		//differenceMultProb = poweredDifference * histogram[i];
		accumulator += poweredDifference;
	}
	accumulator  = accumulator / 
		static_cast<float>(pow((numOfGrayLevels - 1), n));

	return accumulator;
}


float FeatureExtractor::getEntropy(float* matrix, int width, int height){
	return 0;
}

float FeatureExtractor::getElDifMoment(float* matrix, int width, int height){
	return 0;
}

float FeatureExtractor::getUniformity(float* matrix, int width, int height){
	return 0;
}

float FeatureExtractor::getMean(float* pixels, int numOfItems) {
	int accumulator = 0;
	int current;
	for (int i = 0; i < numOfItems; i++) {
		current = pixels[i];
		accumulator = accumulator + current;


	}
	return (static_cast<float>(accumulator) / static_cast<float>(numOfItems));

}

float FeatureExtractor::getMean(unsigned short* pixels, int numOfItems) {
	int accumulator = 0;
	int current;
	for (int i = 0; i < numOfItems; i++) {
		current = pixels[i];
		accumulator = accumulator + current;


	}
	return (static_cast<float>(accumulator) / static_cast<float>(numOfItems));

}


float* FeatureExtractor::getHistogram(unsigned short* pixels, int numOfItems, int numOfGrayLevels) {
	int accumulator = 0;
	float* histogram = new float[numOfGrayLevels];
	// initialise to zero
	for (int i = 0; i < numOfGrayLevels; i++) {
		histogram[i] = 0;
	}
	
	int currentGrayLevel;
	for (int i = 0; i < numOfItems; i++) {
		currentGrayLevel = pixels[i];
		histogram[currentGrayLevel]++;

	}
	for (int i = 0; i < numOfItems; i++) {
		histogram[currentGrayLevel] = histogram[currentGrayLevel]
		/ static_cast<float>(numOfItems);
	}
	return histogram;

}