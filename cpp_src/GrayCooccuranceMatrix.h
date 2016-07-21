#ifndef GRAYOCCURANCEMATRIX_H
#define GRAYOCCURANCEMATRIX_H



// ----------------------------------------------------------------------------
// GrayOccuranceMatrix
//
// ----------------------------------------------------------------------------
class GrayCooccuranceMatrix {
private:
	int width;
	int height;
	float* matrix;
	float max;
	float secondMoment;
	float thirdMoment;
	float entropy;
	float elementDifferenceMoment;
	float uniformity;
public:
	GrayCooccuranceMatrix(int width, int height, float* matrix)  {
		this->width = width;
		this->height = height;
		this->matrix = matrix;
	}
	
	void calculateMax();

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;

	}

	float getMax() {
		return max;

	}

	float* getMatrix() {
		return matrix;
	}

	void setWidth(int width) {
		this->width = width;
	}

	void setHeight(int height){
		this->height = height;
	}

	void setMatrix(float* matrix) {
		this->matrix = matrix;
	}

	void setSecondMoment(float secondMoment) {
		this->secondMoment = secondMoment;
	}	

	float getSecondMoment() {
		return secondMoment;
	}

	void setThirdMoment(float thirdMoment) {
		this->thirdMoment = thirdMoment;
	}	

	float getThirdMoment() {
		return thirdMoment;
	}


}; // --- class GrayOccuranceMatrix -------------------------------------------

#endif