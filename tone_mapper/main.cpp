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
#include <string>

void help() {
    std::cout << "Usage: tone_mapper [options] file.ppm\n\n"
                 "Options:\n"
                 "  -o <filename>   Specify output filename\n"
                 "  -clamp <value>  Clamp the image at <value>\n"
                 "  -h              Show this help screen and quit\n"
              << std::endl;
}

void invalidOption(const std::string &arg) {
    std::cerr << "Invalid option: " << arg << std::endl
              << std::endl;
    help();
}

std::string getFileExtension(const std::string &file) {
    size_t i = file.rfind('.', file.length());
    if (i != std::string::npos) {
        return file.substr(i + 1, file.length() - i);
    }
    return "";
}

#define outId "out_"

std::string createOutFilename(const std::string &file) {
    size_t i = file.find_last_of('/', file.length());

    if (i == std::string::npos) {
        i = 0;
    } else {
        i++;
    }

    std::string outFile = file;
    return outFile.insert(i, outId);
}

int main(int argc, char **argv) {
    std::string inFile;
    std::string outFile;
    int clamp = 1;

    // Process arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        std::cout << "argumento: " << arg << std::endl;
        if (arg[0] == '-') {
            // option
            if (arg.length() == 1) {
                invalidOption(arg);
                return 1;
            } else {
                if (arg == "-o") {
                    outFile = argv[i + 1];
                    i++;
                } else if (arg == "-clamp") {
                    clamp = std::stof(argv[i + 1]);
                    i++;
                } else if (arg == "-h") {
                    help();
                    return 0;
                } else {
                    invalidOption(arg);
                    return 1;
                }
            }
        } else {
            // file name
            inFile = arg;
            break;
        }
    }

    if (!inFile.empty()) {
        if (getFileExtension(inFile) != "ppm") {
            std::cerr << "Input file must have .ppm format" << std::endl;
        }

        if (outFile.empty()) {
            outFile = createOutFilename(inFile);
        }

        std::cout << "Antes de procesar" << std::endl;
        std::cout << "inFile: " << inFile << " outFile: " << outFile << std::endl;
        std::cout << "clamp: " << clamp << std::endl;

        std::ifstream f(inFile, std::ios::in);
        if (f.is_open()) {
            Image img = readPPM(f);
            img.clamping();
            img.toDisk();
            writePPM(img);
            f.close();
        } else {
            std::cerr << "Could not open file: " << inFile << std::endl;
        }


    } else {
        help();
        return 0;
    }
}
