#include "cube.h"

Cube::Cube() : Shape(Vector3(0,0,0), Vector3(10,10,10)) {
    updatePoints();
}

Cube::Cube(Vector3 position, Vector3 scale) : Shape(position, scale) {
    updatePoints();
}

void Cube::translate(Vector3 newPosition) {
    this->position = newPosition;

    for (auto& point : points) {
        Vector3 diff = *point - newPosition;

        point->x -= diff.x;
        point->y -= diff.y;
        point->z -= diff.z;
    }
}

void Cube::changeScale(Vector3 newScale) {
    this->scale = newScale;
    
    updatePoints();
}

// void Cube::draw(Framework& fw) {
    
//     // drawing vertices
//     for (auto& p : points)
//         fw.drawPixel(*p, this->color);

//     for (auto& c : connections)
//         fw.drawLine(*c->point1, *c->point2, this->color);
// }


void Cube::updatePoints() {
    float offsetX = scale.x/2;
    float offsetY = scale.y/2;
    float offsetZ = scale.z/2;

    // main vertexes
    points = std::vector<Vector3*> {
        new Vector3(position.x + offsetX, position.y + offsetY, position.z + offsetZ), // front top right       0
        new Vector3(position.x + offsetX, position.y + offsetY, position.z - offsetZ), // back top right        1
        new Vector3(position.x - offsetX, position.y + offsetY, position.z - offsetZ), // back top left         2
        new Vector3(position.x - offsetX, position.y + offsetY, position.z + offsetZ), // front top left        3

        new Vector3(position.x + offsetX, position.y - offsetY, position.z + offsetZ), // front bottom right    4
        new Vector3(position.x + offsetX, position.y - offsetY, position.z - offsetZ), // back bottom right     5
        new Vector3(position.x - offsetX, position.y - offsetY, position.z - offsetZ), // back bottom left      6
        new Vector3(position.x - offsetX, position.y - offsetY, position.z + offsetZ), // front bottom left     7
    };

    quads = std::vector<Quad> {
        Quad(*points[0], *points[1], *points[2], *points[3]), // top face
        //Quad(*points[0], *points[3], *points[4], *points[7]), // front face
        //Quad(*points[0], *points[1], *points[4], *points[5]), // right face
        
        //Quad(*points[4], *points[5], *points[6], *points[7]), // bottom face
        //Quad(*points[1], *points[2], *points[5], *points[6]), // back face
        //Quad(*points[2], *points[3], *points[6], *points[7]), // left face
        
    };
}


std::vector<Quad> Cube::getQuads() {
    return quads;
}
