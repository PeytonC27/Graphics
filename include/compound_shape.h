#pragma once

#include "shape.h"

class CompoundShape : public Shape {
public:
    CompoundShape(std::vector<Shape*> shapes);

    void translate(Vector3 newPosition) override;
};