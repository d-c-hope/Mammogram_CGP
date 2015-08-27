#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <math.h>
#include <list>
#include "GrayCooccuranceMatrix.h"

class FeatureExtractor {

private:
	std::list<GrayCooccuranceMatrix*> grayCoocList; 
public:
	void setSpatialGrayDependenceMatrix(unsigned short* pixels, short width, 
										short height, int xDist,int uDist,
										int numOfGrayLevels);

	float getNthMomentByHistogram(unsigned short* pixels, short width, short height, int numOfGrayLEvels, short n);
	float getNthMoment(float* matrix, int width, int height, int numOfGrayLevels,short n);
	float getEntropy(float* matrix, int width, int height);
	float FeatureExtractor::getElDifMoment(float* matrix, int width, int height);
	float FeatureExtractor::getUniformity(float* matrix, int width, int height);
	float getMean(float* pixels, int numOfItems);
	float getMean(unsigned short* pixels, int numOfItems);

	float* getHistogram(unsigned short* pixels, int numOfItems, int numOfGrayLevels);

	int findNumberOfOccurances(int* compPixelArray, int width, int height, int SMaX, int SMaY, int xDist, int yDist);
	

	std::list<GrayCooccuranceMatrix*> getGrayCoocList() {
		return grayCoocList;
	}

	void calculateSGDMFeatures(int numOfGrayLevels);

};

#endif
