#include <quad.h>

Quad::Quad(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4): Shape(Vector3((v1.x+v2.x+v3.x+v4.x)/4, (v1.y+v2.y+v3.y+v4.y)/4, (v1.z+v2.z+v3.z+v4.z)/4), Vector3(1,1,1)), v1(v1), v2(v2), v3(v3), v4(v4) {
    updatePoints();
}

void Quad::translate(Vector3 newPosition) {

    Vector3 diff = position - newPosition;

    this->v1 += diff;
    this->v2 += diff;
    this->v3 += diff;
    this->v4 += diff;
    this->position = newPosition;

    std::cout << position << std::endl;
}

void Quad::changeScale(Vector3 newScale) {
    this->scale = newScale;
    
    updatePoints();
}

void Quad::updatePoints() {

}
