/*********************************************************************************
 * Color
 *
 * File: image.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include <string>
#include <iostream>
#include <fstream>
#include "image.hpp"

Image readPPM(std::ifstream &is) {
    // Make sure that the file format is P3
    std::string format;
    is >> format;
    if (format != "P3") {
        std::cerr << "Invalid PPM file, first line should be 'P3'";

    }

    bool end = false;
    int readedLines = 0;
    while (!end && !is.eof()) {
        if (is.peek() == '#') {
            // The next line is a comment
            string line = is.
        }
        else {

        }

    }


    


}


void writePPM(const Image &img){

    std::ofstream f_out;
    f_out.open("salida.ppm",std::ios::out);

    if (f_out.fail()) {

        f_out << "P3" << std::endl;
        f_out << img.num_rows << " " << img.num_colums << std::endl;
        f_out << "255" << std::endl;

        for (int i = 0; i < img.v.size(); i+img.num_colums){

            for (int n = 0; n < img.num_colums; i++){

                if (n == img.num_colums)
                    f_out << img.v[i+n].r << " " << img.v[i+n].g << " " << img.v[i+n].b << std::endl;

                else
                
                    f_out << img.v[i+n].r << " " << img.v[i+n].g << " " << img.v[i+n].b << "  ";
            }

        }
        f_out.close();

    } else {
    
        std::cout << "Ha ocurrido un error"<< std::endl;
    }
    
};