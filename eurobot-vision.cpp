#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "ColorMask/ColorMask.hpp"
#include "Contouring/Contouring.hpp"
#include "ColorTracking/ColorTracking.hpp"
#include "Perspective/Perspective.hpp"
#include "ShapeDetection/ShapeDetection.hpp"


/*****************************************************************************/


int main(int, char**) {


	std::cout << "OpenCV version : " << CV_VERSION << std::endl;

	// Contouring demo

	// eur::Contouring contouring;
	// contouring.setImageInput("../img/example.png");
	// contouring.launchDemo();



	// Color tracking demo

	// std::vector<eur::ColorMask> colorMasks {
	// 	eur::ColorMask(120, 130, 155, 220, 40, 170, "Red"),
	// 	eur::ColorMask(20, 50, 120, 230, 30, 80, "Green"),
	// 	eur::ColorMask(0, 15, 120, 210, 40, 90, "Blue"),
	// 	eur::ColorMask(85, 105, 155, 215, 40, 170, "Yellow"),
	// 	eur::ColorMask(100, 120, 145, 215, 40, 170, "Orange")
	// };
	//
	//
	// eur::ColorTracking colorTracking;
	// colorTracking.colorMasks = colorMasks;
	// colorTracking.launchMaskDemo(0);
	// colorTracking.launchDemo(0);


	// Contouring demo

	eur::ShapeDetection shapeDetection;
	//shapeDetection.setImageInput("../img/example3.png");
	shapeDetection.launchDemo(0);


	// Perspective demo

	// eur::Perspective perspective;
	// perspective.width = 330;
	// perspective.height = 714;
	//
	// perspective.setImageInput("../img/example2.jpg");
	// perspective.launchDemo();



	return 0;
}
