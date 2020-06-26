#include <iostream>

#include <opencv2/opencv.hpp>

#include "../Camera/Camera.hpp"


// We define our custom namespace & classes to abstract OpenCV function calls
// This class provides an interface to convert the perspective of a rectangle.

namespace eur {
	class ShapeDetection;
}


class eur::ShapeDetection: public eur::Camera {
	public:
		cv::Mat grey();	// Prepares frame by applying grey filter
		cv::Mat canny();
		std::vector<std::vector<cv::Point>> getPolys();

		int thresh = 42;

	private:
		int demo();	// virtual

		cv::Mat greyFrame, cannyFrame;

		std::vector<std::vector<cv::Point>> contours, polys;
		std::vector<cv::Point2f> centers;
		std::vector<cv::Rect> boundRect;
		std::vector<float>radius;
};
