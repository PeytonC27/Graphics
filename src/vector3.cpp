#include "vector3.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::~Vector3() {}

float Vector3::magnitude() {
    return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalized() {
    float magnitude = this->magnitude();
    return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

Vector3 Vector3::operator+(const Vector3 &other) const {
    return Vector3(this->x + other.x, this->y + other.y);
}   

Vector3& Vector3::operator+=(const Vector3 &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3& Vector3::operator-=(const Vector3 &other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}


Vector3 Vector3::operator*(float scalar) const {
    return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vector3 Vector3::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

Vector3 Vector3::operator/(float scalar) const {
    return Vector3(this->x / scalar, this->y / scalar, this->z / scalar);
}

Vector3 Vector3::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

bool Vector3::operator<(const Vector3& other) const {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z) < std::sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
}

bool Vector3::operator==(const Vector3& other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
}


std::ostream &operator<<(std::ostream &os, const Vector3 &vec) {
    os << "(" << vec.x << ", " << vec.y <<  ", " << vec.z << ")";
    return os;
}