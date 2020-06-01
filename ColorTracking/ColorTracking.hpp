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
		int hTolerance = 5; // Hue tolerance
		void updateSTolerance();
		void updateVTolerance();

		int intSTolerance = 50;
		int intVTolerance = 50;

		// Frame processing methods
		cv::Mat hsvConversion();
		cv::Mat colorFilter();
		std::vector<std::vector<cv::Point>> getObjects();



	private:

		// hsvFrame: frame converted to HSV, colorOut: output frame
		cv::Mat hsvFrame, filteredFrame, colorOut;

		int demo();	// virtual

		float sTolerance = 0.05;	// Saturation tolerance
		float vTolerance = 0.05;	// Value tolerance

};
