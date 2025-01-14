#pragma once

#include "vector2.h"
#include "shape.h"

class Circle : public Shape {
public:
	Vector2 center;
	float radius;

	Circle(Vector2 center, float radius);
	
	void draw(SDL_Renderer* renderer, Color color) override;

};