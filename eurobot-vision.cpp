#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "ColorMask/ColorMask.hpp"
#include "Contouring/Contouring.hpp"
#include "ColorTracking/ColorTracking.hpp"


/*****************************************************************************/


int main(int, char**) {


	// Contouring demo

	// eur::Contouring contouring;
	// contouring.launchDemo();



	// Color tracking demo

	std::vector<eur::ColorMask> colorMasks {
		eur::ColorMask(115, 145, 120, 255, 30, 115, "Red"),
		eur::ColorMask(30, 45, 210, 255, 15, 80, "Green"),
		eur::ColorMask(0, 20, 175, 255, 50, 170, "Blue"),
		eur::ColorMask(80, 100, 85, 255, 55, 125, "Yellow"),
		eur::ColorMask(100, 122, 130, 255, 85, 160, "Orange"),
		eur::ColorMask(0, 25, 60, 130, 85, 255, "White")
	};


	eur::ColorTracking colorTracking;
	colorTracking.colorMasks = colorMasks;
	// colorTracking.launchMaskDemo();
	colorTracking.launchDemo();

	return 0;
}
