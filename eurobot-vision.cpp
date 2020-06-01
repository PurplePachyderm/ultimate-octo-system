#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "Color/Color.hpp"
#include "Contouring/Contouring.hpp"
#include "ColorTracking/ColorTracking.hpp"


/*****************************************************************************/


int main(int, char**) {


	// Contouring demo
	// eur::Contouring contouring;
	// contouring.launchDemo();



	// Color tracking demo
	std::vector<eur::Color> colors {
		eur::Color(80, 15, 40, "Rubik's red"),
		eur::Color(0, 40, 40, "Rubik's green"),
		eur::Color(10, 40, 150, "Rubik's blue"),
		eur::Color(100, 110, 80, "Rubik's yellow"),
		eur::Color(100, 60, 40, "Rubik's orange"),
		eur::Color(95, 110, 140, "Rubik's white"),
	};

	for(unsigned int i=0; i<colors.size(); i++) {
		colors[i].print();
	}

	eur::ColorTracking colorTracking;
	colorTracking.colors = colors;
	colorTracking.launchDemo();


	return 0;
}
