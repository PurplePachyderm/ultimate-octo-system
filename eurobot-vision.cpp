#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "Contouring/Contouring.hpp"


/*****************************************************************************/


int main(int, char**) {

	eur::Color color(0xFFA042, "Red");
	color.print();

	// Contouring demo
	eur::Contouring contouring;
	contouring.launchCannyDemo();


	return 0;
}
