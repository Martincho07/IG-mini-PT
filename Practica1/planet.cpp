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

bool inSurface(const Planet &planet, const Point3 &p) {
    return (dot((p - planet.center), (p - planet.center)) - pow(modulus(planet.axis) / 2, 2)) == 0;
}

void launch(const Planet &origin, const Planet &destination) {
    // Hay que restar los origenes de los sistemas de coordenadas de los planetas para obtener el vector de la trayeectoria

    Vector3 path = destination.orig - origin.orig;

    // Comprobar que los vectores no atraviesan el planeta
    assert(dot(path, origin.k) >= 0);
    assert(dot(path, destination.k) >= 0);

    std::cout << "Orig origin" << origin.orig << std::endl;
    std::cout << "Dest origin" << destination.orig << std::endl;

    std::cout << "Trayectoria canonico: " << path << std::endl;

    // Ahora cambiamos de base la trayectoria para verla desde el punto de vista desde las dos estaciones
    Transform ob = changeBase(origin.i, origin.j, origin.k, origin.orig);
    Transform db = changeBase(destination.i, destination.j, destination.k, destination.orig);

    Vector3 pathFromOrigin = ob(path);
    Vector3 pathFromDestination = db(path);

    std::cout << "Trayectoria desde orgin: " << pathFromOrigin << std::endl;
    std::cout << "Trayectoria desde destination: " << pathFromDestination << std::endl;
};
