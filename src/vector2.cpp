#include "vector2.h"
#include <cmath>

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2::Vector2() : x(0), y(0) {}

Vector2::~Vector2() {}

float Vector2::magnitude() {
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() {
    float magnitude = this->magnitude();
    return Vector2(x / magnitude, y / magnitude);
}

// https://stackoverflow.com/questions/1243614/how-do-i-calculate-the-normal-vector-of-a-line-segment
Vector2 Vector2::normal() {
    Vector2 vectorRotated90CCW = Vector2(-this->y, this->x);

    return vectorRotated90CCW;
}

Vector2 Vector2::operator+(const Vector2 &other) const {
    return Vector2(this->x + other.x, this->y + other.y);
}   

Vector2& Vector2::operator+=(const Vector2 &other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2 &other) const {
    return Vector2(this->x - other.x, this->y - other.y);
}

Vector2& Vector2::operator-=(const Vector2 &other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}


Vector2 Vector2::operator*(float scalar) const {
    return Vector2(this->x * scalar, this->y * scalar);
}

Vector2 Vector2::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector2 Vector2::operator/(float scalar) const {
    return Vector2(this->x / scalar, this->y / scalar);
}

Vector2 Vector2::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

bool Vector2::operator<(const Vector2& other) const {
    return std::sqrt(this->x * this->x + this->y * this->y) < std::sqrt(other.x * other.x + other.y * other.y);
}


std::ostream &operator<<(std::ostream &os, const Vector2 &vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

Vector2 Vector2::up(0, 1);
Vector2 Vector2::down(0, -1);
Vector2 Vector2::left(-1, 0);
Vector2 Vector2::right(1, 0);