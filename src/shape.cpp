#include "shape.h"
#include <cmath>

#define PI 3.1415926535


Shape::Shape() : position(Vector3(0,0,0)), scale(Vector3(1,1,1)) {}

Shape::Shape(Vector3 position, Vector3 scale) : position(position), scale(scale) {

}

void Shape::setRotation(Vector3 newRotation, bool updateRotationIdentity) {
    this->rotation = newRotation - this->rotation;

    // get centroid
    Vector3 centroid;
    for (auto& p : points)
        centroid += *p;
    centroid /= points.size();

    for (auto& point : points) {
        point->x -= centroid.x;
        point->y -= centroid.y;
        point->z -= centroid.z;

        Vector3 originalPoint(point->x, point->y, point->z);

        float radians = 0;

        // rerotate
        radians = rotation.x * PI / 180;
        point->y = std::cos(radians) * originalPoint.y - std::sin(radians) * originalPoint.z;
        point->z = std::sin(radians) * originalPoint.y + std::cos(radians) * originalPoint.z;
        originalPoint = *point;

        radians = rotation.y * PI / 180;
        point->x = std::cos(radians) * originalPoint.x + std::sin(radians) * originalPoint.z;
        point->z = -std::sin(radians) * originalPoint.x + std::cos(radians) * originalPoint.z;
        originalPoint = *point;

        radians = rotation.z * PI / 180;
        point->x = std::cos(radians) * originalPoint.x - std::sin(radians) * originalPoint.y;
        point->y = std::sin(radians) * originalPoint.x + std::cos(radians) * originalPoint.y;
        originalPoint = *point;

        point->x += centroid.x;
        point->y += centroid.y;
        point->z += centroid.z;
    }

    if (updateRotationIdentity)
        this->rotationIdentity = this->rotation;
}

void Shape::rotate(Vector3 rotationAmt) {
    this->rotation = rotationAmt;

    // get centroid
    Vector3 centroid;
    for (auto& p : points)
        centroid += *p;
    centroid /= points.size();

    for (auto& point : points) {
        point->x -= centroid.x;
        point->y -= centroid.y;
        point->z -= centroid.z;

        Vector3 originalPoint(point->x, point->y, point->z);

        float radians = 0;

        // rerotate
        radians = rotation.x * PI / 180;
        point->y = std::cos(radians) * originalPoint.y - std::sin(radians) * originalPoint.z;
        point->z = std::sin(radians) * originalPoint.y + std::cos(radians) * originalPoint.z;
        originalPoint = *point;

        radians = rotation.y * PI / 180;
        point->x = std::cos(radians) * originalPoint.x + std::sin(radians) * originalPoint.z;
        point->z = -std::sin(radians) * originalPoint.x + std::cos(radians) * originalPoint.z;
        originalPoint = *point;

        radians = rotation.z * PI / 180;
        point->x = std::cos(radians) * originalPoint.x - std::sin(radians) * originalPoint.y;
        point->y = std::sin(radians) * originalPoint.x + std::cos(radians) * originalPoint.y;
        originalPoint = *point;

        point->x += centroid.x;
        point->y += centroid.y;
        point->z += centroid.z;
    }
}


void Shape::setColor(Color color) {
    this->color = color;
}