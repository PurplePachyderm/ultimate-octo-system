#include <iostream>
#include <math.h>

#include "ColorMask.hpp"
#include "../Color/Color.hpp"


eur::ColorMask::ColorMask(eur::Color lower, eur::Color upper, std::string maskName) {
	// Simple constructors,  directly initializing fields

	lowerColor = lower;
	upperColor = upper;
	name = maskName;
}



eur::ColorMask::ColorMask(int lowH, int highH, int lowS, int highS, int lowV, int highV, std::string maskName) {
	// Constructors accepts OpenCV values for HSV bounds, and recalculates color fields

	// OpenCV uses the following HSV ranges:
	// Hue: 0-180
	// Saturation: 0-255
	// Value: 0-255


	// 0) Adjust OpenCV bounds to match classic norms

	int adjustedLowH = 2 * lowH;
	int adjustedHighH = 2 * highH;

	float adjustedLowS =  (float) lowS  / 255.0;
	float adjustedHighS =  (float) highS  / 255.0;

	float adjustedLowV =  (float) lowV  / 255.0;
	float adjustedHighV =  (float) highV  / 255.0;


	lowerColor = eur::Color(adjustedLowH, adjustedLowS, adjustedLowV, "Lower " + maskName);
	upperColor = eur::Color(adjustedHighH, adjustedHighS, adjustedHighV, "Lower " + maskName);


	name = maskName;

}
