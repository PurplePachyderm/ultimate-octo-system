	// Basic color class
	// Provides an inteface to create RGB colors and get HSV attributes

	// RGB components range: 0 to 255
	// Hue range: 0 to 360
	// Saturation range: 0 to 1
	// Value range: 0 to 1


#pragma once


namespace eur {
	class Color;
}


class eur::Color {
	public:
		//Constructors
		Color(int newR, int newG, int newB, std::string newName);
		Color(unsigned int colorCode, std::string newName);

		void print();

		unsigned char r, g, b;
		std::string name;

		int getHue();
		float getSaturation();
		float getValue();
};
