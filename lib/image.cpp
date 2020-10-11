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
#include <bits/stdc++.h>
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

void equalization(Image &img, float V){

    for (RGB &pixel : img.v){
        pixel = pixel / V;

    }

};

void equalizeAndClamp(Image &img,  float V){
    equalization(img, V);
    clamping(img);

};

void gammaCurve(Image &img, float V, float gamma){
    equalization(img, V);
    for (RGB &pixel : img.v)
        pixel = pixel ^ gamma;
};

void clampAndGammaCurve(Image &img, float V, float gamma){
    gammaCurve(img,V,gamma);
    clamping(img);

};

void Reinhard(Image &img, float a, float max){

    

    // diferents scales
    int s[9] = {1, 2, 3, 4, 7, 10, 17, 27, 43};

    // best scale for a pixel
    float s_m;
    RGB pixel;
    int y = 0;

    // world luminity
    double L_w = 0.0f;

    // pixel luminity
    float L = 0.0f;

    // min wite in the image
    float min_L = img.getMax();

    // reinhard algorithm
    // http://erikreinhard.com/papers/s2002.pdf
    for (const RGB &pixel: img.v)
        L_w += logf(1e-6f + pixel.L());

    L_w = expf(L_w / (img.width * img.height));

    
    for (RGB &pixel: img.v){
        L = (a / L_w) * pixel.r;
        //s_m = selectS(y, n,s, pixel, a, L);   
        pixel.r = (L * (1.0f + L / pow(min_L,2))) / (1.0f + L);
        L = (a / L_w) * pixel.g;
        //s_m = selectS(y, n,s, pixel, a, L);
        pixel.g = (L * (1.0f + L / pow(min_L,2))) / (1.0f + L);
        L = (a / L_w) * pixel.b;
        //s_m = selectS(y, n,s, pixel, a, L);
        pixel.b = (L * (1.0f + L / pow(min_L,2))) / (1.0f + L);
    }
    
    /*
    for (int i = 0; i < img.v.size(); i = i + img.width) {
        for (int n = 0; n < img.width; n++) {

            pixel = img.v[i + n];
            L = (a / L_w) * pixel.r;
            s_m = selectS(n,(int) i,s, pixel, a, L);   
            pixel.r =  L / (1.0f + V_i(n,(int) i / img.width,s_m,ALPHA_1,pixel,L));

            L = (a / L_w) * pixel.g;
            s_m = selectS(n,(int) i,s, pixel, a, L);
            pixel.g = L / (1.0f + V_i(n,(int) i / img.width,s_m,ALPHA_1,pixel,L));

            L = (a / L_w) * pixel.b;
            s_m = selectS(n,(int) i,s, pixel, a, L);
            pixel.b = L / (1.0f + V_i(n,(int) i / img.width,s_m,ALPHA_1,pixel,L));
                
        }
    }*/

};

// Selection the best scale froma a pixel
int selectS(int x, int y, const int s[9], const RGB &pixel, float a, float L){

    int scale = 0;

    while (abs(V(x, y, s[scale], pixel, a,L)) >= THRESHOLD){

        scale++;
    }
    
    //std::cout << "scale: " << scale << std::endl;
    //std::cout << "V: " << V(x, y, s[scale], pixel, a) << std::endl;
    //std::cout << "a_1: " << ALPHA_1 << std::endl;
    //std::cout << "a_2: " << ALPHA_2 << std::endl;
    //std::cout << "scale: " << s[scale] << std::endl;
    return s[scale];
};

// calulate V value for a determinate scale
float V(int x, int y, int s, const RGB &pixel, float a, float L){

    //std::cout << "denominador: " << (V_i(x,y,s,ALPHA_1,pixel) - V_i(x,y,s,ALPHA_2,pixel))  << std::endl;
    //std::cout << "op 1: " << V_i(x,y,s,ALPHA_1,pixel) << std::endl;
    //std::cout << "op 2: " << V_i(x,y,s,ALPHA_2,pixel) << std::endl;
    return (V_i(x,y,s,ALPHA_1,pixel,L) - V_i(x,y,s,ALPHA_2,pixel,L)) / (((pow(2,FI) * a) / pow(s,2) ) + V_i(x,y,s,ALPHA_1,pixel,L));

};

// operator Vi in reinhard algorithm
float V_i(int x, int y, int s,float alpha, const RGB &pixel,float L){

    //std::cout << "L: " << pixel.L() << std::endl;
    //std::cout << "R_i: " << R_i(x, y, s, alpha) << std::endl;
    return L * R_i(x, y, s, alpha);

};

// operator Ri in reinhard algorithm
float R_i(int x, int y, int s,float alpha){

    //std::cout << "div: " << (1.0f /(M_PI * pow(alpha * s, 2.0f))) << std::endl;
    //std::cout << "expo: " << expf((-((pow(x,2) + pow(y,2)) / pow(alpha*s,2))) * (1.0f / (M_PI * pow(alpha * s, 2)))) << std::endl;
    //std::cout << "x: " << x << std::endl;
    //std::cout << "y: " << y << std::endl;
    //std::cout << "numerador: " << pow(x,2) + pow(y,2)  << std::endl;
    //std::cout << "denominador: " << pow(alpha*s,2) << std::endl;

    return expf((-((pow(x,2) + pow(y,2)) / pow(alpha*s,2))) * (1.0f / (M_PI * pow(alpha * s, 2))));
};