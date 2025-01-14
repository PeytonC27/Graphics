#pragma once

#include "SDL2/SDL.h"
#include "vector2.h"
#include "color.h"
#include "shape.h"
#include <vector>

class Framework {
public:
    SDL_Renderer* renderer = NULL;
	
    Framework(int height, int width);
    ~Framework();

    void drawPixel(Vector2 coordinate, Color color);
    void drawLine(Vector2 origin, Vector2 destination, Color color);
    void drawLine(Vector2 origin, Vector2 direction, float distance);
	void drawCircle(Vector2 center, float radius, Color color);
	
    int saveImage();
    void clear();
    void render();

private:
    int height;
    int width;
	std::vector<Shape*> shapes;
    SDL_Window* window = NULL; 
};