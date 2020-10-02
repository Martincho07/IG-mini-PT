/*********************************************************************************
 * Transformations
 *
 * File: transform.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 24/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "transform.hpp"

#include <assert.h>
#include <cmath>

// Matrix4x4 method definitions
Matrix4x4 transpose(const Matrix4x4 &m) {
    Matrix4x4 r;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            r.m[i][j] = m.m[j][i];
        }
    }
    return r;
}

// Return the inversed matrix
Matrix4x4 inverse(const Matrix4x4 &m) {
    // https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    float A2323 = m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2];
    float A1323 = m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1];
    float A1223 = m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1];
    float A0323 = m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0];
    float A0223 = m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0];
    float A0123 = m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0];
    float A2313 = m.m[1][2] * m.m[3][3] - m.m[1][3] * m.m[3][2];
    float A1313 = m.m[1][1] * m.m[3][3] - m.m[1][3] * m.m[3][1];
    float A1213 = m.m[1][1] * m.m[3][2] - m.m[1][2] * m.m[3][1];
    float A2312 = m.m[1][2] * m.m[2][3] - m.m[1][3] * m.m[2][2];
    float A1312 = m.m[1][1] * m.m[2][3] - m.m[1][3] * m.m[2][1];
    float A1212 = m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1];
    float A0313 = m.m[1][0] * m.m[3][3] - m.m[1][3] * m.m[3][0];
    float A0213 = m.m[1][0] * m.m[3][2] - m.m[1][2] * m.m[3][0];
    float A0312 = m.m[1][0] * m.m[2][3] - m.m[1][3] * m.m[2][0];
    float A0212 = m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0];
    float A0113 = m.m[1][0] * m.m[3][1] - m.m[1][1] * m.m[3][0];
    float A0112 = m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0];

    float det =
        m.m[0][0] *
            (m.m[1][1] * A2323 - m.m[1][2] * A1323 + m.m[1][3] * A1223) -
        m.m[0][1] *
            (m.m[1][0] * A2323 - m.m[1][2] * A0323 + m.m[1][3] * A0223) +
        m.m[0][2] *
            (m.m[1][0] * A1323 - m.m[1][1] * A0323 + m.m[1][3] * A0123) -
        m.m[0][3] * (m.m[1][0] * A1223 - m.m[1][1] * A0223 + m.m[1][2] * A0123);

    det = 1 / det;

    return Matrix4x4(
        det * (m.m[1][1] * A2323 - m.m[1][2] * A1323 + m.m[1][3] * A1223),
        det * -(m.m[0][1] * A2323 - m.m[0][2] * A1323 + m.m[0][3] * A1223),
        det * (m.m[0][1] * A2313 - m.m[0][2] * A1313 + m.m[0][3] * A1213),
        det * -(m.m[0][1] * A2312 - m.m[0][2] * A1312 + m.m[0][3] * A1212),
        det * -(m.m[1][0] * A2323 - m.m[1][2] * A0323 + m.m[1][3] * A0223),
        det * (m.m[0][0] * A2323 - m.m[0][2] * A0323 + m.m[0][3] * A0223),
        det * -(m.m[0][0] * A2313 - m.m[0][2] * A0313 + m.m[0][3] * A0213),
        det * (m.m[0][0] * A2312 - m.m[0][2] * A0312 + m.m[0][3] * A0212),
        det * (m.m[1][0] * A1323 - m.m[1][1] * A0323 + m.m[1][3] * A0123),
        det * -(m.m[0][0] * A1323 - m.m[0][1] * A0323 + m.m[0][3] * A0123),
        det * (m.m[0][0] * A1313 - m.m[0][1] * A0313 + m.m[0][3] * A0113),
        det * -(m.m[0][0] * A1312 - m.m[0][1] * A0312 + m.m[0][3] * A0112),
        det * -(m.m[1][0] * A1223 - m.m[1][1] * A0223 + m.m[1][2] * A0123),
        det * (m.m[0][0] * A1223 - m.m[0][1] * A0223 + m.m[0][2] * A0123),
        det * -(m.m[0][0] * A1213 - m.m[0][1] * A0213 + m.m[0][2] * A0113),
        det * (m.m[0][0] * A1212 - m.m[0][1] * A0212 + m.m[0][2] * A0112));
}

// Transform method definitions
Transform identity() {
    Matrix4x4 m(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
    return Transform(m, m);
}

// Return a translation transformation in the direction of the delta vector
Transform translation(const Vector3 &delta) {
    Matrix4x4 m(1, 0, 0, delta.x,
                0, 1, 0, delta.y,
                0, 0, 1, delta.z,
                0, 0, 0, 1);
    Matrix4x4 mInv(1, 0, 0, -delta.x,
                   0, 1, 0, -delta.y,
                   0, 0, 1, -delta.z,
                   0, 0, 0, 1);
    return Transform(m, mInv);
}

// Return a scale transformation
Transform scale(float sx, float sy, float sz) {
    Matrix4x4 m(sx, 0, 0, 0,
                0, sy, 0, 0,
                0, 0, sz, 0,
                0, 0, 0, 1);
    Matrix4x4 mInv(1 / sx, 0, 0, 0,
                   0, 1 / sy, 0, 0,
                   0, 0, 1 / sz, 0,
                   0, 0, 0, 1);
    return Transform(m, mInv);
}

// Return a rotation transformation over the X axis
Transform rotationX(float theta) {
    float sinTheta = sinf(theta);
    float cosTheta = cosf(theta);
    Matrix4x4 m(1, 0, 0, 0,
                0, cosTheta, -sinTheta, 0,
                0, sinTheta, cosTheta, 0,
                0, 0, 0, 1);
    return Transform(m, transpose(m));
}

// Return a rotation transformation over the Y axis
Transform rotationY(float theta) {
    float sinTheta = sinf(theta);
    float cosTheta = cosf(theta);
    Matrix4x4 m(cosTheta, 0, sinTheta, 0,
                0, 1, 0, 0,
                -sinTheta, 0, cosTheta, 0,
                0, 0, 0, 1);
    return Transform(m, transpose(m));
}

// Return a rotation transformation over the Z axis
Transform rotationZ(float theta) {
    float sinTheta = sinf(theta);
    float cosTheta = cosf(theta);
    Matrix4x4 m(cosTheta, -sinTheta, 0, 0,
                sinTheta, cosTheta, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
    return Transform(m, transpose(m));
}

// Return a change of base transformation
Transform changeBasis(const Vector3 &u, const Vector3 &v, const Vector3 &w,
                      const Point3 &o) {
    Matrix4x4 m(u.x, v.x, w.x, o.x,
                u.y, v.y, w.y, o.y,
                u.z, v.z, w.z, o.z,
                0, 0, 0, 1);
    return Transform(m, inverse(m));
}

// Return the inverse transformation
Transform inverse(const Transform &t) {
    return Transform(t.mInv, t.m);
}
