#pragma once

#include "vector3.h"
#include <vector>
#include "framework.h"
#include <cmath>

struct Connection {
    Vector3* point1;
    Vector3* point2;
};

class Shape {
public:
    Shape(Vector3 position, Vector3 scale = Vector3(1,1,1));

    /// @brief Rotates the shape to a new rotation vector (in degrees)
    /// @param newRotation the new rotation
    /// @param updateRotationIdentity whether the base rotation of the object should change to this new vector
    void setRotation(Vector3 newRotation, bool updateRotationIdentity = false);

    /// @brief Rotaes the shape (adds to its current rotation)
    /// @param rotation the amount to rotate
    void rotate(Vector3 rotationAmt);

    /// @brief Draws the shape
    /// @param fw the framework to draw with
    virtual void draw(Framework& fw) = 0;

    /// @brief Trenslates the shape to a new location
    /// @param newPosition the new position of the shape
    virtual void translate(Vector3 newPosition) = 0;

    /// @brief Changes the scale of the shape
    /// @param newScale the new scaling of the shape
    virtual void changeScale(Vector3 newScale) = 0;


    /// @brief Updates every point of this shape (important for scaling, rotating, and translating)
    virtual void updatePoints() = 0;

    Vector3 position;
    std::vector<Vector3*> points;
    std::vector<Connection*> connections;
    Vector3 scale;
    Vector3 rotation;
protected:
    Vector3 rotationIdentity;
};