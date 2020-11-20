/*********************************************************************************
 * Pixel
 *
 * File: pixel.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

struct Pixel {

    float x_min, x_max, y_min, y_max;
    int fila, columna;

    Pixel(int _fila, int _columna, float _x_min, float _x_max, float _y_min, float _y_max) : fila(_fila), columna(_columna), x_min(_x_min), x_max(_x_max), y_min(_y_min), y_max(_y_min){};
    Pixel(){};
};