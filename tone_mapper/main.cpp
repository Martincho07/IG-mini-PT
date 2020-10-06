/*********************************************************************************
 * main
 *
 * File: main.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "image.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char **argv) {

    if (argc == 2) {
        std::ifstream f(argv[1], std::ios::in);

        if (f.is_open()) {
            std::cout << "Fichero abierto" << std::endl;
            Image img = readPPM(f);
            f.close();
        } else {
            std::cerr << "Could not open file: " << argv[1] << std::endl;
        }
    } else {
        std::cout << "El unico parametro admitido es el path de un archivo .ppm" << std::endl;
    }
}
