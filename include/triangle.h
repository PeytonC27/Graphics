#pragma once

#include "shape.h"

class Triangle : public Shape {
public:
    Vector3 v1, v2, v3;

    Triangle(Vector3 v1, Vector3 v2, Vector3 v3);

    void translate(Vector3 newPosition) override;
    void changeScale(Vector3 newScale) override;
    void updatePoints() override;

private:
    

};