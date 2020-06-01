#include <iostream>
#include <math.h>

#include "ColorTracking.hpp"


// Those external callback functions are necessaty since the trackbar callback
// must be prototyped as void foo(int, void *): methods have a hidden this
// pointer, and can not be used as such.

void saturationCallback(int, void * params) {
	eur::ColorTracking * colorTracking = (eur::ColorTracking*) params;
	colorTracking->updateSTolerance();
}

void valueCallback(int, void * params) {
	eur::ColorTracking * colorTracking = (eur::ColorTracking*) params;
	colorTracking->updateVTolerance();
}



cv::Mat eur::ColorTracking::hsvConversion() {

	cv::cvtColor(inFrame, hsvFrame, cv::COLOR_RGB2HSV);

	return hsvFrame;
}



cv::Mat eur::ColorTracking::colorFilter() {

	// OpenCV uses the following HSV ranges:
	// 	Hue: 0-180
	// 	Saturation: 0-255
	// 	Value: 0-255
	int minHueRange = std::max(0, colors[0].getHue() - hTolerance) / 2;
	int maxHueRange = std::min(360, colors[0].getHue() + hTolerance) / 2;
	int minSaturationRange = (int) (std::max((float) 0.0, colors[0].getSaturation() - sTolerance) * 255);
	int maxSaturationRange = (int) (std::min((float) 1.0, colors[0].getSaturation() + sTolerance) * 255);
	int minValueRange = (int) (std::max((float) 0.0, colors[0].getValue() - vTolerance) * 255);
	int maxValueRange = (int) (std::min((float) 1.0, colors[0].getValue() + vTolerance) * 255);


	cv::inRange(hsvFrame, cv::Scalar(minHueRange, minSaturationRange, minValueRange), cv::Scalar(maxHueRange, maxSaturationRange, maxValueRange), filteredFrame);

	return hsvFrame;
}



void eur::ColorTracking::updateSTolerance() {
	sTolerance = intSTolerance / 1000.0;
}



void eur::ColorTracking::updateVTolerance() {
	vTolerance = intVTolerance / 1000.0;
}



int eur::ColorTracking::demo() {

	// Create display windows
	cv::namedWindow("Webcam input", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Color tracking output", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("Hue tolerance :", "Color tracking output", &hTolerance, 180);
	cv::createTrackbar("Saturation tolerance  :", "Color tracking output", &intSTolerance, 500, saturationCallback, this);
	cv::createTrackbar("Value tolerance  :", "Color tracking output", &intVTolerance, 500, valueCallback, this);


	// Camera update loop
	std::cout << "Press ESC to exit ..." << std::endl;

	while (1) {
		getFrame();

		// TODO Processing
		hsvConversion();
		colorFilter();

		cv::imshow("Webcam input", inFrame);
		cv::imshow("Color tracking output", filteredFrame);

		// Applying byte mask to eliminate useless 1
		int key = cv::waitKey(demoFrameTime) & 0xFF;

		// If key is ESC, exit loop
		if(key == 27)
			break;
	}


	return 0;
}
