#include <iostream>

#include "Color.hpp"


// Constructor using individual color components
eur::Color::Color(int newR, int newG, int newB, std::string newName) {

	r = 256 - (256 - newR);
	g = 256 - (256 - newG);
	b = 256 - (256 - newB);

	std::cout << (int) r << std::endl;
	std::cout << (int) g << std::endl;
	std::cout << (int) b << std::endl;

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
}
