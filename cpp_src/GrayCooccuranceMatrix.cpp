#include "GrayCooccuranceMatrix.h"

void GrayCooccuranceMatrix::calculateMax() {
	max = 0;
	for (int i = 0; i < (width *height); i++) {
		if (matrix[i] > max) max = matrix[i];

	}


}