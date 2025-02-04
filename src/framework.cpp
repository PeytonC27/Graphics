#include "framework.h"
#include "SDL2/SDL_image.h"
#include "color.h"

#include <cmath>

struct RGB {
	int r;
	int g;
	int b;
};


Vector3 fixPosition(Vector3 pos, int height) {
	return Vector3(pos.x, -(pos.y - height));
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

void Framework::drawPixel(Vector3 coordinate, Color color) {

	auto key = std::make_pair(coordinate.x, coordinate.y);
	
	auto it = points.find(key);
	if (it != points.end())
		if (it->second.position.z >= coordinate.z) return;

	points[key] = PixelData {coordinate, color};
}


void Framework::drawLine(Vector3 start, Vector3 end, Color color) {
    Vector3 difference = end - start;

    Vector3 direction = difference.normalized();
    float distance = difference.magnitude();

    Vector3 increment = difference / distance;
    float x = start.x, y = start.y, z = start.z;

    for (float i = 0; i < distance; i++) {
        drawPixel(
            Vector3(std::round(x), std::round(y), std::round(z)), color
        );
        x += increment.x;
        y += increment.y;
        z += increment.z;
    }
}


void Framework::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
	
	points.clear();
}

void Framework::render(float zFadeLimit, bool flipY) {

	for (auto& p : points) {
		Vector3 point = p.second.position;
        Color color = p.second.color;

		float alpha = point.z < 0 ? std::max((zFadeLimit + point.z) / zFadeLimit * color.alpha, 0.0f) : color.alpha; 
        float y = flipY ? -(point.y - height) : point.y;

		SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, alpha);
		SDL_RenderDrawPointF(renderer, point.x, y);
		//std::cout << point << std::endl;
	}

    //for (auto& p : points)
    //    std::cout << p.second << std::endl;
    //std::cout << "--------------------" << std::endl;
	
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