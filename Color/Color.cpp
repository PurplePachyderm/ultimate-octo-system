#include <iostream>
#include <math.h>

#include "Color.hpp"


// Constructor using individual color components
eur::Color::Color(int newR, int newG, int newB, std::string newName) {

	r = newR;
	g = newG;
	b = newB;

	name = newName;
}


// Constructor using hexadecimal color code
eur::Color::Color(unsigned int colorCode, std::string newName) {

	r = (colorCode & 0xFF0000) >> 16;
	g = (colorCode & 0x00FF00) >> 8;
	b = colorCode & 0x0000FF;

	name = newName;
}


void eur::Color::print() {
	std::cout << "Color : " << name << std::endl;
	std::cout << "	R: " << (int) r << std::endl;
	std::cout << "	G: " << (int) g << std::endl;
	std::cout << "	B: " << (int) b << std::endl;
	std::cout << "	Hue: " << getHue() << std::endl;
	std::cout << "	Saturation: " << getSaturation() << std::endl;
	std::cout << "	Value: " << getValue() << std::endl;

	getHue();
	getSaturation();
	getValue();

}



int eur::Color::getHue() {

	// 1) Colors normalization
	float normR = r / 255.0;
	float normG = g / 255.0;
	float normB = b / 255.0;

	// 2) Cmax, Cmin, Delta calculation
	float cMax = std::max(normR, std::max(normG, normB));
	float cMin = std::min(normR, std::min(normG, normB));
	float delta = cMax - cMin;

	// 3) Hue calculation
	int hue;

	if(cMax == normR && delta != 0) {

		// This is needed to avoid negative value when G < B
		float temp = (normG - normB) / delta;
		if(temp < 0) {
			temp += 6.0;
		}

		hue = 60 * ( fmod(temp, 6.0) );
	}

	if(cMax == normG && delta != 0) {
		hue = 60 * ( (normB - normR) / delta + 2 );
	}

	if(cMax == normB && delta != 0) {
		hue = 60 * ( (normR - normG) / delta + 4 );
	}

	if(delta == 0) {
		hue = 0;
	}


	return hue;
}



float eur::Color::getSaturation() {

	// 1) Colors normalization
	float normR = r / 255.0;
	float normG = g / 255.0;
	float normB = b / 255.0;


	// 2) Cmax, Cmin, Delta calculation
	float cMax = std::max(normR, std::max(normG, normB));
	float cMin = std::min(normR, std::min(normG, normB));
	float delta = cMax - cMin;

	// 3) Saturation calculation
	if(cMax == 0) {
		return 0;
	}
	else {
		return delta / cMax;
	}

}



float eur::Color::getValue() {

	// 1) Colors normalization
	float normR = r / 255.0;
	float normG = g / 255.0;
	float normB = b / 255.0;

	// 2) Cmax = value
	return std::max(normR, std::max(normG, normB));

}
