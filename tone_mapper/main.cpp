/*********************************************************************************
 * main
 *
 * File: main.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "error.hpp"
#include "file.hpp"
#include "image.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>

void help() {
    std::cout << "Usage: tone_mapper [options] filename\n\n"
                 "Options:\n"
                 "  -o <filename>   Specify output filename\n"
                 "  -clamp <value>  Clamp the image at <value>\n"
                 "  -h              Show this help screen and quit\n"
              << std::endl;
}

int main(int argc, char **argv) {
    std::string inFile;
    std::string outFile;
    int clamp = 1;
    float maxValue;
    char option = ' ';
    float v = 0;

    // Process arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        std::cout << "argumento: " << arg << std::endl;
        if (arg[0] == '-') {
            if (arg == "-o") {
                if (i + 1 >= argc) {
                    ErrorExit("Missing value after ", arg, " argument");
                }
                outFile = argv[i + 1];
                i++;
            } else if (arg == "-clamp") {
                if (i + 1 >= argc) {
                    ErrorExit("Missing value after ", arg, " argument");
                }
                clamp = std::stof(argv[i + 1]);
                i++;
            } else if (arg == "-h") {
                help();
                return 0;
            } else {
                ErrorExit("Invalid option");
            }
        } else {
            // file name
            inFile = arg;
            break;
        }
    }

    if (!inFile.empty()) {
        if (outFile.empty()) {
            outFile = createOutFilename(inFile);
        }

        std::cout << "Antes de procesar" << std::endl;
        std::cout << "inFile: " << inFile << " outFile: " << outFile << std::endl;
        std::cout << "clamp: " << clamp << std::endl;

        Image img = readPPM(inFile);
        maxValue = img.getMax();

        std::cout << "Seleccione el tone mapper a aplicar:" << std::endl;
        std::cout << "\t 1-Clamping. " << std::endl;
        std::cout << "\t 2-Equalization. " << std::endl;
        std::cout << "\t 3-Equalize and clamp. " << std::endl;
        std::cout << "\t 4-Gamma curve. " << std::endl;
        std::cout << "\t 5-Clamp and gamma curve. " << std::endl;
        std::cout << "\t 6-Reinhard 2002. " << std::endl;
        std::cin >> option;

        if (option == '1') {
            std::cout << "Applying clamping..." << std::endl;
            clampAndGammaCurve(img, 1.0f, 1.0f);

        } else if (option == '2') {
            std::cout << "Applying equalization..." << std::endl;
            clampAndGammaCurve(img, maxValue, 1.0f);

        } else if (option == '3') {
            std::cout << "Enter a value v = [0," << maxValue << "]" << std::endl;
            std::cin >> v;
            assert(v >= 0 && v <= maxValue);
            std::cout << "Applying equalize and clamp..." << std::endl;
            clampAndGammaCurve(img, v, 1.0f);
        
        } else if (option == '4'){
            std::cout << "Applying gamma curve..." << std::endl;
            clampAndGammaCurve(img, maxValue, 1.0f/2.2f);

        } else if (option == '5') {
            std::cout << "Enter a value v = [0," << maxValue << "]" << std::endl;
            std::cin >> v;
            assert(v >= 0 && v <= maxValue);
            std::cout << "Applying clamp and gamma curve..." << std::endl;
            clampAndGammaCurve(img, v, 1.0f/2.2f);

        } else if (option == '6') {
            std::cout << "Enter a value v = [0," << maxValue << "]" << std::endl;
            std::cin >> v;
            assert(v >= 0 && v <= maxValue);
            std::cout << "Applying Reinhard 2002..." << std::endl;
            Reinhard(img, v, maxValue);

        } else {
            std::cout << "Opcion invalida" << std::endl;
            return 1;
        }

        writePPM(img, outFile);


    } else {
        help();
    }

    return 0;
}
