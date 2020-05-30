#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>


	// We define our custom namespace & classes to abstract OpenCV function calls

namespace eur {
    class Contouring;
}


class eur::Contouring {
	public:
		int thresh = 42;	// Threshold for contour detection
		unsigned int demoFrameTime = 34;	//Used to change framerate of the demo (ms)

		// Frame processing methods
		cv::Mat canny(cv::Mat);
		// TODO Canny by color ?

		int setCameraInput();	//Use first camera (ID = 0)
		int setCameraInput(int cameraId);	//Use your custom ID

		int launchCannyDemo();	//Use first camera (ID = 0)
		int launchCannyDemo(int cameraId);	//Use your custom ID


	private:
		cv::VideoCapture camera;

		// inFrame: camera input, grayFrame: intermediate grayscale, cannyOut: output frame
		cv::Mat inFrame, grayFrame, cannyOut;

		int cannyDemo();
};
