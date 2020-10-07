/*********************************************************************************
 * File
 *
 * File: file.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "image.hpp"

#include <fstream>
#include <iostream>
#include <string>

#define OUT_ID "out_"

/*
 * Add OUT_ID to the beggining of the name of <file>
 */
std::string createOutFilename(const std::string &file);

/*
 * Return true if the file extension of <file> is equal to <ext>
 */
bool checkFileExtension(const std::string &file, const std::string &ext);

/*
 * Read an image stored in a modified PPM format for representing HDR images
 *
 * Modified .ppm format:
 *
 * P3
 * #MAX=<max>
 * <width> <heigth>
 * <colorResolution>
 * <r> <g> <b>     <r> <g> <b> ...
 * <r> <g> <b>     <r> <g> <b> ...
 * ...
 *
 * Lines starting with # are considered comments
 * With the #MAX=<max> comment it's posible to indicate
 * the real maximum of the image as a real number, in case
 * it's different to 1.
 *
 * Return true if the reading is successful
 */
Image readPPM(const std::string file);

/*
 * Read an image stored in memory as vector and create a PPM file
 *
 * .ppm format:
 *
 * P3
 * <width> <heigth>
 * 255
 * <r> <g> <b> ... <r> <g> <b>
 * <r> <g> <b> ... <r> <g> <b>
 *     ...             ...
 * <r> <g> <b> ... <r> <g> <b>
 *
 * The color resolution is always 255
 *
 * Return true if the writting is successful
 */
bool writePPM(const Image &img, const std::string file);
