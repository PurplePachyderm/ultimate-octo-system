#include <iostream>

#include <opencv2/opencv.hpp>

#include "../Camera/Camera.hpp"
#include "../Color/Color.hpp"


	// We define our custom namespace & classes to abstract OpenCV function calls
	// This class provides an interface to detect/track objects of one or several specific
	// colors, as well as a demo function

namespace eur {
	class ColorTracking;
}


class eur::ColorTracking: public eur::Camera {
	public:
		std::vector<eur::Color> colors;	// Colors to be detected
		unsigned int hTolerance, sTolerance, vTolerance;	// Hue/saturation/value tolerance

		// Frame processing methods
		cv::Mat canny();
		std::vector<std::vector<cv::Point>> getEdges();


	private:

		// hsvFrame: frame converted to HSV, colorOut: output frame
		cv::Mat hsvFrame, colorOut;

		int demo();	// virtual
};
