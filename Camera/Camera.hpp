#pragma once

#define CAMERA 1
#define IMAGE 2

#include <opencv2/opencv.hpp>


	// We define our custom namespace & classes to abstract OpenCV function calls
	// This abstract class aims to provide an interface to easily get frames from a camera
	// and to be reused in all our high level, "feature" classes.
	// It also includes virtual methods to start the demo.


namespace eur {
    class Camera;
}


class eur::Camera {
	public:
		unsigned int demoFrameTime = 34;	// Used to change framerate of the demo (ms)

		int setCameraInput();	// Use first camera (ID = 0)
		int setCameraInput(int cameraId);	// Use your custom ID
		int setImageInput(std::string path);	// Use an image path

		// Frame processing methods
		cv::Mat getFrame();


		int launchDemo();	// Use first camera (ID = 0)
		int launchDemo(int cameraId);	// Use your custom ID
		int launchDemo(std::string path);	// Use an image path


	protected:
		cv::VideoCapture camera;

		cv::Mat inFrame;	// Camera input
		cv::Mat image;

		int input = 0;

		virtual int demo();
};
