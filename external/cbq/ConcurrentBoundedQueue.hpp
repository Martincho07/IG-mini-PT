//*****************************************************************
// File:   ConcurrentBoundedQueue.hpp
// Author: PSCD-Unizar
// Date:   Octubre 2018
// Coms:   Especificación de una cola FIFO acotada con gestión de acceso concurrente
//*****************************************************************

#pragma once

#include "BoundedQueue.hpp"
#include "Logger.hpp"
#include "Semaphore_V2.hpp"
#include <cassert>
#include <iomanip>
#include <iostream>

template <typename T>
struct ConcurrentBoundedQueue {

    int N;
    BoundedQueue<T> *bq;   //"BoundedQueue" con los datos
    Logger *log;           //Para guardar información de log
                           //estructura para traducir el diseño mediante <await ...>
    Semaphore mutex;       //se deberá inicializar a 1 y pasarle (log,"mutex")
    Semaphore b_hay_hueco; //se deberá inicializar a 0 y pasarle (log,"b_hay_hueco")
    Semaphore b_hay_dato;  //se deberá inicializar a 0 y pasarle (log,"b_hay_dato")
    int d_hay_hueco;       //se deberán inicializar de acuerdo a la técnica propuesta
    int d_hay_dato;
    int complet_tasks;

    //-----------------------------------------------------
    //Pre:  0<N
    //Post: this->bq=< > AND #this=N AND this->log=nullptr
    //Com:  constructor
    //-----------------------------------------------------
    ConcurrentBoundedQueue(const int _N) : N(_N) {

        bq = new BoundedQueue<T>(_N);
        log = nullptr;
        mutex.setInitValue(1);
        b_hay_hueco.setInitValue(0);
        b_hay_dato.setInitValue(0);
        d_hay_hueco = 0;
        d_hay_dato = 0;
        complet_tasks = 0;
    };

    //-----------------------------------------------------
    //Pre:  0<N
    //Post: this->bq=< > AND #this=N AND this->log=log
    //Com:  constructor
    ConcurrentBoundedQueue(const int _N, Logger *log) : N(_N) {

        bq = new BoundedQueue<T>(_N);
        this->log = log;
        mutex.setInitValue(1);
        mutex.setLogInfo(this->log, "mutex");
        b_hay_hueco.setInitValue(0);
        b_hay_hueco.setLogInfo(this->log, "b_hay_hueco");
        b_hay_dato.setInitValue(0);
        b_hay_dato.setLogInfo(this->log, "b_hay_dato");
        d_hay_hueco = 0;
        d_hay_dato = 0;
        complet_tasks = 0;
    };

    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  destructor
    ~ConcurrentBoundedQueue() {
        delete bq;
    };

    //-----------------------------------------------------
    //Pre:
    //Post: this->bq=<>
    void empty() {
        this->bq->empty();
    };

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n >
    //Post: this->bq=< d_1 ... d_n d >
    //Coms: se bloquea hasta que haya un hueco para insertar el dato
    void enqueue(const T d) {
        // Espera sobre mutex para poder ejecutar en exclusión mutua del resto de código
        mutex.wait();
        if (bq->length() == bq->size()) {
            d_hay_hueco++;
            mutex.signal();
            // No caben elementos en la cola, el proceso se bloquea hasta que haya espacio
            b_hay_hueco.wait();
        }
        // Encolar <d>
        bq->enqueue(d);
        AVISAR();
    };

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n >
    //Post: this->bq=< d_2 ... d_n >
    //Coms: se bloquea hasta que haya un dato para desencolar
    void dequeue() {
        // Espera sobre mutex para poder ejecutar en exclusión mutua del resto de código
        mutex.wait();
        if (bq->length() == 0) {
            d_hay_dato++;
            mutex.signal();
            // No hay elementos en la cola, el proceso se bloquea hasta que haya
            b_hay_dato.wait();
        }
        // Desencolar un elemento
        bq->dequeue();
        AVISAR();
    };

    //-----------------------------------------------------
    //Pre:
    //Post: f=d_1
    //Coms: se bloquea hasta que this->bq=< d_1 ... d_n >
    void first(T &f) {
        // Espera sobre mutex para poder ejecutar en exclusión mutua del resto de código
        mutex.wait();
        if (bq->length() == 0) {
            d_hay_dato++;
            mutex.signal();
            // No hay elementos en la cola, el proceso se bloquea hasta que haya
            b_hay_dato.wait();
        }
        // Obtener el primero elemento de la cola y guardarlo en <f>
        f = bq->first();
        // NUEVO
        bq->dequeue();
        complet_tasks++;

        progreso();

        AVISAR();
    };

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n >
    //Post: l=n
    void length(int &l) {
        mutex.wait();
        l = bq->length();
        mutex.signal();
    };

    void num_complete(int &num) {
        mutex.wait();
        num = complet_tasks;
        mutex.signal();
    };

    //-----------------------------------------------------
    //Pre:
    //Post: s=#this->bq
    void size(int &s) {
        s = bq->size();
    };

    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  muestra la cola por la salida estándar, separando los elementos mediante comas
    void print() {
        mutex.wait();
        bq->print();
        mutex.signal();
    };

    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  muestra el progreso de tareas completadas
    void progreso() {
        // std::cout << "Completado " << complet_tasks << std::endl;
        std::cout
            << "\r\033[FCompleted: [" << std::fixed << std::setprecision(2) << 100 * (float)complet_tasks / N << "%]\n"
            << std::flush;
    };

    //-----------------------------------------------------
    //Pre:
    //Post: copy=this
    //Com:  Clonación de la cola
    void clone(ConcurrentBoundedQueue<T> &copy) {
        mutex.wait();
        this->bq->clone(copy->bq);
        mutex.signal();
    };

    //-----------------------------------------------------
    void AVISAR() {
        if (bq->length() < bq->size() && d_hay_hueco > 0) {
            d_hay_hueco--;
            b_hay_hueco.signal();
        } else if (bq->length() > 0 && d_hay_dato > 0) {
            d_hay_dato--;
            b_hay_dato.signal();
        } else {
            mutex.signal();
        }
    }
};
