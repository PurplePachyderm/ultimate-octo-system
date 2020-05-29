#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>


/*****************************************************************************/


int main(int, char**) {

	// Open the first found camera
	cv::VideoCapture camera(0);
	if (!camera.isOpened()) {
		std::cerr << "ERROR: Could not open camera" << std::endl;
	return 1;
	}


	// Create display window
	cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);


	// Camera update loop
	std::cout << "Press ESC to exit ..." << std::endl;

	cv::Mat frame;
	while (1) {
		camera >> frame;

		cv::imshow("Webcam", frame);

		// Wait for 17 ms (60fps)
		int key = cv::waitKey(17) & 0xFF;

		// If key is ESC, exit loop
		if(key == 27)
			break;
	}


	return 0;
}
