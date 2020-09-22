/*********************************************************************************
 * Biblioteca
 *
 * Fichero:    coordinate.cpp
 * Autor:      Fernando Peña (NIA: 756012), Jose Daniel Subias Sarrato(NIA: 759533)
 * Fecha:      1/5/2020
 * Asignatura: Informática Gráfica, curso 2020-2021
 *
 **********************************************************************************/

#pragma once
#include "coordinate.hpp"

#include <iostream>

using namespace std;

// 1
HCoordinate c = createPoint(1, 2, 3);

// 2
HCoordinate c
createPoint(c, 1, 2, 3);

// 3
HCoordinate c
c.createPoint(1, 2, 3);


// operaciones
HCoordinate c = a * b;


HCoordinate operator*(HCoordinate &hc1, HCoordinate &hc2) {
    // operaciones
    return
}

HCoordinate createPoint(float x, float y, float z) {
    HCoordinate hc;
    hc.c[0] = x;
    hc.c[1] = y;
    hc.c[2] = z;
    hc.c[3] = 1;
    return hc;
};

void createPoint(HCoordinate &hc, float x, float y, float z) {
    hc.c[0] = x;
    hc.c[1] = y;
    hc.c[2] = z;
    hc.c[3] = 1;
};

void createDirection(HCoordinate &hc, float x, float y, float z) {
    hc.c[0] = x;
    hc.c[1] = y;
    hc.c[2] = z;
    hc.c[3] = 0;
};
