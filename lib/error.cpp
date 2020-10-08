/*********************************************************************************
 * Error
 *
 * File: error.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "error.hpp"

#include <iostream>

namespace {
void processError(const char *errorType, const char *message) {
    std::cerr << errorType << ": " << message << std::endl;
}
} // namespace

void Warning(const char *message) {
    processError("Warning", message);
}

// void Error(const char *message) {
//     processError("Error", message);
// }
