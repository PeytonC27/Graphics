#include "framework.h"
#include "line.h"
#include "circle.h"
#include "SDL2/SDL_image.h"
#include <cmath>

struct RGB {
	int r;
	int g;
	int b;
};

Vector2 fixPosition(Vector2 pos, int height) {
	return Vector2(pos.x, -(pos.y - height));
}

Framework::Framework(int height, int width) : height(height), width(width) {
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL as video
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);   // setting draw color
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);                      // clear new window
    SDL_RenderPresent(renderer);                    // reflects changes done in window
}

Framework::~Framework() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Framework::drawPixel(Vector2 coordinate, Color color) {
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
    coordinate = fixPosition(coordinate, height);
    SDL_RenderDrawPoint(renderer, coordinate.x, coordinate.y);
}

// This now uses the Bresenham Line Algorithm
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void Framework::drawLine(Vector2 origin, Vector2 destination, Color color) {
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);

	origin = fixPosition(origin, height);
	destination = fixPosition(destination, height);
	Line* l = new Line(origin, destination);
	shapes.push_back(l);

    l->draw(renderer, color);
}


void Framework::drawCircle(Vector2 center, float radius, Color color) {
	center = fixPosition(center, height);
	
	Circle* c = new Circle(center, radius);
	shapes.push_back(c);

    c->draw(renderer, color);
}

void Framework::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void Framework::render() {
	//Color color = Color(255, 255, 255);
	//for (const auto& shape : shapes) {
	//	shape->draw(renderer, color);
	//}
	
    SDL_RenderPresent(renderer);                    // reflects changes done in window
}

int Framework::saveImage() {// Create an SDL_Surface to store the renderer's pixel data
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(
        0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

    if (!surface) {
        std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Read pixel data from the renderer into the surface
    if (SDL_RenderReadPixels(renderer, nullptr, surface->format->format, surface->pixels, surface->pitch) != 0) {
        std::cerr << "Failed to read pixels: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return -1;
    }

    // Save the surface to a PNG file
    int result = IMG_SavePNG(surface, "a.png");
    if (result != 0) {
        std::cerr << "Failed to save image: " << IMG_GetError() << std::endl;
    }

    // Clean up
    SDL_FreeSurface(surface);
    return result;
}