#ifndef PIXELARRAY_H
#define PIXELARRAY_H

// ----------------------------------------------------------------------------
// PixelArray
//
// ----------------------------------------------------------------------------
template<class T>
class PixelArray {
private:
	int width;
	int height;
	T* array;
public:
	PixelArray(int width, int height, T* array)  {
		this->width = width;
		this->height = height;
		this->array = array;
	}
	
	~PixelArray() {
//		delete array;
	}

	void calculateMax();

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;

	}

	int getMax() {
		return max;

	}

	T* getArray() {
		return array;
	}

	void setWidth(int width) {
		this->width = width;
	}

	void setHeight(int height){
		this->height = height;
	}

	void setArray(T* array) {
		this->array = array;
	}


}; // --- class PixelArray -------------------------------------------

#endif