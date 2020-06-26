#include <iostream>

#include <opencv2/opencv.hpp>

#include "../Camera/Camera.hpp"
#include "../ColorMask/ColorMask.hpp"


	// We define our custom namespace & classes to abstract OpenCV function calls
	// This class provides an interface to detect/track objects of one or several specific
	// colors, as well as a demo function


namespace eur {
	class ColorTracking;
}



class eur::ColorTracking: public eur::Camera {
	public:

		std::vector<eur::ColorMask> colorMasks;	// Colors to be detected
		double maxNoiseArea = 5000.0;	// Defines the maximum size a noise can have, before beinf considered an object

		// Used for mask demo
		int minHueRange, maxHueRange;
		int minSaturationRange, maxSaturationRange;
		int minValueRange, maxValueRange;

		// Frame processing methods
		cv::Mat hsvConversion();
		cv::Mat slideFilter();	// Demo only
		std::vector<cv::Mat> masksFilter();
		std::vector<std::vector<cv::Point>> getObjects();
		cv::Mat drawOutput(); // Draws points on camera output for demo

		int launchMaskDemo();
		int launchMaskDemo(int cameraId);


	private:

		// hsvFrame: frame converted to HSV, filteredFrame: applied mask, colorOut: output frame (text for demo)
		cv::Mat hsvFrame, filteredFrame, colorOut;
		std::vector<cv::Mat> filteredFrames;	// One fram per mask
		std::vector<std::vector<cv::Point>> objects;	// One vector of points / mask

		int maskDemo();
		int demo();	// virtual

};
