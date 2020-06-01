#include <iostream>
#include <math.h>

#include "Color.hpp"


// Override default constructor
eur::Color::Color() {

}



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


// Constructor using HSV values (normal ranges)
eur::Color::Color(int hue, float saturation, float value, std::string newName) {


	// 0) Chroma, Hprime, X, m
	float chroma = value * saturation;
	float hPrime = (float) hue / 60.0;
	float x = chroma * (1 - std::abs( std::fmod(hPrime, 2.0) - 1));
	float m = value - chroma;



	// 2) R1, G1, B1
	float r1, g1, b1;
	if(0 <= hPrime && hPrime <= 1) {
		r1 = chroma;
		g1 = x;
		b1 = 0;
	}
	if(1 < hPrime && hPrime <= 2) {
		r1 = x;
		g1 = chroma;
		b1 = 0;
	}
	if(2 < hPrime && hPrime <= 3) {
		r1 = 0;
		g1 = chroma;
		b1 = x;
	}
	if(3 < hPrime && hPrime <= 4) {
		r1 = 0;
		g1 = x;
		b1 = chroma;
	}
	if(4 < hPrime && hPrime <= 5) {
		r1 = x;
		g1 = 0;
		b1 = chroma;
	}
	if(5 < hPrime && hPrime <= 6) {
		r1 = chroma;
		g1 = 0;
		b1 = x;
	}

	r = (unsigned int) (255.0 * (r1 + m));
	g = (unsigned int) (255.0 * (g1 + m));
	b = (unsigned int) (255.0 * (b1 + m));


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

	// 0) Invert R and B (OpenCV uses BGR instead of RGB)
	// float temp = r;
	// r = b;
	// b = temp;

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

	// 0) Invert R and B (OpenCV uses BGR instead of RGB)
	// float temp = r;
	// r = b;
	// b = temp;

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

	// 0) Invert R and B (OpenCV uses BGR instead of RGB)
	// float temp = r;
	// r = b;
	// b = temp;

	// 1) Colors normalization
	float normR = r / 255.0;
	float normG = g / 255.0;
	float normB = b / 255.0;

	// 2) Cmax = value
	return std::max(normR, std::max(normG, normB));

}


int eur::Color::getCvHue() {
	int hue = getHue();
	return hue / 2;
}



int eur::Color::getCvSaturation() {
	float saturation = getSaturation();
	return (int) (255.0 * saturation);
}



int eur::Color::getCvValue() {
	float value = getValue();
	return (int) (255.0 * value);
}
