#pragma once

#include "vector2.h"
#include "shape.h"

class Line : public Shape {
public:
	Vector2 start;
	Vector2 end;
	float thickness;
	Line(Vector2 start, Vector2 end, float thickness = 1);
	Line(Vector2 origin, Vector2 direction, float distance, float thickness = 1);
	
	void draw(SDL_Renderer* renderer, Color color) override;
};