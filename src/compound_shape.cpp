#include "compound_shape.h"

CompoundShape::CompoundShape(std::vector<Shape*> shapes) : Shape(Vector3(0,0,0)) {
    Vector3 centroid;
    int totalPoints = 0;

    for (auto& shape : shapes) {
        totalPoints += shape->points.size();

        // points
        for (auto& point : shape->points) {
            this->points.push_back(point);
            centroid += *point;
        }

        // connections
        for (auto& connection : shape->connections)
            this->connections.push_back(connection);
    }

    this->position = centroid / (totalPoints);
}

void CompoundShape::translate(Vector3 newPosition) {
    this->position = newPosition;

    for (auto& point : points) {
        Vector3 diff = *point - newPosition;

        point->x -= diff.x;
        point->y -= diff.y;
        point->z -= diff.z;
    }
}

void CompoundShape::draw(Framework& fw) {
    // drawing vertices
    for (auto& p : points)
        fw.drawPixel(*p, this->color);

    for (auto& c : connections)
        fw.drawLine(*c->point1, *c->point2, this->color);
}