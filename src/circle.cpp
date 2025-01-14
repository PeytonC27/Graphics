#include "circle.h"

#include <cmath>

Circle::Circle(Vector2 center, float radius) : center(center), radius(radius) {

}

void Circle::draw(SDL_Renderer* renderer, Color color) {
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
	for (int x = center.x - radius; x <= center.x + radius; x++) {
        for (int y = center.y - radius; y <= center.y + radius; y++) {
            double inCircle = (std::pow(center.y - y, 2) + std::pow(center.x - x, 2)) <= std::pow(radius, 2);
            if (inCircle) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}