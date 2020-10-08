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

// Error reporting
void Warning(const char *message);
// void Error(const char *message);
// void ErrorExit(const char *message);

template <typename Arg, typename... Args>
void ErrorExit(Arg &&arg, Args &&... args) {
    std::cerr << std::forward<Arg>(arg);
    using expander = int[];
    (void)expander{0, (void(std::cerr << ',' << std::forward<Args>(args)), 0)...};
    std::cerr << std::endl;
    exit(0);
}

template <typename Arg, typename... Args>
void Error(Arg &&arg, Args &&... args) {
    std::cerr << std::forward<Arg>(arg);
    using expander = int[];
    std::cerr << std::endl;
    (void)expander{0, (void(std::cerr << ',' << std::forward<Args>(args)), 0)...};
}
