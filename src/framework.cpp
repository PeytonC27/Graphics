#include "framework.h"
#include "SDL2/SDL_image.h"
#include "color.h"
#include "triangle.h"
#include "vector4.h"

#include <cmath>
#include <algorithm>

struct RGB {
	int r;
	int g;
	int b;
};


float FOV = 90.0f;
float aspectRatio = 1;
float near = 0.1f, far = 100.0f;

Vector3 project(Vector3 point) {
    float fovFactor = 1.0f / std::tan((FOV * 0.5f) * (M_PI / 180.0f));  // Convert FOV to radians

    float w = point.z * fovFactor;
    if (w == 0) w = 0.0001f;  // Prevent division by zero

    float x_proj = (point.x / w) * aspectRatio;  // Scale to screen size
    float y_proj = (point.y / w);                // Scale to screen size
    float z_proj = (point.z - near) / (far - near);    // Normalize depth

    return Vector3(x_proj + 250, 250 - y_proj, z_proj);  // Center on screen
}


Vector3 fixPosition(Vector3 pos, int height) {
	return Vector3(pos.x, -(pos.y - height), pos.z);
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

    //if (coordinate.x == 200)
    //    std::cout << coordinate << std::endl;

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

void Framework::drawQuad(Quad quad, Color color) {
    color.increaseBrightness(10);
    drawTriangle(Triangle(quad.v1, quad.v2, quad.v3), color);
    color.increaseBrightness(-20);
    drawTriangle(Triangle(quad.v1, quad.v3, quad.v4), color);
}

void Framework::drawTriangle(Triangle triangle, Color color) {
    
    std::cout << "Before Projection:" << std::endl;
    std::cout << triangle.v1 << std::endl;
    std::cout << triangle.v2 << std::endl;
    std::cout << triangle.v3 << std::endl;

    // sort and project each vertex
    std::vector<Vector3> vertices = {
        project(triangle.v1),
        project(triangle.v2),
        project(triangle.v3)
    };
    
    std::cout << "After Projection:" << std::endl;
    std::cout << vertices[0] << std::endl;
    std::cout << vertices[1] << std::endl;
    std::cout << vertices[2] << std::endl;

    std::sort(vertices.begin(), vertices.end(), [](const Vector3& a, const Vector3& b) {
        return a.y < b.y; // Sort in ascending order
    });
    Triangle sortedTriangle = Triangle(vertices[0], vertices[1], vertices[2]);


    std::cout << std::endl;


    Vector3 a = sortedTriangle.v1;
    Vector3 b = sortedTriangle.v2;
    Vector3 c = sortedTriangle.v3;

    if (std::round(b.y) == std::round(c.y))  {
        fillBottomFlatTriangle(sortedTriangle, color);
    }
    else if (std::round(a.y) == std::round(b.y)) {
        fillTopFlatTriangle(sortedTriangle, color);
    }
    else {
        float ratio = (c.y - a.y) != 0 ? (b.y - a.y) / (c.y - a.y) : 0;
        Vector3 v4 = Vector3(a.x + ratio * (c.x - a.x), b.y, 0);

        fillBottomFlatTriangle(Triangle(a, b, v4), color);
        fillTopFlatTriangle(Triangle(b, v4, c), color);
    }
}


void Framework::fillBottomFlatTriangle(Triangle triangle, Color color) {
    Vector3 a = triangle.v1;
    Vector3 b = triangle.v2;
    Vector3 c = triangle.v3;

    float dy1 = b.y - a.y;
    float dy2 = c.y - a.y;

    float invslope1 = dy1 != 0 ? (b.x - a.x) / dy1 : 0;
    float invslope2 = dy2 != 0 ? (c.x - a.x) / dy2 : 0;

    float curx1 = a.x;
    float curx2 = a.x;

    for (int scanlineY = a.y; scanlineY <= b.y; scanlineY++)
    {
        drawLine(Vector3((int)curx1, scanlineY, 0), Vector3((int)curx2, scanlineY, 0), color);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void Framework::fillTopFlatTriangle(Triangle triangle, Color color) {
    Vector3 a = triangle.v1;
    Vector3 b = triangle.v2;
    Vector3 c = triangle.v3;

    float dy1 = c.y - a.y;
    float dy2 = c.y - b.y;

    float invslope1 = dy1 != 0 ? (c.x - a.x) / dy1 : 0;
    float invslope2 = dy2 != 0 ? (c.x - b.x) / dy2 : 0;

    float curx1 = c.x;
    float curx2 = c.x;


    for (int scanlineY = c.y; scanlineY >= a.y; scanlineY--)
    {
        this->drawLine(Vector3(curx1, scanlineY, 0), Vector3(curx2, scanlineY, 0), color);
        curx1 -= invslope1;
        curx2 -= invslope2;
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