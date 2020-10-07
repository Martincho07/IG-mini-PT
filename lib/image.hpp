/*********************************************************************************
 * Image
 *
 * File: image.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "color.hpp"
#include <fstream>
#include <string>
#include <vector>

struct Image {

    std::vector<RGB> v;
    float m;
    float c;
    int width;
    int height;

    Image(){};

    // Constructors
    Image(const std::vector<RGB> _v, float _c, float _m, int _width, int _height)
        : v(_v), c(_c), m(_m), width(_width), height(_height){};

    // Tone mapping functions
    void clamping(){

        for(RGB &pixel: v){

            if (pixel.r > 255)
                pixel.r = 255;

            if(pixel.g > 255)
                pixel.g = 255;

            if(pixel.b > 255)
                pixel.b = 255;
        }

    };

    void equalization(){};

    void equalizeAndClamp(){};

    void gammaCurve(){};

    void clampAndGammaCurve(){};

    void toDisk(){

        for(RGB &pixel: v){

            pixel = pixel * (c/m);
        }
    };
};

/* Read an image stored in a modified PPM format for representing HDR images
 *
 * Modified .ppm format:
 *
 * P3
 * #MAX=<max>
 * <width> <heigth>
 * <colorResolution>
 * <r> <g> <b>     <r> <g> <b> ...
 * <r> <g> <b>     <r> <g> <b> ...
 * ...
 *
 * Lines starting with # are considered comments
 * With the #MAX=<max> comment it's posible to indicate
 * the real maximum of the image as a real number, in case
 * it's different to 1.
 */
Image readPPM(std::ifstream &is);

/*
 * Read an image stored in memory as vector and create a PPM file
 *
 * .ppm format:
 *
 * P3
 * <width> <heigth>
 * 255
 * <r> <g> <b> ... <r> <g> <b>
 * <r> <g> <b> ... <r> <g> <b>
 *     ...             ...
 * <r> <g> <b> ... <r> <g> <b>
 *
 * The color resolution is always 255
 */
void writePPM(std::ofstream os, const Image &img);

