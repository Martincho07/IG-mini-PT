/*********************************************************************************
 * Color
 *
 * File: image.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include <vector>
#include <string>
#include <fstream>
#include <color.hpp>

struct Image {

     std::vector<RGB> v;
     float m;
     float c;
     int num_rows;
     int num_colums;

    // Constructors
    Image(const std::vector<RGB>  _v, float _c, float _m, int _num_rows, int _num_colums) : 
    v(_v), c(_c), m(_m), num_rows(_num_rows), num_colums(_num_colums){}; 


    // Tone mapping functions
    void clamping() {

        for (RGB &pixel : v){

            if ()

            if()

            if()

        }

    };
    void equalization(){



    };
    void equalizeAndClamp(){



    };
    void gammaCurve(){




    };
    void clampAndGammaCurve(){



    };

};


// Read an image stored in a modified HDR PPM format
// 
// .ppm format:
//
// P3
// #MAX=<max>
// <width> <heigth>
// <colorResolution>
// <r> <g> <b>     <r> <g> <b> ...
// <r> <g> <b>     <r> <g> <b> ...
// ...
//
// Lines starting with # are considered comments
// With the #MAX=<max> comment it's posible to indicate
// the real maximum of the image as a real number in case
// it's different to 1.
Image readPPM(std::ifstream &is);

/*

    Read a imaege stored in memory as vector
    and create a PPM file

    .pp, format
    P3
    <width> <heigth>
    255
    <r> <g> <b> ... <r> <g> <b> 
    <r> <g> <b> ... <r> <g> <b> 

        ...             ...

    <r> <g> <b> ... <r> <g> <b> 

    the resolution(c) is ever equal to 255

*/
void writePPM(const Image &img);