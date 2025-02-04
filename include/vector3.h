#pragma once

#include <iostream>

class Vector3 {
public:
    Vector3(float x, float y, float z = 0);

    Vector3();

    ~Vector3();

    float magnitude();
    float angle();
    Vector3 normalized();

    Vector3 operator+(const Vector3& other) const;
    Vector3& operator+=(const Vector3& other);
    Vector3 operator-(const Vector3& other) const;
    Vector3& operator-=(const Vector3& other);

    Vector3 operator*(float scalar) const;
    Vector3 operator*=(float scalar);
    Vector3 operator/(float scalar) const;
    Vector3 operator/=(float scalar);

    bool operator<(const Vector3& other) const;
    bool operator==(const Vector3& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);

    float x;
    float y;
    float z;

private:


};