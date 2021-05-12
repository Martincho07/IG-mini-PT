/*********************************************************************************
 * main
 *
 * File: main.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "error.hpp"
#include "file.hpp"
#include "image.hpp"
// #include "tone_mapping.hpp"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Default values
#define STEP 1.0f
#define VALUE 1.0f
#define GAMMA 2.2f
#define A 0.16f
#define L 0.7f
#define S 0.6f

void help() {
    std::cout << "Usage: tone_mapper input-file.ppm [options ...] [output-file.{ppm|hdr}]\n\n"
                 "Options:\n"
                 "  -exposure STEP        Multiply each pixel by 2^STEP to adjust the exposure\n"
                 "  -clamp                Discard all values greater than 255 (1 in floating point precision)\n"
                 "  -equalize             Linear transformation of all values from minimum to the maximum (normalization)\n"
                 "  -clamp-and-equalize VALUE\n"
                 "                        Clamp all values greater than VALUE and equalize the rest of them\n"
                 "  -gamma-curve GAMMA    Apply a gamma curve to all the values\n"
                 "  -clamp-and-gamma-curve VALUE GAMMA\n"
                 "                        Apply a gamma curve after clamping all the values greater than VALUE\n"
                 "  -reinhard02 A L       Apply the Reinhard 2002 operator with a given A key value and L value\n"
                 "  -mantiuk08 A S        Apply the Mantiuk 2008 operator with a given A key value and S value\n"
                 "  -?, -h, -help         Show this help message and quit\n"
                 "\nUse the string 'default' as argument value to use the default value\n"
                 "Default values:\n"
                 "  STEP = 1\n"
                 "  VALUE = 1\n"
                 "  GAMMA = 2.2\n"
                 "  A = 0.16\n"
                 "  L = 0.7\n"
                 "  S = 0.6\n"
                 "\nIf no output-file is provided, the image is saved as: out_'input-file'.ppm"
              << std::endl;
}

float getArgValue(int argc, char **argv, int i, float defaultValue) {
    float value = defaultValue;
    if (i + 1 >= argc || argv[i + 1][0] == '-') {
        ErrorExit("Missing value after ", argv[i], " argument");
    }
    if (!(std::string(argv[i + 1]) == "default")) {
        try {
            value = std::stof(argv[i + 1]);
        } catch (std::invalid_argument e) {
            ErrorExit("The option value must be a real number: ", argv[i + 1]);
        }
    }
    return value;
}

int main(int argc, char **argv) {
    std::string inFile;
    std::string outFile;

    FileFormat outFileFormat = PPM;

    // List of operators that will be applied
    std::vector<std::shared_ptr<ToneMappingOperator>> operators;

    // Values
    float step, value, gamma, a, s, l;

    if (argc <= 1 || argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "-help" || std::string(argv[1]) == "-?")) {
        help();
        return 0;
    }

    // Get input-file
    if (argv[1][0] == '-') {
        ErrorExit("Missing input file");
    } else {
        inFile = argv[1];
        if (!checkFileExtension(inFile, "ppm")) {
            ErrorExit("Unsupported extension for input file: ", inFile);
        }
    }

    std::cout << "Reading input file... " << std::flush;

    Image img = readPPM(inFile);
    // Maximum float value in the image
    float maxValue = max(img);
    float maxLuma = maxLum(img);

    // Process options
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            if (arg == "-exposure") {
                step = getArgValue(argc, argv, i, STEP);
                i++;
                operators.push_back(std::make_shared<Exposure>(step));
                // img.applyToneMappingOperator(Exposure(step));
                // std::cout << "Aplicando antes" << std::endl;
            } else if (arg == "-clamp") {
                operators.push_back(std::make_shared<Clamp>(1.0f));
            } else if (arg == "-equalize") {
                operators.push_back(std::make_shared<Equalize>(maxValue));
            } else if (arg == "-clamp-and-equalize") {
                value = getArgValue(argc, argv, i, VALUE);
                i++;
                operators.push_back(std::make_shared<ClampAndEqualize>(value));
            } else if (arg == "-gamma-curve") {

                gamma = getArgValue(argc, argv, i, GAMMA);
                i++;
                operators.push_back(std::make_shared<GammaCurve>(maxValue, gamma));
            } else if (arg == "-clamp-and-gamma-curve") {
                value = getArgValue(argc, argv, i, VALUE);
                i++;
                gamma = getArgValue(argc, argv, i, GAMMA);
                i++;
                operators.push_back(std::make_shared<ClampAndGammaCurve>(value, gamma));
            } else if (arg == "-reinhard02") {
                a = getArgValue(argc, argv, i, A);
                i++;
                l = getArgValue(argc, argv, i, L);
                i++;
                std::cout << "luma: " << maxLuma << std::endl;
                operators.push_back(std::make_shared<Reinhard02>(a, logAverageLuminance(img), l * maxLuma));
            } else if (arg == "-mantiuk08") {
                a = getArgValue(argc, argv, i, A);
                i++;
                s = getArgValue(argc, argv, i, S);
                i++;
                operators.push_back(std::make_shared<Mantiuk08>(a, s, logAverageLuminance(img), maxValue));
            } else if (arg == "-h" || arg == "-help" || arg == "-?") {
                help();
                return 0;
            } else {
                ErrorExit("Invalid option: ", arg);
            }
        } else {
            // file name
            outFile = arg;
            if (checkFileExtension(outFile, "")) {
                outFile += ".ppm";
            }
            if (checkFileExtension(outFile, "ppm")) {
                outFileFormat = PPM;
            } else if (checkFileExtension(outFile, "hdr")) {
                outFileFormat = HDR;
            } else {
                ErrorExit("Unsupported extension for output file: ", outFile);
            }
            break;
        }
    }

    // Create output filename in case is not given by the user
    if (outFile.empty()) {
        outFile = createOutFilename(inFile);
    }

    // Apply operators
    for (int i = 0; i < operators.size(); i++) {

        img.applyToneMappingOperator(*operators[i]);
    }

    // Write output file
    std::cout << "Writing output file..." << std::endl;
    switch (outFileFormat) {
    case PPM:
        writePPM(img, outFile, max(img), LDR_LIMIT);
        break;
    case HDR:
        writeHDR(img, outFile);
        break;
    default:
        break;
    }

    return 0;
}
