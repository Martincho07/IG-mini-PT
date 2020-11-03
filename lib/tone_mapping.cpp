/*********************************************************************************
 * Tone mapping operands
 *
 * File: tone_mapping.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 21/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "tone_mapping.hpp"
#include "math.h"

RGB Exposure::operator()(const RGB &c) const {
    // Pixel luminance
    float L = c.L();
    // Scale pixel luminance
    float L_d = L * pow(2, step);
    // Apply luminance transformation
    return c / L * L_d;
    // return c * pow(2, step);
};

std::ostream &Exposure::format(std::ostream &os) const {
    os << "exposure (step = " << step << ")";
    return os;
}

RGB Clamp::operator()(const RGB &c) const {
    return RGB(c.r > 1.0 ? 1.0f : c.r,
               c.g > 1.0 ? 1.0f : c.g,
               c.b > 1.0 ? 1.0f : c.b);
};

std::ostream &Clamp::format(std::ostream &os) const {
    os << "clamp";
    return os;
}

RGB Equalize::operator()(const RGB &c) const {
    return c / value;
};

std::ostream &Equalize::format(std::ostream &os) const {
    os << "equalize (value = " << value << ")";
    return os;
}

RGB ClampAndEqualize::operator()(const RGB &c) const {
    return equalization(clamping(c));
};

std::ostream &ClampAndEqualize::format(std::ostream &os) const {
    os << "clamp and equalize [";
    clamping.format(os);
    os << ", ";
    equalization.format(os);
    os << "]";
    return os;
}

RGB GammaCurve::operator()(const RGB &c) const {
    return pow(equalization(c), inv_gamma);
};

std::ostream &GammaCurve::format(std::ostream &os) const {
    os << "gamma curve (gamma = " << gamma << ", ";
    equalization.format(os);
    os << ")";
    return os;
}

RGB ClampAndGammaCurve::operator()(const RGB &c) const {
    return gamma_curve(clamping(c));
};

std::ostream &ClampAndGammaCurve::format(std::ostream &os) const {
    os << "clamp and gamma curve";
    clamping.format(os);
    os << ", ";
    gamma_curve.format(os);
    os << "]";
    return os;
};

RGB Reinhard02::operator()(const RGB &c) const {
    // LAB lab_c = rgb2lab(c);
    // // XYZ xyz_c = rgb2xyz(c);
    // // World luminance for the pixel
    // float L_w = lab_c.l;
    // // float L_w = xyz_c.y;

    // // float L_w = c.L();

    LAB lab_c = rgb2lab(c);
    float L_w = lab_c.l;
    // Scaled luminance for the pixel
    float L = (a / avg_L_w) * L_w;
    // Tone mapped luminance preserving whites
    float L_d = (L * (1 + (L / pow(min_L, 2)))) / (1.0f + L);
    // Apply the luminance transformation on the pixel
    lab_c.l = L_d;
    // xyz_c.y = L_d;
    return clamping(lab2rgb(lab_c));
    // return lab2rgb(lab_c);
    // return xyz2rgb(xyz_c);
    // return Clamp()(c / L_w * L_d);

    // float L;
    // L = (a / avg_L_w) * c.r;
    // float r = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
    // L = (a / avg_L_w) * c.g;
    // float g = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
    // L = (a / avg_L_w) * c.b;
    // float b = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
    // return Equalize(min_L)(RGB(r, g, b));

    // float L_w, L, L_d;
    // L_w = c.L();
    // L = (a / avg_L_w) * L_w;
    // L_d = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
    // return RGB(
    //     pow(c.r / L_w, 0.9) * L_d,
    //     pow(c.g / L_w, 0.9) * L_d,
    //     pow(c.b / L_w, 0.9) * L_d);
};

std::ostream &Reinhard02::format(std::ostream &os) const {
    os << "Reinhard 2002 (a = " << a << ", avg_L_w = " << avg_L_w << ", min_L = " << min_L << ")";
    return os;
}

RGB Mantiuk08::operator()(const RGB &c) const {
    // World luminance for the pixel
    float L_w = c.L();
    // Scaled luminance for the pixel
    float L = a / avg_L_w * L_w;
    // Tone mapped luminance preserving whites
    float L_d = L * (1 + L / pow(min_L, 2)) / (1.0f + L);
    // Apply the luminance transformation on the pixel
    return Clamp()(c / L_w * L_d);
    // pixel = pixel * (1.0f / 4.0f);
    // L_pixel = pixel.L();
    // L = (a / L_w) * pixel.r;
    // L_tone_mapping = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
    // pixel.r = pow(pixel.r / L_pixel, s) * L_tone_mapping;

    // L = (a / L_w) * pixel.g;
    // L_tone_mapping = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
    // pixel.g = pow(pixel.g / L_pixel, s) * L_tone_mapping;

    // L = (a / L_w) * pixel.b;
    // L_tone_mapping = (L * (1.0f + L / pow(min_L, 2))) / (1.0f + L);
    // pixel.b = pow(pixel.b / L_pixel, s) * L_tone_mapping;
};

std::ostream &Mantiuk08::format(std::ostream &os) const {
    os << "Mantiuk 2008";
    return os;
}