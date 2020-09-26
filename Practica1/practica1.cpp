/*********************************************************************************
 * Main
 *
 * File: main.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, curso 2020-2021
 **********************************************************************************/

#include <fstream>
#include <iostream>

#include "geometry.hpp"
#include "planet.hpp"

Planet readStation(std::istream &is, bool interactive) {
    Vector3 axis;
    Point3 center, refCity;
    float inclination, azimuth;

    float x, y, z;

    // If interactive is false, supress the ouput
    if (!interactive) {
        std::cout.setstate(std::ios::failbit);
    }

    std::cout << "Enter a station:" << std::endl;
    std::cout << "\tPlanet center: ";
    is >> x >> y >> z;
    center = Point3(x, y, z);
    std::cout << "\tPlanet axis: ";
    is >> x >> y >> z;
    axis = Vector3(x, y, z);
    std::cout << "\tReference city: ";
    is >> x >> y >> z;
    refCity = Point3(x, y, z);
    std::cout << "\tStation inclination: ";
    is >> inclination;
    std::cout << "\tStation azimuth: ";
    is >> azimuth;

    // Restore cout status
    std::cout.clear();

    std::cout << center << axis << refCity << inclination << azimuth << std::endl;

    return Planet(center, refCity, axis, inclination, azimuth);
}

int main(int argc, char **argv) {
    // If there's a file as argument, read it
    // Else, ask for the stations from standard input
    Planet planet1, planet2;

    if (argc > 1) {
        std::filebuf fb;
        if (fb.open(argv[1], std::ios::in)) {
            std::istream is(&fb);
            planet1 = readStation(is, false);
            planet2 = readStation(is, false);
        } else {
            std::cout << "No se ha podido abrir el fichero: " << argv[1] << std::endl;
            return 1;
        }
    } else {
        std::cout << "Origin planet" << std::endl;
        planet1 = readStation(std::cin, true);
        std::cout
            << std::endl
            << "Destination planet" << std::endl;
        planet2 = readStation(std::cin, true);
    }

    std::cout << std::endl
              << "Trayectorias" << std::endl;
    launch(planet1, planet2);
    return 0;
}
