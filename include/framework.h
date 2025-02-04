#pragma once

#include "SDL2/SDL.h"
#include "vector3.h"
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

struct Frame {
    std::unordered_map<std::pair<float, float>, Vector3, HashFunction> points;
    int lifespan = 0;
};

class Framework {
public:
    SDL_Renderer* renderer = NULL;
	
    Framework(int height, int width);
    ~Framework();

    void drawPixel(Vector3 coordinate);
    void drawLine(Vector3 start, Vector3 end);
	
    int saveImage();
    void clear();
    void render(float zFadeLimit, bool flipY = false);
    void renderFrame(Frame frame, float zFadeLimit, bool flipY = false);
    void renderDelayedFrames(std::list<Frame> frames, float zFadeLimit, bool flipY = false);

    Frame captureFrame();

private:
    int height;
    int width;

    std::unordered_map<std::pair<float, float>, Vector3, HashFunction> points;

    SDL_Window* window = NULL; 
};