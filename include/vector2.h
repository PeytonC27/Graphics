#pragma once

#include <iostream>

class Vector2 {
public:
    Vector2(float x, float y);
    Vector2();

    ~Vector2();

    float magnitude();
    float angle();
    Vector2 normalized();
    Vector2 normal();

    Vector2 operator+(const Vector2& other) const;
    Vector2& operator+=(const Vector2& other);
    Vector2 operator-(const Vector2& other) const;
    Vector2& operator-=(const Vector2& other);

    Vector2 operator*(float scalar) const;
    Vector2 operator*=(float scalar);
    Vector2 operator/(float scalar) const;
    Vector2 operator/=(float scalar);

    bool operator<(const Vector2& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);

    float x;
    float y;

    static Vector2 up;
    static Vector2 down;
    static Vector2 left;
    static Vector2 right;

private:


};