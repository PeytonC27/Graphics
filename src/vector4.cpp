#include "vector4.h"

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector3 Vector4::toVector3() const {
    return Vector3(x/w, y/w, z/w);
}