#include "Contouring.hpp"


cv::Mat eur::Contouring::canny(cv::Mat) {
	// Simply detects all contours in an image
	// WARNING Assumes inFrame is already set up

	// Noise elimination && greyscale conversion
	cv::cvtColor(inFrame, grayFrame, cv::COLOR_BGR2GRAY);
	cv::blur(grayFrame, grayFrame, cv::Size(5,5));

	// Contour detection
	Canny(grayFrame, cannyOut, thresh, thresh * 2);

	return cannyOut;

}



int eur::Contouring::setCameraInput() {
	camera.open(0, cv::CAP_ANY);
	if (!camera.isOpened()) {
		std::cerr << "ERROR: Could not open camera" << std::endl;
		return 1;
	}

	return 0;
}



int eur::Contouring::setCameraInput(int cameraId) {
	camera.open(cameraId, cv::CAP_ANY);
	if (!camera.isOpened()) {
		std::cerr << "ERROR: Could not open camera" << std::endl;
		return 1;
	}

	return 0;
}



int eur::Contouring::launchCannyDemo() {
	int cameraError = setCameraInput();
	if(cameraError) {
		return cameraError;
	}

	return cannyDemo();
}



int eur::Contouring::launchCannyDemo(int cameraId) {
	int cameraError = setCameraInput(cameraId);
	if(cameraError) {
		return cameraError;
	}

	return cannyDemo();
}



int eur::Contouring::cannyDemo() {

	// Create display windows
	cv::namedWindow("Webcam input", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Contouring output", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("Canny threshold :", "Contouring output", &thresh, 255);


	// Camera update loop
	std::cout << "Press ESC to exit ..." << std::endl;

	while (1) {
		camera >> inFrame;

		canny(inFrame);

		cv::imshow("Webcam input", inFrame);
		cv::imshow("Contouring output", cannyOut);

		// Applying byte mask to eliminate useless 1
		int key = cv::waitKey(demoFrameTime) & 0xFF;

		// If key is ESC, exit loop
		if(key == 27)
			break;
	}


	return 0;
}
