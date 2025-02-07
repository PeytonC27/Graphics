#pragma once

#include "vector3.h"

class Vector4 {
public:
    float x, y, z, w;

    Vector4(float x, float y, float z, float w);

    Vector3 toVector3() const;
};