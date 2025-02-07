#pragma once

#include "shape.h"

class Quad : public Shape {
public:
    Vector3 v1, v2, v3, v4;

    Quad(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4);

    void translate(Vector3 newPosition) override;
    void changeScale(Vector3 newScale) override;
    void updatePoints() override;

private:
};