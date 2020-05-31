#include <iostream>

#include <opencv2/opencv.hpp>

#include "../Camera/Camera.hpp"


	// We define our custom namespace & classes to abstract OpenCV function calls
	// This class provides an interface to get all contours of an image regardless of color
	// as well as a demo fuction.

namespace eur {
    class Contouring;
}


class eur::Contouring: public eur::Camera {
	public:
		int thresh = 42;	// Threshold for contour detection

		// Frame processing methods
		cv::Mat canny();
		std::vector<std::vector<cv::Point>> getEdges();


	private:

		// grayFrame: intermediate grayscale, cannyOut: output frame
		cv::Mat grayFrame, cannyOut;

		int demo();	// virtual
};
