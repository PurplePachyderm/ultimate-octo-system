	// Basic color class

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
};
