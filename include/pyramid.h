#pragma once

#include "shape.h"

class Pyramid : public Shape {
public:
    Pyramid(Vector3 position, float radius);

    void draw(Framework& fw) override;
    void translate(Vector3 newPosition) override;

private:
    float radius;
};