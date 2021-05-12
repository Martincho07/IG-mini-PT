/*********************************************************************************
 * Camera
 *
 * File: camera.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "camera.hpp"
#include "random.hpp"

Camera::Camera(float fov, const Point3 &target, float distance, float aspect_ratio) {

    // grados a radianes
    fov = (fov * M_PI) / 180.0f;

    r = Vector3(1, 0, 0);
    u = Vector3(0, 1, 0);
    f = Vector3(0, 0, 1);

    o = target - f * distance;
    // o = target - f + Vector3(0, 0, -distance);

    u = u * (tanf(fov / 2.0f));
    r = r * (aspect_ratio * modulus(u));

    r = r * distance;
    u = u * distance;
    f = f * distance;

    camera2world = Transform(Matrix4x4(r.x, u.x, f.x, o.x,
                                       r.y, u.y, f.y, o.y,
                                       r.z, u.z, f.z, o.z,
                                       0.0f, 0.0f, 0.0f, 1.0f));
};

Ray PinholeCamera::calculate_ray(float x, float y) const {
    Vector3 xr = r * x;
    Vector3 yu = u * y;
    Vector3 direction = xr + yu + f;

    return Ray(o, direction);
}

Ray ThinLensCamera::calculate_ray(float x, float y) const {
    float ua, va;

    // Rejection sampling
    // float r1, r2;
    // do {
    //     r1 = random_float();
    //     r2 = random_float();
    // } while (r1 * r1 + r2 * r2 <= 1);
    // float max = aperture_radius;
    // float min = -aperture_radius;
    // ua = (max - min) * r1 + min;
    // va = (max - min) * r2 + min;

    // https://stackoverflow.com/questions/5837572/generate-a-random-point-within-a-circle-uniformly
    float arand = aperture_radius * sqrt(random_float());
    float theta = random_float() * 2 * M_PI;
    ua = arand * cos(theta);
    va = arand * sin(theta);

    // // Random
    // ua = random_float(-aperture_radius, aperture_radius);
    // va = random_float(-aperture_radius, aperture_radius);

    Point3 oray = o + (r / (2 * modulus(r))) * ua + (u / (2 * modulus(u))) * va;
    Point3 center = o + r * x + u * y + f;

    Vector3 direction = normalize(center - oray);

    return Ray(oray, direction);
}
