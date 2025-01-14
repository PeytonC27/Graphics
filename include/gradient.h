#pragma once

#include "color.h"

class Gradient {

public:
	Gradient(Color start, Color end);
	
	Color at(float ratio);

private:

	Color start;
	Color end;
};