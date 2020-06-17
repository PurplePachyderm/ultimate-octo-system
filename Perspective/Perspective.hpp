#include <iostream>

#include <opencv2/opencv.hpp>

#include "../Camera/Camera.hpp"


// We define our custom namespace & classes to abstract OpenCV function calls
// This class provides an interface to convert the perspective of a rectangle.

namespace eur {
	class Perspective;
}


class eur::Perspective: public eur::Camera {
	public:

		// Frame processing methods
		void calibrate();
		cv::Mat getTransformMartrix();

		cv::Mat flatten();
		int width, height;

		std::vector<cv::Point2f> convertPoints();

	private:

		// grayFrame: intermediate grayscale, cannyOut: output frame
		cv::Mat flatFrame, demoFrame;

		bool calibrationDone = false;

		// The points must be in the following order:
		// top-left; top-right; bottom-right; bottom-left
		std::vector<cv::Point2f> calibrationPoints;
		cv::Mat transformMatrix;

		std::vector<cv::Point2f> imagePoints, convertedPoints;

		int demo();	// virtual


};
