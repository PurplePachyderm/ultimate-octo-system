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



double eur::ShapeDetection::angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;

	return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}



std::vector<std::vector<cv::Point>> eur::ShapeDetection::getPolys() {

	cv::findContours(cannyFrame, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	polys.clear();


	for( size_t i = 0; i < contours.size(); i++ ) {
		polys.push_back(std::vector<cv::Point>());
		cv::approxPolyDP( contours[i], polys[i], 7, true );
	}

	return polys;
}



std::vector<std::vector<cv::Point>> eur::ShapeDetection::getTriangles() {
	cv::findContours(cannyFrame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<cv::Point> approx;
	polys.clear();

	std::cout << "New iteration: " << std::endl;

	for (int i = 0; i < contours.size(); i++) {

		cv::approxPolyDP( contours[i], approx, 7, true );

		std::cout << "	Poly: " << std::endl;
		std::cout << "		Poly sides: " << approx.size() << std::endl;
		std::cout << "		Poly area: " << cv::contourArea(contours[i]) << std::endl;

		// Skip small or non-convex objects
		if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
			continue;

		if (approx.size() == 3) {
			polys.push_back(approx);
		}

	}

	return polys;
}



std::vector<std::vector<cv::Point>> eur::ShapeDetection::getTrapezes() {
	cv::findContours(cannyFrame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<cv::Point> approx;
	polys.clear();

	std::cout << "New iteration: " << std::endl;

	for (int i = 0; i < contours.size(); i++) {

		cv::approxPolyDP( contours[i], approx, 7, true );

		std::cout << "	Poly: " << std::endl;
		std::cout << "		Poly sides: " << approx.size() << std::endl;
		std::cout << "		Poly area: " << cv::contourArea(contours[i]) << std::endl;

		// Skip small or non-convex objects
		if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
			continue;

		if (approx.size() == 4) {


			// Detect if quadrilateral is a trapeze using angles' cos

			std::vector<double> cos;
			for (int j = 2; j < approx.size()+1; j++)
				cos.push_back(angle(approx[j%approx.size()], approx[j-2], approx[j-1]));

			// Sort ascending the cosine values
			std::sort(cos.begin(), cos.end());

			// Get the lowest and the highest cosine
			double mincos = cos.front();
			double maxcos = cos.back();

			// Criteria for being trapeze
			if (approx.size() == 4 && mincos >= -0.3 && maxcos <= 0.2){
				polys.push_back(approx);
			}

		}

	}

	return polys;
}



std::vector<std::vector<cv::Point>> eur::ShapeDetection::getRectangles() {
	cv::findContours(cannyFrame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<cv::Point> approx;
	polys.clear();

	std::cout << "New iteration: " << std::endl;

	for (int i = 0; i < contours.size(); i++) {

		cv::approxPolyDP( contours[i], approx, 7, true );

		std::cout << "	Poly: " << std::endl;
		std::cout << "		Poly sides: " << approx.size() << std::endl;
		std::cout << "		Poly area: " << cv::contourArea(contours[i]) << std::endl;

		// Skip small or non-convex objects
		if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
			continue;

		if (approx.size() == 4) {


			// Detect if quadrilateral is a rectangle using angles' cos

			std::vector<double> cos;
			for (int j = 2; j < approx.size()+1; j++)
				cos.push_back(angle(approx[j%approx.size()], approx[j-2], approx[j-1]));

			// Sort ascending the cosine values
			std::sort(cos.begin(), cos.end());

			// Get the lowest and the highest cosine
			double mincos = cos.front();
			double maxcos = cos.back();

			// Criteria for being a rectangle
			if (approx.size() == 4 && mincos >= -0.1 && maxcos <= 0.3){
				polys.push_back(approx);
			}

		}

	}

	return polys;
}



int eur::ShapeDetection::demo() {

	// Create display windows
	cv::namedWindow("Webcam input", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Transformed frame output", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("Canny threshold :", "Webcam input", &thresh, 255);


	// Camera update loop
	std::cout << "Press ESC to exit ..." << std::endl;

	while (1) {
		// Get frame & polys
		getFrame();
		grey();
		canny();
		getTrapezes();


		// Get bounding rects & radiuses
		boundRect.clear();
		centers.clear();
		radius.clear();

		for( size_t i = 0; i < polys.size(); i++ ) {

			boundRect.push_back(cv::Rect());
			boundRect[i] = cv::boundingRect( polys[i] );

			centers.push_back(cv::Point2f());
			radius.push_back(float());
			cv::minEnclosingCircle(polys[i], centers[i], radius[i]);

		}


		// Draw polys
		cv::RNG rng(12345);
		outFrame = inFrame.clone();

		centers.reserve(contours.size());
		boundRect.reserve(contours.size());
		radius.reserve(contours.size());

		for( size_t i = 0; i< polys.size(); i++ ) {
			cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
			drawContours( outFrame, polys, (int)i, color );
			rectangle( outFrame, boundRect[i].tl(), boundRect[i].br(), color, 2 );
			circle( outFrame, centers[i], (int)radius[i], color, 2 );
		}


		cv::imshow("Webcam input", outFrame);
		cv::imshow("Transformed frame output", cannyFrame);

		// Applying byte mask to eliminate useless 1
		int key = cv::waitKey(demoFrameTime) & 0xFF;

		// If key is ESC, exit loop
		if(key == 27)
			break;
	}


	return 0;
}
