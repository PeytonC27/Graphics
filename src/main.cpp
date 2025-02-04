#include "vector3.h"
#include "framework.h"
#include "color.h"
#include "gradient.h"
#include "SDL2/SDL.h"
#include "cube.h"
#include "compound_shape.h"

#include <iostream>
#include <cmath>
#include <list>
#include <random>
#include <set>
#include <ctime>
#include <algorithm>
#include <functional>
#include <sstream>
#include <fstream>

int main(int argc, char* argv[]) {
    int fps = 60;
    double msPerFrame = (1000.0/fps);
    //double delta = 1.0/fps;

    int height = 500;
    int width = 500;
	

    Framework fw(height, width);
	SDL_Event event;
    //const Uint8* state = SDL_GetKeyboardState(nullptr);

    //Cube c(Vector3(250, 250, -50), 100);

    std::vector<Shape*> myShapes;
    myShapes.push_back(new Cube(Vector3(250, 250, 0), Vector3(100, 10, 100)));
    myShapes[0]->setColor(Color(122, 122, 255, 255));

    // main loop
    while (!(event.type == SDL_QUIT)) {
        fw.clear();


        for (const auto& shape : myShapes) {
            shape->rotate(Vector3(0.5, 0.5, 0.5));
            shape->draw(fw);
        }

        fw.render(100, true);

        SDL_Delay(msPerFrame);          // setting a delay
        SDL_PollEvent(&event);          // catching event
    }


    std::cout << "done" << std::endl;

    return 0;
}

