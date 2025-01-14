#pragma once

#include <framework.h>
#include <color.h>
#include <functional>
#include <vector>

struct Function {
    std::function<float(float)> func;
    Color color;
};

class Graph {
public:
    Graph();

    void setXRange(float maxX);
    void setXRange(float minX, float maxX);

    void setYRange(float maxY);
    void setYRange(float minY, float maxY);

    void addFunction(std::function<float(float)> func, Color color = Color(255, 255, 255));
    void display();

private:
    Framework fw;
    std::vector<Function> functions;

    bool connectDots;
    float minX = 0, maxX = 500;
    float minY = 0, maxY = 500;

    int width, height;
};