/*********************************************************************************
 * Transformations
 *
 * File: transform.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 24/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "geometry.hpp"

// Matrix of dimension 4x4
struct Matrix4x4 {
    float m[4][4];

    // Constructors
    Matrix4x4() : m{0} {};

    Matrix4x4(float _m[4][4])
        : m{_m[0][0], _m[0][1], _m[0][2], _m[0][3], _m[1][0], _m[1][1], _m[1][2], _m[1][3], _m[2][0], _m[2][1], _m[2][2], _m[2][3], _m[3][0], _m[3][1], _m[3][2], _m[3][3]} {};

    Matrix4x4(float m00, float m01, float m02, float m03,
              float m10, float m11, float m12, float m13,
              float m20, float m21, float m22, float m23,
              float m30, float m31, float m32, float m33)
        : m{m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33} {};

    // Operators

    // Multiply two matrixes
    Matrix4x4 operator*(const Matrix4x4 &m2) const {
        Matrix4x4 r;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                r.m[i][j] = m[i][0] * m2.m[0][j] + m[i][1] * m2.m[1][j] +
                            m[i][2] * m2.m[2][j] + m[i][3] * m2.m[3][j];
            }
        }
        return r;
    }
};

// Return the transposed matrix
Matrix4x4 transpose(const Matrix4x4 &m);

// Return the inversed matrix
Matrix4x4 inverse(const Matrix4x4 &m);

// Transformations
class Transform {
  private:
    Matrix4x4 m, mInv;

  public:
    // Constructors
    Transform(){};

    Transform(const Matrix4x4 &m) : m(m), mInv(inverse(m)){};

    Transform(const Matrix4x4 &m, const Matrix4x4 &mInv) : m(m), mInv(mInv){};

    // Operators

    // Apply the transfomation to a point
    Point3 operator()(const Point3 &p) const {
        // Assume that the homogenous coordinate for the point p is 1
        float xp = m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2] * p.z + m.m[0][3];
        float yp = m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2] * p.z + m.m[1][3];
        float zp = m.m[2][0] * p.x + m.m[2][1] * p.y + m.m[2][2] * p.z + m.m[2][3];
        float wp = m.m[3][0] * p.x + m.m[3][1] * p.y + m.m[3][2] * p.z + m.m[3][3];

        assert(wp != 0); // TODO

        if (wp == 1) {
            return Point3(xp, yp, zp);
        } else {
            return Point3(xp, yp, zp) / wp;
        }
    }

    // Apply the transformation to a vector
    Vector3 operator()(const Vector3 &v) const {
        // Assume that the homogeneous coordinate for the vector v is 0
        return Vector3(m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z,
                       m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z,
                       m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z);
    }

    // Compose
    Transform operator*(const Transform &t2) const {
        return Transform(m * t2.m);
    }

    // Return the inverse transformation
    friend Transform inverse(const Transform &t);
};

// Return the identity transformation
Transform identity();

// Return a translation transformation in the direction of the delta vector
Transform translation(const Vector3 &delta);

// Return a scale transformation
Transform scale(float tx, float ty, float tz);

// Return a rotation transformation over the X axis
Transform rotationX(float theta);
// Return a rotation transformation over the Y axis
Transform rotationY(float theta);
// Return a rotation transformation over the Z axis
Transform rotationZ(float theta);

// Return a change of base transformation
Transform changeBasis(const Vector3 &u, const Vector3 &v, const Vector3 &w,
                      const Point3 &o);
