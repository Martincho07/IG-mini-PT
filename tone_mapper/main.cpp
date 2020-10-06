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

    if (argc == 1){



        std::ifstream f_in;

        if (argc == 1){}
            if (f_in.open(argv[1], std::ios::in)) {

                Image img = readPPM(f_in);


            } else {
                std::cout << "No se ha podido abrir el fichero: " << argv[1] << std::endl;
                return 1;
            }
        } else {

                std::cout << "El unico parametro admitido es el path de un archivo .ppm"

        }

        f_in.close();
    }
}
