#pragma once

#include "shape.h"
#include "quad.h"

class Cube : public Shape {
public:
    Cube();
    Cube(Vector3 position, Vector3 scale = Vector3(1,1,1));

    void translate(Vector3 newPosition) override;
    void changeScale(Vector3 newScale) override;
    void updatePoints() override;

    std::vector<Quad> getQuads();

private:
    
    std::vector<Quad> quads;
};