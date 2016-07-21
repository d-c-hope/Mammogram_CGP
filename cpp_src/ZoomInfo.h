#ifndef ZOOMINFO_H
#define ZOOMINFO_H


// ----------------------------------------------------------------------------
// class ZoomInfo
//
// this class is used for zooming in on the image so that as the user zooms
// to further levels instances of this class present the level zoomed to
// i.e. the coordinates in the original image that we can currently see
// ----------------------------------------------------------------------------
class ZoomInfo {
	private:
		int topLeftX;
		int topLeftY;
		int width;
		int height;

	public:

		// constructor initializes
		ZoomInfo(int topLeftX, int topLeftY, int width, int height) {
			this->topLeftX = topLeftX;
			this->topLeftY = topLeftY;
			this->width = width;
			this->height = height;
		}

		// returns the top left X coordinate of the image
		void setTopLeftX(int topLeftX) {
			this->topLeftX = topLeftX;
		}

		// sets the top let y coordinate of the image
		void setTopLeftY(int topLeftY) {
			this->topLeftY = topLeftY;
		}

		// sets the width of the image
		void setWidth(int width) {
			this->width = width;
		}

		// sets the height of the image
		void setHeight(int height) {
			this->height = height;
		}

		// returns the top left X coordinate of the image
		int getTopLeftX() {
			return topLeftX;
		}

		// returns the top left Y coordinate of the image
		int getTopLeftY() {
			return topLeftY;
		}

		// returns the width of the image
		int getWidth() {
			return width;
		}
		
		// returns the height of the image
		int getHeight() {
			return height;
		}



}; // --- class ZoomInfo ------------------------------------------------------

#endif
