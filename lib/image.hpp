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
#include <math.h>

// Reinhard constants for tone mapper algorithm
#define GAMMA 1.0f/2.2f
#define FI 8.0f
#define THRESHOLD 0.05f
#define ALPHA_1 0.35f
#define ALPHA_2 ALPHA_1 * 1.6f 

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

    float getMin() const {

        float minValue = 0.0;
        float aux = INFINITY;

        for (const RGB & pixel: v){

            minValue = pixel.getMinValue();

            if (minValue < aux && minValue != 0.0f)
                aux = minValue;
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

void Reinhard(Image &img, float a, float max);

int selectS(int x, int y, const int s[9], const RGB &pixel, float a, float L);

float V(int x, int y, int s, const RGB &pixel, float a, float L);

float V_i(int x, int y, int s,float alpha, const RGB &pixel, float L);

float R_i(int x, int y, int s,float alpha);