#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "Color/Color.hpp"
#include "Contouring/Contouring.hpp"


/*****************************************************************************/


int main(int, char**) {

	eur::Color color(101, 125, 89, "Olive Green");
	color.print();


	// Contouring demo
	eur::Contouring contouring;
	contouring.launchDemo();


	return 0;
}
