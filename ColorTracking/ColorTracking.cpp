#include <iostream>
#include <math.h>

#include "ColorTracking.hpp"


cv::Mat eur::ColorTracking::hsvConversion() {

	cv::cvtColor(inFrame, hsvFrame, cv::COLOR_RGB2HSV);

	return hsvFrame;
}



cv::Mat eur::ColorTracking::slideFilter() {
	// Uses the demo slides to create custom filter

	// OpenCV uses the following HSV ranges:
	// 	Hue: 0-180
	// 	Saturation: 0-255
	// 	Value: 0-255

	// Color filtering
	cv::inRange(
		hsvFrame,
		cv::Scalar(minHueRange, minSaturationRange, minValueRange),
		cv::Scalar(maxHueRange, maxSaturationRange, maxValueRange),
		filteredFrame
	);

	// Noise erosion
	cv::erode(filteredFrame, filteredFrame, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
	cv::erode(filteredFrame, filteredFrame, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));

	// Remaining objects dilatation
	cv::dilate(filteredFrame, filteredFrame, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
	cv::dilate(filteredFrame, filteredFrame, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));

	return filteredFrame;
}



std::vector<cv::Mat> eur::ColorTracking::masksFilter() {
	// Uses the colorMasks attribute to return one filtered frame per color mask

	// OpenCV uses the following HSV ranges:
	// 	Hue: 0-180
	// 	Saturation: 0-255
	// 	Value: 0-255


	filteredFrames = std::vector<cv::Mat>(colorMasks.size());

	for(unsigned int i=0; i<colorMasks.size(); i++) {

		int minHueRange = colorMasks[i].lowerColor.getCvHue();
		int maxHueRange = colorMasks[i].upperColor.getCvHue();
		int minSaturationRange = colorMasks[i].lowerColor.getCvSaturation();
		int maxSaturationRange = colorMasks[i].upperColor.getCvSaturation();
		int minValueRange = colorMasks[i].lowerColor.getCvValue();
		int maxValueRange = colorMasks[i].upperColor.getCvValue();

		cv::inRange(
			hsvFrame,
			cv::Scalar(minHueRange, minSaturationRange, minValueRange),
			cv::Scalar(maxHueRange, maxSaturationRange, maxValueRange),
			filteredFrames[i]
		);

		// Noise erosion
		cv::erode(filteredFrames[i], filteredFrames[i], cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
		cv::erode(filteredFrames[i], filteredFrames[i], cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));

		// Remaining objects dilatation
		cv::dilate(filteredFrames[i], filteredFrames[i], cv::getStructuringElement(cv::MORPH_RECT, cv::Size(8, 8)));
		cv::dilate(filteredFrames[i], filteredFrames[i], cv::getStructuringElement(cv::MORPH_RECT, cv::Size(8, 8)));

	}


	return filteredFrames;
}



std::vector<std::vector<cv::Point>> eur::ColorTracking::getObjects() {


	// Filter / object / points
	std::vector < std::vector< std::vector<cv::Point> > > contours (colorMasks.size());
	// Filter / object (coords)
	objects = std::vector< std::vector<cv::Point> > (colorMasks.size());


	std::vector<cv::Vec4i> hierarchy;

	for(unsigned int i = 0; i < colorMasks.size(); i++) {
		findContours(filteredFrames[i], contours[i], hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE );


		for(unsigned int j = 0; j < contours[i].size(); j++) {

			cv::Moments moment = cv::moments((cv::Mat)contours[i][j]);
			double area = moment.m00;

			// Actual object found
			if(area > maxNoiseArea) {
				objects[i].push_back(cv::Point(moment.m10/area , moment.m01/area ));
			}
		}
	}

	return objects;
}



cv::Mat eur::ColorTracking::drawOutput() {

	colorOut = inFrame.clone();

	for(unsigned int i=0; i<objects.size(); i++) {
		for(unsigned int j=0; j<objects[i].size(); j++) {
			cv::putText(colorOut, colorMasks[i].name, objects[i][j], 2,1, cv::Scalar(0,255,0), 2);
		}
	}

	return colorOut;
}



// This demo can be used to demonstrate HSV masks, and to determine a mask
// for a real world color

int eur::ColorTracking::launchMaskDemo() {
	int cameraError = 0;
	if(input != IMAGE) {
		cameraError = setCameraInput();
	}

	if(cameraError) {
		return cameraError;
	}

	return maskDemo();
}



int eur::ColorTracking::launchMaskDemo(int cameraId) {
	int cameraError = setCameraInput(cameraId);
	if(cameraError) {
		return cameraError;
	}

	return maskDemo();
}



int eur::ColorTracking::maskDemo() {

	// Create display windows
	cv::namedWindow("Webcam input", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Color tracking output", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("Hue min :", "Color tracking output", &minHueRange, 180);
	cv::createTrackbar("Hue max :", "Color tracking output", &maxHueRange, 180);
	cv::createTrackbar("Saturation min :", "Color tracking output", &minSaturationRange, 255);
	cv::createTrackbar("Saturation max :", "Color tracking output", &maxSaturationRange, 255);
	cv::createTrackbar("Value min :", "Color tracking output", &minValueRange, 255);
	cv::createTrackbar("Value max :", "Color tracking output", &maxValueRange, 255);


	// Camera update loop
	std::cout << "Press ESC to exit ..." << std::endl;

	while (1) {
		getFrame();

		// Processing
		hsvConversion();
		slideFilter();


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



// This demo shows on screen which colors are detected

int eur::ColorTracking::demo() {
	// Create display windows
	cv::namedWindow("Webcam input", cv::WINDOW_AUTOSIZE);



	// Camera update loop
	std::cout << "Press ESC to exit ..." << std::endl;

	while (1) {
		getFrame();

		// Processing
		hsvConversion();
		masksFilter();

		getObjects();

		drawOutput();


		cv::imshow("Webcam input", colorOut);

		// Applying byte mask to eliminate useless 1
		int key = cv::waitKey(demoFrameTime) & 0xFF;

		// If key is ESC, exit loop
		if(key == 27)
			break;
	}


	return 0;
}
