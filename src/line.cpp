#include <cmath>
#include "line.h"
#include <SDL2/SDL.h>

Line::Line(Vector2 start, Vector2 end, float thickness) : start(start), end(end), thickness(thickness) {}

Line::Line(Vector2 origin, Vector2 direction, float distance, float thickness) : start(origin), end(start + direction.normalized() * distance), thickness(thickness) {}

void Line::draw(SDL_Renderer* renderer, Color color) {


	// BREHENSEN LINE ALGORITHM
	//if (thickness == 1) {

		// adjust coordinates for the image
		
		int x1 = (int)std::roundf(start.x);
		int x2 = (int)std::roundf(end.x);
		int y1 = (int)std::roundf(start.y);
		int y2 = (int)std::roundf(end.y);
		
		int dx = std::abs(x2 - x1);
		int sx = (x1 < x2) ? 1 : -1;
		int dy = -std::abs(y2 - y1);
		int sy = (y1 < y2) ? 1 : -1;
		int err = dx + dy;
		
		
		SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
		
		while (true) {
			// draw pixel
			//RGB color = getRGB((float)x1 / width);
			
			//SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
			SDL_RenderDrawPoint(renderer, x1, y1);
			
			//std::cout << "Plotted: " << Vector2(x1, y1) << std::endl;
			
			// brensen line alg
			if ((x1 == x2) && (y1 == y2)) break;
			float e2 = err << 1;
			if (e2 >= dy) {
				if (x1 == x2) break;
				err += dy;
				x1 += sx;
			}
			if (e2 <= dx) {
				if (y1 == y2) break;
				err += dx;
				y1 += sy;
			}
		}
}
	// thick line from https://github.com/SFML/SFML/wiki/source:-line-segment-with-thickness
	//else {
		
	//}