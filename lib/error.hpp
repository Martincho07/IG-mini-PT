/*********************************************************************************
 * Error
 *
 * File: error.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include <iostream>
#include <ostream>

#include <execinfo.h>
#include <stdio.h>

// https : //stackoverflow.com/questions/29326460/how-to-make-a-variadic-macro-for-stdcout
inline void Println(std::ostream &os) {
    os << std::endl;
}

template <typename First, typename... Rest>
inline void Println(std::ostream &os, First &&first, Rest &&...rest) {
    os << std::forward<First>(first);
    Println(os, std::forward<Rest>(rest)...);
}

// Error reporting functions

template <typename... Args>
void Warning(Args... args) {
    std::cerr << "Warning: ";
    Println(std::cerr, std::forward<Args>(args)...);
}

template <typename... Args>
void Error(Args... args) {
    std::cerr << "Error: ";
    Println(std::cerr, std::forward<Args>(args)...);
}

template <typename... Args>
void ErrorExit(Args... args) {
    std::cerr << "Error: ";
    Println(std::cerr, std::forward<Args>(args)...);
    exit(1);
}

inline void Backtrace() {
    void *callstack[128];
    int i, frames = backtrace(callstack, 128);
    char **strs = backtrace_symbols(callstack, frames);
    for (i = 0; i < frames; ++i) {
        printf("%s\n", strs[i]);
    }
    free(strs);
}
