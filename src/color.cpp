#include "color.h"


Color::Color(int red, int green, int blue) : red(red), green(green), blue(blue), alpha(255) {}

Color::Color(int red, int green, int blue, int alpha) : red(red), green(green), blue(blue), alpha(alpha) {}
	
void Color::increaseBrightness(int amount) {
	this->red += amount;
	this->blue += amount;
	this->green += amount;
}