/*********************************************************************************
 * Planet
 *
 * File: planet.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 26/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "planet.hpp"

#include <assert.h>
#include <cmath>

Planet::Planet(const Point3 &_center, const Point3 &_refCity, const Vector3 &_axis, float inclination, float azimuth)
    : center(_center), refCity(_refCity), axis(_axis) {

    //  u is normal to the planet surface
    Vector3 u = refCity - center;

    float radius = modulus(axis) / 2;

    // Test that the parameters are correct
    assert(SIMILAR(modulus(u), radius));
    assert(inclination > 0 && inclination < M_PI);
    assert(azimuth >= -M_PI && azimuth <= M_PI);

    // Construct a coordinate system local to the planet
    // The x axis has 0 azimuth
    Vector3 zPlanet = normalize(cross(u, axis));
    Vector3 yPlanet = normalize(axis);
    Vector3 xPlanet = cross(yPlanet, zPlanet);

    std::cout << "Sistema interno planeta: " << std::endl
              << "\tx: " << xPlanet.x << " " << xPlanet.y << " " << xPlanet.z << std::endl
              << "\ty: " << yPlanet.x << " " << yPlanet.y << " " << yPlanet.z << std::endl
              << "\tz: " << zPlanet.x << " " << zPlanet.y << " " << zPlanet.z << std::endl;

    // Create a point on the north pole and rotate it on the Z and Y axis
    Point3 station = Point3(0, radius, 0);

    std::cout << "Estacion sin rotar: " << std::endl
              << "\tvalues: " << station.x << " " << station.y << " " << station.z << std::endl;
    station = (rotationY(azimuth) * rotationZ(inclination))(station);

    std::cout << "Estacion rotada: " << std::endl
              << "\tvalues: " << station.x << " " << station.y << " " << station.z << std::endl;

    // Calculate station's local coordinate system
    orig = changeBasis(xPlanet, yPlanet, zPlanet, center)(station); // origin in the UCS
    k = normalize(orig - center);                                   // Surface normal
    i = normalize(cross(k, axis));                                  // Latitude tangent direction
    j = normalize(cross(k, i));                                     // Longitude tangent direction

    std::cout << "Sistema coords: " << std::endl
              << "\ti: " << i << std::endl
              << "\tj: " << j << std::endl
              << "\tk: " << k << std::endl
              << "\torig" << orig << std::endl;
};

bool inSurface(const Planet &planet, const Point3 &p) {
    return (dot((p - planet.center), (p - planet.center)) - pow(modulus(planet.axis) / 2, 2)) == 0;
};

void launch(const Planet &origin, const Planet &destination) {
    // Hay que restar los origenes de los sistemas de coordenadas de los planetas para obtener el vector de la trayeectoria

    Vector3 path = destination.orig - origin.orig;
    std::cout << "path: " << path << std::endl;

    // Comprobar que los vectores no atraviesan el planeta
    std::cout << "Orig: " << dot(path, origin.k) << std::endl;
    std::cout << "Dest: " << dot(path, destination.k) << std::endl;

    std::cout << "Orig origin" << origin.orig << std::endl;
    std::cout << "Dest origin" << destination.orig << std::endl;

    std::cout << "Trayectoria canonico: " << path << std::endl;

    // Ahora cambiamos de base la trayectoria para verla desde el punto de vista desde las dos estaciones
    Transform ob = changeBasis(origin.i, origin.j, origin.k, origin.orig);
    std::cout << dot(origin.i, origin.j) << dot(origin.j, origin.k) << dot(origin.j, origin.i) << dot(origin.k, origin.j) << std::endl;
    std::cout << "ob: " << ob << std::endl;
    std::cout << "inv ob: " << inverse(ob) << std::endl;

    Transform db = changeBasis(destination.i, destination.j, destination.k, destination.orig);
    std::cout << dot(destination.i, destination.j) << dot(destination.j, destination.k) << dot(destination.j, destination.i) << dot(destination.k, destination.i) << std::endl;
    std::cout << "db: " << db << std::endl;
    std::cout << "inv db: " << inverse(db) << std::endl;

    Vector3 pathFromOrigin = inverse(ob)(path);
    Vector3 pathFromDestination = inverse(db)(path);

    // Comprobar que las trayectorias no se meten dentro en el planeta
    // Esto es que el ángulo entre la trayectoria y la normal del planeta sea menor o igual que 90 grados
    // (que el coseno sea no negativo)
    assert(dot(path, origin.k) >= 0);
    assert(dot(-path, destination.k) >= 0);

    std::cout << "Trayectoria desde origin: " << pathFromOrigin << std::endl;
    std::cout << "Trayectoria desde destination: " << pathFromDestination << std::endl;
};
