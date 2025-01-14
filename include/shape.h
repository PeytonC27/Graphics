#pragma once

#include "color.h"
#include <SDL2/SDL.h>

class Shape {
public:
	
	Shape();

	virtual void draw(SDL_Renderer* renderer, Color color) = 0;
};