/*********************************************************************************
 * Biblioteca
 *
 * Fichero:    coordinate.hpp
 * Autor:      Fernando Peña (NIA: 756012), Jose Daniel Subias Sarrato(NIA: 759533)
 * Fecha:      22/10/2020
 * Asignatura: Informática Gráfica, curso 2020-2021
 **********************************************************************************/

#pragma once
#include <iostream>
using namespace std;

struct HCoordinate;
void funcion();

void createPoint(HCoordinate &hc, float x, float y, float z);
void createDirection(HCoordinate &hc, float x, float y, float z);

struct HCoordinate {
    friend void funcion();
    friend void createPoint(HCoordinate & hc, float x, float y, float z);
    friend void createDirection(HCoordinate & hc , float x, float y, float z);

    private:
        float c[4];
};
