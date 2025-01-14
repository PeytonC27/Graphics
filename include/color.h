#pragma once

class Color {
private:
	
public:
	
	int red;
	int green;
	int blue;
	int alpha;

	Color(int red, int green, int blue);
	Color(int red, int green, int blue, int alpha);
	
	void increaseBrightness();
};