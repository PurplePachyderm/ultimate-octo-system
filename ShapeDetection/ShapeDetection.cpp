#include "ShapeDetection.hpp"


cv::Mat eur::ShapeDetection::grey() {
	cv::cvtColor( inFrame, greyFrame, cv::COLOR_BGR2GRAY );
	cv::blur( greyFrame, greyFrame, cv::Size(3,3) );

	return greyFrame;
}


cv::Mat eur::ShapeDetection::canny() {

	cv::Canny(greyFrame, cannyFrame, thresh, thresh * 2);

	return greyFrame;
}



std::vector<std::vector<cv::Point>> eur::ShapeDetection::getPolys() {

	cv::findContours(cannyFrame, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	polys.empty();


	for( size_t i = 0; i < contours.size(); i++ ) {
		polys.push_back(std::vector<cv::Point>(0));
		cv::approxPolyDP( contours[i], polys[i], 7, true );

	}

	return polys;
}



int eur::ShapeDetection::demo() {

	// Create display windows
	cv::namedWindow("Webcam input", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Transformed frame output", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("Canny threshold :", "Contouring output", &thresh, 255);


	// Camera update loop
	std::cout << "Press ESC to exit ..." << std::endl;

	while (1) {
		// Get frame & polys
		getFrame();
		grey();
		canny();
		getPolys();


		// Get bounding rects & radiuses
		boundRect.empty();
		centers.empty();
		radius.empty();

		for( size_t i = 0; i < contours.size(); i++ ) {

			boundRect.push_back(cv::Rect());
			boundRect[i] = cv::boundingRect( polys[i] );

			centers.push_back(cv::Point2f());
			radius.push_back(float());
			cv::minEnclosingCircle(polys[i], centers[i], radius[i]);

		}


		// Draw polys
		cv::RNG rng(12345);

		centers.reserve(contours.size());
		boundRect.reserve(contours.size());
		radius.reserve(contours.size());

		for( size_t i = 0; i< contours.size(); i++ ) {
			cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
			drawContours( inFrame, polys, (int)i, color );
			rectangle( inFrame, boundRect[i].tl(), boundRect[i].br(), color, 2 );
			circle( inFrame, centers[i], (int)radius[i], color, 2 );
		}


		cv::imshow("Webcam input", inFrame);
		cv::imshow("Transformed frame output", greyFrame);

		// Applying byte mask to eliminate useless 1
		int key = cv::waitKey(demoFrameTime) & 0xFF;

		// If key is ESC, exit loop
		if(key == 27)
			break;
	}


	return 0;
}
