#include "gradient.h"

Gradient::Gradient(Color start, Color end) : start(start), end(end) {}

Color Gradient::at(float ratio) {
	return Color(
			start.red + (end.red - start.red) * ratio,
			start.green + (end.green - start.green) * ratio,
			start.blue + (end.blue - start.blue) * ratio,
			start.alpha + (end.alpha - start.alpha) * ratio
		);
}