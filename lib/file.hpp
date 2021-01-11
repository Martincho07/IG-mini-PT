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
#include "shape.hpp"

#include <fstream>
#include <iostream>
#include <string>

#define OUT_ID "out_"
#define LDR_LIMIT 255

/*
 * Return a new filename with the format:
 * <path of file>OUT_ID<name of file>.<extension of file>
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
bool writePPM(Image &img, const std::string file, float max, int colorResolution);

/*
 * Read an image stored in memory as vector and create an uncompressed HDR RGBE file
 *
 * .hdr format:
 *
 * #?RADIANCE
 * FORMAT=32-bit_rle_rgbe
 * 
 * -Y <height> +X <width>
 * <r><g><b><e><r><g><b><e>...<r><g><b><e>
 *
 * Return true if the writting is successful
 */
bool writeHDR(const Image &img, const std::string file);

struct Triangle;

/*
 * Read a 3D object stored in a PLY file
 * Returns a list with the triangles that make up the object
 */
std::vector<Triangle> readPLY(const std::string file, const std::shared_ptr<Material> brdf = std::make_shared<LambertianDiffuse>(RGB(0.5, 0.5, 0.5)));
