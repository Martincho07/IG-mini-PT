//*****************************************************************
// File:   BoundedQueue.hpp
// Author: PSCD-Unizar
// Date:   septiembre 2018
// Coms:   Especificación de una cola FIFO acotada.
//         Una cola será denotada como "< d_1 ... d_n >", de manera que "d_1"
//         hace referencia al primero de la cola (el dato más antiguo) y "d_n"
//         al último. "n>0" implicará que la cola es no vacía. "this" se referirá a la propia cola.
//         Denotaremos mediante "#this" el número máximo de elementos que puede contener.
//*****************************************************************
#pragma once

#include <cassert>
#include <iostream>
#include <string>

template <typename T>
struct BoundedQueue {

    int N;
    int nEl;
    T *data;
    int pri, sig;

    //-----------------------------------------------------
    //Pre:  0<N
    //Post: this=< > AND #this=N
    //Com:  constructor
    BoundedQueue(const int _N) : N(_N) { // Construir a partir del numero de elementos

        this->N = N;
        data = new T[N];
        empty();
    };
    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  destructor
    ~BoundedQueue() { // Destruir cola

        delete[] data;
    };
    //-----------------------------------------------------
    //Pre:
    //Post: this=<>
    void empty() { // inicializar vacia

        pri = 0;
        sig = 0;
        nEl = 0;
    };
    //-----------------------------------------------------
    //Pre:  this=< d_1 ... d_n > AND n<#this
    //Post: this=< d_1 ... d_n d >
    void enqueue(const T d) {

        assert(nEl < N); // No se pueden meter elemento a cola llena
        data[sig] = d;
        sig = (sig + 1) % N;
        nEl++;
    };
    //-----------------------------------------------------
    //Pre:  this=< d_1 ... d_n > AND 0<n
    //Post: this=< d_2 ... d_n >
    void dequeue() {

        assert(nEl > 0); // No se pueden sacar elementos de cola vacia
        pri = (pri + 1) % N;
        nEl--;
    };
    //-----------------------------------------------------
    //Pre:  this=< d_1 ... d_n > AND 0<n
    //Post: first()=d_1
    T first() {

        assert(nEl > 0); // No se puede sacar el primer elemento de cola vacia
        T f = data[pri];
        return f;
    };
    //-----------------------------------------------------
    //Pre:  this=< d_1 ... d_n >
    //Post: length()=n
    int length() { // numero de elementos

        return nEl;
    };
    //-----------------------------------------------------
    //Pre:
    //Post: size()=#this
    int size() { // tamaño de la cola (maximo de elementos)

        return N;
    };
    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  muestra la cola por la salida estándar, separando los elementos mediante comas, y salta de línea
    void print() { // muestra la cola por pantalla

        if (nEl > 0) {
            for (int i = 0; i < nEl - 1; i++) {
                std::cout << data[(pri + i) % N] << ",";
            }
            std::cout << data[(pri + nEl - 1) % N];
        }
        std::cout << std::endl;
    };
    //-----------------------------------------------------
    //Pre:
    //Post: copy=this
    //Com:  Clonación de la cola
    void clone(BoundedQueue<T> &copy) {

        assert(N == copy.N); // La cola tiene que tener el mismo tamaño que la que se quiere copiar

        // compañeros de la misma clase pueden acceder a elementos privados
        copy.nEl = nEl;
        copy.pri = pri;
        copy.sig = sig;
        for (int i = 0; i < N; i++) {
            copy.data[i] = data[i];
        }
    }
};
