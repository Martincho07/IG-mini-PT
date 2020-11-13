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
#include "color.hpp"
#include "math.h"
#include <cfloat>

void Image::applyToneMappingOperator(const ToneMappingOperator &op) {
    std::cout << "Applying operator: " << op << " ..." << std::endl;
    for (RGB &pixel : v)
        pixel = op(pixel);
}

void Image::puntOnCoordenate(int f, int c, const RGB r) {
    //std::cout << "f, c: " << f << " " << c << std::endl;
    v[(f * width) + c] = r;
};

float max(const Image &img) {
    float maxValue = FLT_MIN;
    float aux = 0.0f;
    for (const RGB &pixel : img.v) {
        aux = max(pixel);
        if (aux > maxValue)
            maxValue = aux;
    }

    return maxValue;
};

float maxLum(const Image &img) {
    float maxLuma = -1.0f;

    for (const RGB &pixel : img.v)
        maxLuma = std::max(rgb2lab(pixel).l, maxLuma);

    return maxLuma;
};

float min(const Image &img) {
    float minValue = FLT_MAX;
    float aux = 0.0f;
    for (const RGB &pixel : img.v) {
        aux = min(pixel);
        if (aux < minValue)
            minValue = aux;
    }
    return aux;
};

float logAverageLuminance(const Image &img) {
    float avg_L_w = 0.0f;

    for (const RGB &pixel : img.v) {
        // std::cout << "L: " << pixel.L() << std::endl;
        //std::cout << "lab.l: " << rgb2lab(pixel).l * 100 << std::endl;

        // std::cout << logf(1e-6f + pixel.L()) << std::endl;
        //std::cout << rgb2lab(pixel).l << std::endl;
        avg_L_w += log(1e-45f + rgb2lab(pixel).l);
        // avg_L_w += logf(1e-6f + pixel.L());
    }
    std::cout << avg_L_w << std::endl;
    std::cout << exp(avg_L_w) << std::endl;

    avg_L_w = exp(avg_L_w / img.v.size());
    return avg_L_w;
}

void clamping(Image &img) {
    for (RGB &pixel : img.v) {
        if (pixel.r > 1.0f)
            pixel.r = 1.0f;

        if (pixel.g > 1.0f)
            pixel.g = 1.0f;
        if (pixel.b > 1.0f)
            pixel.b = 1.0f;
    }
};

void equalization(Image &img, float V) {
    for (RGB &pixel : img.v) {
        pixel = pixel / V;
    }
};

void equalizeAndClamp(Image &img, float V) {
    equalization(img, V);
    clamping(img);
};

void gammaCurve(Image &img, float V, float gamma) {
    equalization(img, V);
    for (RGB &pixel : img.v)
        pixel = pow(pixel, gamma);
};

void clampAndGammaCurve(Image &img, float V, float gamma) {
    gammaCurve(img, V, gamma);
    clamping(img);
};

void Reinhard(Image &img, float a) {

    // white luminity average
    float L_w_avg = 0.0f;

    // pixel luminity
    float L = 0.0f;

    float L_w = 0.0f;

    float L_d = 0.0f;

    // min wite in the image
    float min_L = max(img);

    // Reinhard algorithm
    // http://erikreinhard.com/papers/s2002.pdf

    for (const RGB &pixel : img.v)
        L_w_avg += logf(1e-6f + pixel.L());

    L_w_avg = expf(L_w_avg / (img.width * img.height));

    for (RGB &pixel : img.v) {

        L = a / L_w_avg * pixel.L();
        L_d = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
        pixel / (L_d * pixel.L());
    }
};

void Mantiuk(Image &img, float a, float s = 0.6f) {

    // white luminity
    float L_w = 0.0f;

    float L_tone_mapping = 0.0f;
    // pixel luminity
    float L = 0.0f;

    float L_pixel = 0.0f;

    // min wite in the image
    float min_L = max(img);

    // Mantiuk algorithm
    // https://www.researchgate.net/publication/317749456_A_comparative_review_of_tone-mapping_algorithms_for_high_dynamic_range_video
    for (const RGB &pixel : img.v)
        L_w += logf(1e-6f + pixel.L());

    L_w = expf(L_w / (img.width * img.height));

    for (RGB &pixel : img.v) {
        pixel = pixel * (1.0f / 4.0f);
        L_pixel = pixel.L();
        L = (a / L_w) * pixel.r;
        L_tone_mapping = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
        pixel.r = pow(pixel.r / L_pixel, s) * L_tone_mapping;

        L = (a / L_w) * pixel.g;
        L_tone_mapping = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
        pixel.g = pow(pixel.g / L_pixel, s) * L_tone_mapping;

        L = (a / L_w) * pixel.b;
        L_tone_mapping = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
        pixel.b = pow(pixel.b / L_pixel, s) * L_tone_mapping;
    }
};