#include "pyramid.h"

Pyramid::Pyramid(Vector3 position, float radius) : Shape(position), radius(radius) {

    //float baseOffset = std::sqrt(2.0f/3.0f) * radius;
    //float baseYPos = position.y - radius / 3.0f;

    // main vertexes
    // points = std::vector<Vector3> {
    //     Vector3(position.x, position.y + radius, position.z), // apex

    //     Vector3(position.x + baseOffset * std::cos(1 * M_PI / 6), baseYPos, position.z + baseOffset * std::sin(1 * M_PI / 6)),
    //     Vector3(position.x + baseOffset * std::cos(5 * M_PI / 6), baseYPos, position.z + baseOffset * std::sin(5 * M_PI / 6)),
    //     Vector3(position.x + baseOffset * std::cos(9 * M_PI / 6), baseYPos, position.z + baseOffset * std::sin(9 * M_PI / 6))
    // };

    Vector3 centroid;
    for (auto& p : points) {
        //centroid += p;
        std::cout << "Point: " << p << std::endl;
    }

    std::cout << "Centroid: " << centroid/points.size() << std::endl;
}

void Pyramid::translate(Vector3 newPosition) {
    this->position = newPosition;

    
    //float baseOffset = std::sqrt(2.0f/3) * radius;
    //float baseYPos = position.y - radius / 3;

    // points = std::vector<Vector3> {
    //     Vector3(position.x, position.y + radius, position.z), // apex

    //     Vector3(position.x + baseOffset * std::cos(1 * M_PI / 6), baseYPos, position.z + baseOffset * std::sin(1 * M_PI / 6)),
    //     Vector3(position.x + baseOffset * std::cos(5 * M_PI / 6), baseYPos, position.z + baseOffset * std::sin(5 * M_PI / 6)),
    //     Vector3(position.x + baseOffset * std::cos(9 * M_PI / 6), baseYPos, position.z + baseOffset * std::sin(9 * M_PI / 6))
    // };
}

void Pyramid::draw(Framework& fw) {
    // drawing vertices
    // for (auto& p : points)
    //     fw.drawPixel(p);

    // // apex to other points
    // fw.drawLine(points[0], points[1]);
    // fw.drawLine(points[0], points[2]);
    // fw.drawLine(points[0], points[3]);

    // // triangle at bottom
    // fw.drawLine(points[1], points[2]);
    // fw.drawLine(points[2], points[3]);
    // fw.drawLine(points[3], points[1]);
}