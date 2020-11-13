//*****************************************************************
// File:   Semaphore_V2.h
// Author: PSCD-Unizar
// Date:   octubre 2016
// Coms:   Especificación de una clase de semáforos, extendida, con operaciones
//         "wait(nat)" y "signal(nat)"
//         El valor transmitido en la inicialización ha de ser
//         no negativo. Si fuera negativo, da error y aborta la ejecución.
//         La semántica que implementa es la que en
//         M. Ben-Ari, "Principles of Concurrent and Distributed Programming", Addison-Wesley, 2006
//         denomina "Busy-wait" (ver pág. 120)
//         Para los casos en que el uso del semáforo va a ser exclusivamente como "mutex", Cpp
//         suministra la clase "std::mutex", cuya especificación se encuentra en
//         http://en.cppreference.com/w/cpp/thread/mutex
//*****************************************************************

#pragma once

#include "Logger.hpp"
#include <assert.h>
#include <condition_variable>
#include <fstream>
#include <mutex>

struct Semaphore {

    std::mutex mtx; //los dos primeros atributos se entenderán al estudiar los monitores
    std::condition_variable_any cv;
    int count;        //natural asociado al semáforo
    bool initialized; //para manejar constructor genérico: ¿está inicializado?
    //si vamos a querer trabajar con información en un log
    Logger *logger;   //ya debería estar creado; aquí solo la referencia
    std::string name; //nombre que se asociará al semáforo para la información del "logger"
    bool withLog;     //¿se ha ejecutado el constructor log?

    //------------------------- constructores
    //Pre: n>=0
    //Post: count=n AND initialized AND NOT withLog
    //Coms: constructor "estándar", tal y como se ha contado en clases de teoría
    //      Ejemplo: "Semaphore s(2);"
    Semaphore(const int n) : count(n) {
        assert(n >= 0); //aborta si se viola la Pre

        initialized = true; //ya está inicializado
        withLog = false;
    };

    //Pre:
    //Post: NOT initialized AND NOT withLog
    //Coms: este constructor es no estándar. Se usará para los casos en que declaremos
    //      un array de semáforos, debiendo posteriormente ejecutar un "setInitiValue"
    //      Un intento de acceso a "wait" o "signal" sin ejecutar "setInitiValue" dará
    //      un error
    //      Ejemplo: "Semaphore s; s.setInitValue(2);" es equivalente a "Semaphore s(2);"
    Semaphore() {
        initialized = false; //habrá que inicializarlo
        withLog = false;
    };

    //Pre: n>=0
    //Post: count=n AND initialized AND this->logger=logger AND this->name=name AND withLog
    //Coms: esta es la versión del constructor "Semaphore(int n)" para el caso en que se desee
    //      que las invocaciones a "wait" y "signal" generen información para un fichero
    //      de log
    Semaphore(const int n, Logger *logger, std::string name) {

        assert(n >= 0);     //aborta si se viola la Pre
        initialized = true; //ya está inicializado
        std::cout << "inicializado" << std::endl;
        withLog = true;
        count = n;
        this->logger = logger;
        this->name = name;
    };

    //Pre:
    //Post: NOT initialized AND this->logger=logger AND this->name=name AND withLog
    //Coms: esta es la versión del constructor "Semaphore(int n, Logger &logger, string name)" para
    //      el caso en que se desee que las invocaciones a "wait" y "signal" generen información
    //      para un fichero de log
    Semaphore(Logger *logger, std::string name) {
        initialized = false; //habrá que inicializarlo
        withLog = true;
        this->logger = logger;
        this->name = name;
    };

    //------------------------- destructor
    //Pre:
    //Post:
    //Coms: se invoca de manera automática al cerrarse el bloque donde ha sido declarado
    ~Semaphore() {}

    //-------------------------
    //Pre:  n>=0 AND NOT initialized
    //Post: initialized AND count=n
    //Coms: Semáforos declarados con los constructores "Semaphore()" y "Semaphore(Logger &logger, string name)"
    //      requieren que se asigne, mediante este procedimiento, el valor inicial asociado al natural del semáforo
    void setInitValue(const int n) {
        std::unique_lock<std::mutex> lck(mtx); //mutex para atomicidad de la función

        assert(!initialized && n >= 0);

        count = n;
        initialized = true;
    }
    //------------------------- operaciones estándar
    //Pre: initialized
    //Post: <count++>
    //Coms: en el caso de semáforos con información de log, genera un evento en el fichero
    void signal() {
        std::unique_lock<std::mutex> lck(mtx);

        assert(initialized);

        count++;
        cv.notify_all(); //podemos cambiar la semántica con cv.notify_one()

        if (withLog) {
            logger->addMessage("SIGNAL," + name + "," + std::to_string(count));
        }
    }

    //Pre: initialized
    //Post: <await count>0
    //          count--
    //      >
    //Coms: en el caso de semáforos con información de log, genera un evento en el fichero
    void wait() {
        std::unique_lock<std::mutex> lck(mtx);

        assert(initialized);

        while (count == 0) {
            cv.wait(lck);
        }
        count--;

        if (withLog) {
            logger->addMessage("WAIT," + name + "," + std::to_string(count));
        }
    }

    //------------------------- operaciones extendidas
    //Pre: n>0 AND initialized
    //Post: <count=count+n>
    //Coms: en el caso de semáforos con información de log, genera un evento en el fichero
    void signal(const int n) {
        std::unique_lock<std::mutex> lck(mtx);

        assert(initialized && n > 0);

        count = count + n;
        cv.notify_all(); //podemos cambiar la semántica con cv.notify_one()

        if (withLog) {
            logger->addMessage("SIGNAL," + name + "," + std::to_string(count));
        }
    }

    //Pre: n>0 AND initialized
    //Post: <await count>=n
    //          count = count-n
    //      >
    //Coms: en el caso de semáforos con información de log, genera un evento en el fichero
    void wait(const int n) {
        std::unique_lock<std::mutex> lck(mtx);

        assert(initialized && n > 0);

        while (count < n) {
            cv.wait(lck);
        }
        count = count - n;

        if (withLog) {
            logger->addMessage("SIGNAL," + name + "," + std::to_string(count));
        }
    }

    //------------------------- operaciones extendidas
    //Pre:
    //Post: this->logger=logger AND this->name=name AND withLog
    void setLogInfo(Logger *logger, std::string name) {
        std::unique_lock<std::mutex> lck(mtx);

        this->logger = logger;
        this->name = name;
        withLog = true;
    }
};
