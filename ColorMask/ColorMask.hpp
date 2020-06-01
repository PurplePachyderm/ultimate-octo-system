	// Basic color mask class, with upper and lower eur::Color fields

#pragma once

#include "../Color/Color.hpp"


namespace eur {
	class ColorMask;
}



class eur::ColorMask {
	public:
		// Constructors
		ColorMask(eur::Color lower, eur::Color upper, std::string maskName);
		ColorMask(int lowH, int highH, int lowS, int highS, int lowV, int highV, std::string maskName);


		eur::Color lowerColor, upperColor;
		std::string name;
};
