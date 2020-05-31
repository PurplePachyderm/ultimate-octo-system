#include <iostream>

#include <opencv2/opencv.hpp>

#include "../Color/Color.hpp"


	// We define our custom namespace & classes to abstract OpenCV function calls

namespace eur {
    class Contouring;
}


class eur::Contouring {
	public:
		int thresh = 42;	// Threshold for contour detection
		unsigned int demoFrameTime = 34;	//Used to change framerate of the demo (ms)

		// Frame processing methods
		int setCameraInput();	//Use first camera (ID = 0)
		int setCameraInput(int cameraId);	//Use your custom ID

		cv::Mat getFrame();
		cv::Mat canny();
		std::vector<std::vector<cv::Point>> getEdges();


		int launchCannyDemo();	//Use first camera (ID = 0)
		int launchCannyDemo(int cameraId);	//Use your custom ID


	private:
		cv::VideoCapture camera;

		// inFrame: camera input, grayFrame: intermediate grayscale, cannyOut: output frame
		cv::Mat inFrame, grayFrame, cannyOut;

		int cannyDemo();
};
