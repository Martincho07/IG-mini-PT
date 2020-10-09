/*********************************************************************************
 * Image
 *
 * File: image.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "color.hpp"

#include <fstream>
#include <string>
#include <vector>

#define GAMMA 1.0f/2.2f

struct Image {

    std::vector<RGB> v;
    int width;
    int height;

    Image(){};

    // Constructors
    Image(const std::vector<RGB> _v, int _width, int _height)
        : v(_v), width(_width), height(_height){};

    float getMax() const {

        float maxValue = 0.0;
        float aux = -1.0f;

        for (const RGB & pixel: v){

            maxValue = pixel.getMaxValue();

            if (maxValue > aux)
                aux = maxValue;

        }
        return aux;

    };
};

// Tone mapping functions
void clamping(Image &img);

void equalization(Image &img, float V);

void equalizeAndClamp(Image &img,  float V);

void gammaCurve(Image &img, float V, float gamma=GAMMA);

void clampAndGammaCurve(Image &img, float V, float gamma=GAMMA);

