/*********************************************************************************
 * main
 *
 * File: ray_tracer.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "camera.hpp"
#include "geometry.hpp"
#include "shape.hpp"
#include <vector>
#include "image.hpp"
#include "file.hpp"
#include "color.hpp"

int main(int argc, char** argv){

    int width = 6;
    int height = 6;

    float acum_width = -1.0f + (1.0f / width);
    float acum_height = 1.0f - (1.0f / height);
    std::vector<Shape> scene;
    Plane p(RGB(50.0f, 70.0f, 255.0f), Vector3(1.0f,0.0f,0.0f), 5.0f); 
    scene.push_back(p);

    Image image;

    Camera c = Camera(Point3(0.0f,0.0f,0.0f), Vector3(1.0f,0.0f,0.0f), Vector3(0.0f,1.0f,0.0f),Vector3(0.0f,0.0f,1.0f));

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){

            image.v.push_back(c.GenerateRay(normalize((Vector3(acum_width,acum_height,1.0f))), scene));            
            acum_width += 1.0f / (2.0f * width);
        }
        acum_width = -1.0f + (1.0f / width);
        acum_height -= 1.0f / (2.0f * height);
    }

    writePPM(image, "salida.ppm", max(image), 10000000);

};