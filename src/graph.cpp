#include <graph.h>

Graph::Graph() : fw(700, 700) {
    width = 700;
    height = 700;
}

void Graph::setXRange(float maxX) {
    this->minX = 0;
    this->maxX = maxX;
}

void Graph::setXRange(float minX, float maxX) {
    this->minX = minX;
    this->maxX = maxX;
}


void Graph::setYRange(float maxY) {
    this->minY = 0;
    this->maxY = maxY;
}

void Graph::setYRange(float minY, float maxY) {
    this->minY = minY;
    this->maxY = maxY;
}


void Graph::addFunction(std::function<float(float)> func, Color color) {
    this->functions.push_back(Function { func, color });
}

void Graph::display() {
    fw.clear();

    int xOffset = 100;
    int yOffset = 100;

    // drawing axises
    fw.drawLine(Vector2(100, 100), Vector2(600, 100), Color(255, 255, 255));
    fw.drawLine(Vector2(100, 100), Vector2(100, 600), Color(255, 255, 255));

    float scalingForX = (width - xOffset * 2) / (maxX - minX);
    float scalingForY = (height - yOffset * 2) / (maxY - minY);
    float stepLength = (maxX - minX) / 500;

    // drawing each function
    float x, y, xDisplayCoord, yDisplayCoord;
    bool start;
    for (Function function : this->functions) {
        float at = minX;
        start = true;
        Vector2 oldPoint, newPoint;

        while (at <= maxX) {
            x = at;
            y = function.func(at);

            xDisplayCoord = x * scalingForX + xOffset;
            yDisplayCoord = y * scalingForY + yOffset;

            if (start) {
                oldPoint = Vector2(xDisplayCoord, yDisplayCoord);
                start = false;
            }
            else {
                newPoint = Vector2(xDisplayCoord, yDisplayCoord);
                fw.drawLine(oldPoint, newPoint, function.color);
                oldPoint = newPoint;
            }
            
            at += stepLength;
        }
    }

    fw.render();
    fw.saveImage();
}