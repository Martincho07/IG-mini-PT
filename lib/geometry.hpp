/*********************************************************************************
 * Geometry
 *
 * File: coordinate.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once
#include <assert.h>
#include <iostream>
#include <math.h>

struct Vector3;
struct Point3;

// Vectors
struct Vector3 {
    float x, y, z;

    // Constructors
    Vector3() : x(0.0f), y(0.0f), z(0.0f){};
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
        //assert(!hasNaNs());
    };

    // Check if any component has the floating point NaN value
    bool hasNaNs() {
        return isnan(x) || isnan(y) || isnan(z);
    }

    // Operators

    // Sum of two vectors
    Vector3 operator+(const Vector3 &v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 &operator+=(const Vector3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // Substraction of two vectors
    Vector3 operator-(const Vector3 &v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 &operator-=(const Vector3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // Multiply vector by a scalar
    Vector3 operator*(float s) const {
        return Vector3(s * x, s * y, s * z);
    }

    Vector3 &operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // Divide vector by a scalar
    Vector3 operator/(float s) const {
        assert(s != 0);
        return Vector3(x / s, y / s, z / s);
    }

    Vector3 &operator/=(float s) {
        assert(s != 0);
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    // Vector negation. Returns a new vector pointing to the opposite direction
    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }
};

// Print a vector
inline std::ostream &operator<<(std::ostream &os, const Vector3 &v) {
    os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return os;
}

// Return a vector with the absolute value applied to each component
Vector3 abs(const Vector3 &v);

// Dot product of two vectors
float dot(const Vector3 &v1, const Vector3 &v2);

// Cross product of two vectors
Vector3 cross(const Vector3 &v1, const Vector3 &v2);

// Modulus of a vector
float modulus(const Vector3 &v);

// Normalize the vector
Vector3 normalize(const Vector3 &v);

// Points
struct Point3 {
    float x, y, z;

    // Constructors
    Point3() : x(0.0f), y(0.0f), z(0.0f){};
    Point3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
        assert(!hasNaNs());
    };

    // Check if any component has the floating point NaN value
    bool hasNaNs() {
        return isnan(x) || isnan(y) || isnan(z);
    }

    // Operators

    // Add a vector to the point
    Point3 operator+(const Vector3 &v) const {
        return Point3(x + v.x, y + v.y, z + v.z);
    }

    Point3 &operator+=(const Point3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // Substraction of two points to get a direction
    Vector3 operator-(const Point3 &p) const {
        return Vector3(x - p.x, y - p.y, z - p.z);
    }

    // Substract a vector from the point
    Point3 operator-(const Vector3 &v) const {
        return Point3(x - v.x, y - v.y, z - v.z);
    }

    Point3 &operator-=(const Point3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // Multiply point by a scalar (it doesnt' make sense mathematically)
    Point3 operator*(float s) const {
        return Point3(s * x, s * y, s * z);
    }

    Point3 &operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // Divide point by a scalar (it doesn't make sense mathematically)
    Point3 operator/(const float s) const {
        assert(s != 0);
        return Point3(x / s, y / s, z / s);
    }

    Point3 &operator/=(const float s) {
        assert(s != 0);
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    // Vector negation. Returns a new vector pointing to the opposite direction
    Point3 operator-() const {
        return Point3(-x, -y, -z);
    }

    // Cast a vector to a point
    explicit operator Vector3() const {
        return Vector3(x, y, z);
    }
};

// Print a point
inline std::ostream &operator<<(std::ostream &os, const Point3 &p) {
    os << "[ " << p.x << ", " << p.y << ", " << p.z << " ]";
    return os;
}

// Return a point with the absolute value applied to each component
Vector3 abs(const Vector3 &v);

// Return the distance between two points
float distance(const Point3 &p1, const Point3 &p2);