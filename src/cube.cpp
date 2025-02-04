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

void Cube::draw(Framework& fw) {
    
    // drawing vertices
    for (auto& p : points)
        fw.drawPixel(*p, this->color);

    for (auto& c : connections)
        fw.drawLine(*c->point1, *c->point2, this->color);
}

void Cube::updatePoints() {
    float offsetX = scale.x/2;
    float offsetY = scale.y/2;
    float offsetZ = scale.z/2;

    // main vertexes
    points = std::vector<Vector3*> {
        new Vector3(position.x + offsetX, position.y + offsetY, position.z + offsetZ),
        new Vector3(position.x + offsetX, position.y + offsetY, position.z - offsetZ),
        new Vector3(position.x - offsetX, position.y + offsetY, position.z - offsetZ),
        new Vector3(position.x - offsetX, position.y + offsetY, position.z + offsetZ),

        new Vector3(position.x + offsetX, position.y - offsetY, position.z + offsetZ),
        new Vector3(position.x + offsetX, position.y - offsetY, position.z - offsetZ),
        new Vector3(position.x - offsetX, position.y - offsetY, position.z - offsetZ),
        new Vector3(position.x - offsetX, position.y - offsetY, position.z + offsetZ),
    };

    connections = std::vector<Connection*> {
        new Connection { points[0], points[1] },
        new Connection { points[1], points[2] },
        new Connection { points[2], points[3] },
        new Connection { points[3], points[0] },
        
        new Connection { points[4], points[5] },
        new Connection { points[5], points[6] },
        new Connection { points[6], points[7] },
        new Connection { points[7], points[4] },

        new Connection { points[0], points[4] },
        new Connection { points[1], points[5] },
        new Connection { points[2], points[6] },
        new Connection { points[3], points[7] }
    };
}