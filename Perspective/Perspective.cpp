#include "Perspective.hpp"


cv::Mat eur::Perspective::getTransformMartrix() {

	cv::Point2f calPoints [4];
	calPoints[0] = calibrationPoints[0];
	calPoints[1] = calibrationPoints[1];
	calPoints[2] = calibrationPoints[2];
	calPoints[3] = calibrationPoints[3];

	cv::Point2f flatPoints [4];
	flatPoints[0] = cv::Point2f(0, 0);
	flatPoints[1] = cv::Point2f(width, 0);
	flatPoints[2] =  cv::Point2f(width, height);
	flatPoints[3] = cv::Point2f(0, height);


	transformMatrix = cv::getPerspectiveTransform(calPoints, flatPoints);

	return transformMatrix;
}



cv::Mat eur::Perspective::flatten() {
	flatFrame = cv::Mat(cv::Size(width, height), CV_64FC1);

	cv::warpPerspective(inFrame, flatFrame, transformMatrix, flatFrame.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT);

	return flatFrame;
}



std::vector<cv::Point2f> eur::Perspective::convertPoints() {
	// Convert vector to standard array

	if(imagePoints.size() > 0) {
		perspectiveTransform(imagePoints, convertedPoints, transformMatrix);
	}


	return convertedPoints;
}



void onMouseCalibration(int evt, int x, int y, int flags, void* param) {
    if(evt == cv::EVENT_LBUTTONDOWN) {


		std::vector<cv::Point2f>* calibrationPoints = (std::vector<cv::Point2f>*)param;

		if(calibrationPoints->size() < 4) {
			std::cout << "Pushing calibration point: " << x << ", " << y << std::endl;

			calibrationPoints->push_back(cv::Point2f(x,y));
		}

    }
}


void onMouseConversion(int evt, int x, int y, int flags, void* param) {
    if(evt == cv::EVENT_LBUTTONDOWN) {


		std::vector<cv::Point2f>* imagePoints = (std::vector<cv::Point2f>*)param;

		std::cout << "Pushing conversion point: " << x << ", " << y << std::endl;


		imagePoints->push_back(cv::Point2f(x,y));

    }
}



int eur::Perspective::demo() {

	// Create display windows
	cv::namedWindow("Webcam input", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Flattened image", cv::WINDOW_AUTOSIZE);


	// Listen to mouse click
	cv::setMouseCallback("Webcam input", onMouseCalibration, (void*)&calibrationPoints);
	int X, Y;


	// Camera update loop
	std::cout << "Press ESC to exit ..." << std::endl;

	while (1) {
		getFrame();

		demoFrame = inFrame.clone();

		if(calibrationPoints.size() >= 4) {
			calibrationDone = true;
			cv::setMouseCallback("Webcam input", onMouseConversion, (void*)&imagePoints);
		}

		// Calibration phase
		if(!calibrationDone) {
			cv::putText(demoFrame, "Select points for calibration", cv::Point2f(20,30), 2, 1, cv::Scalar(0,255,0), 2);
		}

		// Conversion phase
		else {
			cv::putText(demoFrame, "Choose point to convert", cv::Point2f(20,30), 2, 1, cv::Scalar(0,0,255), 2);

			getTransformMartrix();
			flatten();

			convertPoints();
		}

		// Draw calibration points
		for(unsigned int i=0; i<calibrationPoints.size(); i++) {
			cv::circle(demoFrame, calibrationPoints[i], 5, cv::Scalar(0,255,0), 1, 8, 0);
		}

		// Draw points to convert
		for(unsigned int i=0; i<imagePoints.size(); i++) {
			cv::circle(demoFrame, imagePoints[i], 5, cv::Scalar(0,0,255), 1, 8, 0);
		}

		// Draw converted points on flat image, if calibration is done
		if(calibrationDone) {
			for(unsigned int i=0; i<convertedPoints.size(); i++) {
				cv::circle(flatFrame, convertedPoints[i], 5, cv::Scalar(0,0,255), 1, 8, 0);
			}
		}


		cv::imshow("Webcam input", demoFrame);

		if(calibrationDone) {
			cv::imshow("Flattened image", flatFrame);
		}

		// Applying byte mask to eliminate useless 1
		int key = cv::waitKey(demoFrameTime) & 0xFF;

		// If key is ESC, exit loop
		if(key == 27)
			break;
	}


	return 0;
}
