#pragma once

#include "SDL2/SDL.h"
#include "vector3.h"
#include "color.h"
#include "triangle.h"
#include "quad.h"

#include <vector>
#include <unordered_map>
#include <tuple>
#include <list>

// Hash function for unordered_map
struct HashFunction {
    std::size_t operator()(const std::pair<int, int>& coordinate) const {
        return std::hash<int>()(coordinate.first) ^ std::hash<int>()(coordinate.second);
    }
};

struct PixelData {
    Vector3 position;
    Color color = Color(255, 255, 255, 255);
};

class Framework {
public:
    SDL_Renderer* renderer = NULL;
	
    Framework(int height, int width);
    ~Framework();

    void drawPixel(Vector3 coordinate, Color color);
    void drawLine(Vector3 start, Vector3 end, Color color);
    void drawTriangle(Triangle triangle, Color color);
    void drawQuad(Quad quad, Color color);
	
    int saveImage();
    void clear();
    void render(float zFadeLimit, bool flipY = false);

private:
    int height;
    int width;

    std::unordered_map<std::pair<float, float>, PixelData, HashFunction> points;

    SDL_Window* window = NULL; 

    void fillBottomFlatTriangle(Triangle triangle, Color color);
    void fillTopFlatTriangle(Triangle triangle, Color color);
};