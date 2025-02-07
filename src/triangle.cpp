#include <triangle.h>

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3): Shape(Vector3((v1.x+v2.x+v3.x)/3, (v1.y+v2.y+v3.y)/3, (v1.z+v2.z+v3.z)/3), Vector3(1,1,1)), v1(v1), v2(v2), v3(v3) {
    updatePoints();
}

void Triangle::translate(Vector3 newPosition) {
    this->position = newPosition;

    Vector3 diff = position - newPosition;

    this->v1 += diff;
    this->v2 += diff;
    this->v3 += diff;
}

void Triangle::changeScale(Vector3 newScale) {
    this->scale = newScale;
    
    updatePoints();
}

void Triangle::updatePoints() {
    
}
