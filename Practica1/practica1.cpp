/*********************************************************************************
 * Main
 *
 * File: main.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, curso 2020-2021
 **********************************************************************************/

#include <iostream>

#include "geometry.hpp"
#include "planet.hpp"

Planet askForStation() {
    Vector3 axis;
    Point3 center, refCity;
    float inclination, azimuth;

    float x, y, z;

    std::cout << "Enter a station:" << std::endl;
    std::cout << "\tPlanet center: ";
    std::cin >> x >> y >> z;
    center = Point3(x, y, z);
    std::cout << "\tReference city: ";
    std::cin >> x >> y >> z;
    refCity = Point3(x, y, z);
    std::cout << "\tPlanet axis: ";
    std::cin >> x >> y >> z;
    axis = Vector3(x, y, z);
    std::cout << "\tStation inclination: ";
    std::cin >> inclination;
    std::cout << "\tStation azimuth: ";
    std::cin >> azimuth;

    return Planet(center, refCity, axis, inclination, azimuth);
}

int main() {
    Planet planet1 = askForStation();
    Planet planet2 = askForStation();
}
