	// Basic color class
	// Provides an inteface to create RGB colors and get HSV attributes

	// RGB components range: 0 to 255
	// Hue range: 0 to 360
	// Saturation range: 0 to 1
	// Value range: 0 to 1
	// OpenCV uses the following HSV ranges:
	// 	Hue: 0-180
	// 	Saturation: 0-255
	// 	Value: 0-255


#pragma once



namespace eur {
	class Color;
}


class eur::Color {
	public:
		// Constructors
		Color();
		Color(int newR, int newG, int newB, std::string newName);
		Color(unsigned int colorCode, std::string newName);
		Color(int hue, float saturation, float value, std::string newName);

		void print();

		unsigned char r, g, b;
		std::string name;

		int getHue();
		float getSaturation();
		float getValue();

		int getCvHue();
		int getCvSaturation();
		int getCvValue();
};
