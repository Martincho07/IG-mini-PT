/*********************************************************************************
 * Image
 *
 * File: image.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "image.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

void readPPMComment(std::ifstream &is, float &max) {
    std::string comment;
    char p;
    // Eat whitespace
    while (p = is.peek(), std::isspace(p)) {
        is.get();
    }
    if (p == '#') {
        std::getline(is, comment);
        // Check if the comment is a max value declaration
        if (comment.substr(0, 5) == "#MAX=") {
            max = stof(comment.substr(5));
            if (max < 1) {
                std::cerr << "Unsupported max value: " << max << std::endl;
                exit(1);
            }
        }
        // Recursive call to read more comments
        readPPMComment(is, max);
    }
}

Image readPPM(std::ifstream &is) {
    int height, width, colorResolution;
    float max = 1;

    readPPMComment(is, max);

    // Make sure that the file format is P3
    std::string format;
    is >> format;
    if (format != "P3") {
        std::cerr << "Invalid PPM file, the magic number should be 'P3'" << std::endl;
        exit(1);
    }

    // Get width and height
    readPPMComment(is, max);
    is >> width >> height;
    if (width < 1) {
        std::cerr << "Unsupported width: " << width << std::endl;
        exit(1);
    }
    if (height < 1) {
        std::cerr << "Unsupported height: " << height << std::endl;
        exit(1);
    }

    // Get colorResolution
    readPPMComment(is, max);
    is >> colorResolution;
    if (colorResolution < 1) {
        std::cerr << "Unsupported color resolution: " << colorResolution << std::endl;
        exit(1);
    }

    // Read RGB tuples row by row
    readPPMComment(is, max);

    // Each tuple is mutiplied by this factor to get the real RGB value
    float f = max / colorResolution;

    std::vector<RGB> v(width * height);
    for (int i = 0; i < width * height; i++) {
        is >> v[i];
        v[i] = v[i] * f;
    }

    std::cout << colorResolution << " " << max << " " << width << " " << height << std::endl;
    return Image(v, colorResolution, max, width, height);
}

void writePPM(std::ofstream os, const Image &img){};
