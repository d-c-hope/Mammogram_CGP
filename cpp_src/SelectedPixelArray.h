#ifndef SELECTEDPIXELARRAY_H
#define SELECTEDPIXELARRAY_H


// a way of adding dimensions to an array
class SelectedPixelArray {
public:

	SelectedPixelArray(short width, short height, short* _selectedArray) {
		this->width = width;
		this->height = height;
		this->selectedArray = selectedArray;
	}

	setWidth(short width) {
		this->width = width;

	}



	setHeight(short height) {

		this->height = height;


	}


	setSelectedPixelArray(unsigned short* selectedArray) {

		this->selectedArray = selectedArray;


	}



	short getWidth() {
		return width;

	}



	short getHeight() {

		return height;


	}


	getSelectedPixelArray() {

		return selectedArray;


	}


private:
	short width;

	short height;

	short* selectedArray;


};






#endif