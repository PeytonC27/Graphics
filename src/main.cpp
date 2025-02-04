#include "vector3.h"
#include "framework.h"
#include "color.h"
#include "gradient.h"
#include "SDL2/SDL.h"
#include "cube.h"
#include "compound_shape.h"
#include "rammble_parser.h"

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

using DisplayFunction = std::function<void()>;

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";  // String is all whitespace

    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;

    std::string sbuffer;
    for (char c : str) {
        if (c == delimiter) {
            tokens.push_back(trim(sbuffer));
            sbuffer.clear();
        }
        else {
            sbuffer.push_back(c);
        }
    }  

    return tokens;
}

std::vector<Shape*> parseDisplayCode(const std::string& code) {
    std::unordered_map<std::string, Shape*> shapes;

    std::vector<std::string> lines = split(code, ';');
    
    return interpretRammbleCode(lines);
}

// taken from https://dev.devbf.com/posts/how-to-read-a-whole-file-into-a-stdstring-in-c-c94d9/
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string contents;

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }

    // Get the file's size
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Reserve memory for the string to avoid multiple reallocations
    contents.reserve(fileSize);

    // Read the file's contents into the string
    contents.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    // Close the file
    file.close();

    return contents;
}


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

    std::vector<Shape*> myShapes = parseDisplayCode(readFile("setup.ram"));
	
    //auto points = cube(Vector3(250, 250, -50), 100);

    // calculating centroid
    // Vector3 centroid;
    // for (auto& p : points) {
    //     centroid.x += p.x;
    //     centroid.y += p.y;
    //     centroid.z += p.z;
    // }
    // centroid /= points.size();

    // main loop
    while (!(event.type == SDL_QUIT)) {
        fw.clear();

        // for (auto& p : points) {
        //     p -= centroid;
        //     rotate(p, 0.005, 0.005, 0.005);
        //     p += centroid;
        // }

        // for (auto& p : points) {
            
        //     fw.drawPixel(p);
        // }

        //myShape.translate(Vector3(myShape.position.x + 0.005, myShape.position.y, myShape.position.z));

        // if (event.type = SDL_PRESSED) {
        //     if (event.key.keysym.sym == SDLK_w)
        //         myShape.rotate(0.05, 0, 0);
        //     if (event.key.keysym.sym == SDLK_s)
        //         myShape.rotate(-0.05, 0, 0);
        //     if (event.key.keysym.sym == SDLK_a)
        //         myShape.rotate(0, 0.05, 0);
        //     if (event.key.keysym.sym == SDLK_d)
        //         myShape.rotate(0, -0.05, 0);
        // }


        //frames.push_front(fw.captureFrame());
        for (const auto& shape : myShapes) {
            //shape->setRotation(Vector3(45, 45, 45));
            shape->rotate(Vector3(0, 1, 0));
            shape->draw(fw);
        }

        fw.render(50, true);

        SDL_Delay(msPerFrame);          // setting a delay

        SDL_PollEvent(&event);          // catching event
    }


    std::cout << "done" << std::endl;

    return 0;
}

