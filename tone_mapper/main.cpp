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
#include <string>
#include <vector>

// Default values
#define STEP 0.0f
#define VALUE 1.0f
#define GAMMA 2.2f
#define A 0.16f
#define S 0.6f

void help() {
    std::cout << "Usage: tone_mapper input-file.ppm [options ...] [output-file.{ppm|hdr}]\n\n"
                 "Options:\n"
                 "  -exposure step      Multiply each pixel by 2^step to adjust the exposure\n"
                 "  -clamp              Discard al values greater than 255 (1 in floating point precission)\n"
                 "  -equalize           Linear transformation of all values from minimum to the maximum (normalization)\n"
                 "  -clamp-and-equalize value\n"
                 "                      Clamp all values greater than 'value' and equalize the rest of them\n"
                 "  -gamma-curve gamma  Apply a gamma curve to all the values\n"
                 "  -clamp-and-gamma-curve value gamma\n"
                 "                      Apply a gamma curve after clamping all the values greater than 'value'\n"
                 "  -reinhard02 a       Apply the Reinhard 2002 operator with a given 'a' key value\n"
                 "  -mantiuk08 a s      Apply the Mantiuk 2008 operator with a given 'a' key value and 's' value\n"
                 "  -h, -help           Show this help message and quit\n"
                 "\nUse the character 'D' to indicate the default value\n"
                 "Default values:\n"
                 "  step = 0\n"
                 "  value = 1\n"
                 "  gamma = 2.2\n"
                 "  a = 0.16\n"
                 "  s = 0.6\n"
                 "\nIf no output-file is provided, the image is saved as: out_'input-file'.ppm"
              << std::endl;
}

float getArgValue(int argc, char **argv, int i, float defaultValue) {
    float value = defaultValue;
    if (i + 1 >= argc || argv[i + 1][0] == '-') {
        ErrorExit("Missing value after ", argv[i], " argument");
    }
    if (!(std::string(argv[i + 1]) == "D")) {
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
    float step, value, gamma, a, s;

    if (argc <= 1) {
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
                operators.push_back(std::make_shared<Clamp>());
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
                operators.push_back(std::make_shared<Reinhard02>(a, logAverageLuminance(img), maxValue));
            } else if (arg == "-mantiuk08") {
                a = getArgValue(argc, argv, i, A);
                i++;
                s = getArgValue(argc, argv, i, S);
                i++;
                operators.push_back(std::make_shared<Mantiuk08>(a, s, logAverageLuminance(img), maxValue));
            } else if (arg == "-h" || arg == "-help") {
                help();
                return 0;
            } else {
                ErrorExit("Invalid option: ", arg);
            }
        } else {
            // file name
            outFile = arg;
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

<<<<<<< HEAD
    if (!inFile.empty()) {
        if (outFile.empty()) {
            outFile = createOutFilename(inFile);
        }

        std::cout << "Antes de procesar" << std::endl;
        std::cout << "inFile: " << inFile << " outFile: " << outFile << std::endl;
        std::cout << "clamp: " << clamp << std::endl;

        Image img = readPPM(inFile);
        maxValue = img.getMax();

        std::cout << "Seleccione el tone mapper a aplicar:" << std::endl;
        std::cout << "\t 1-Clamping. " << std::endl;
        std::cout << "\t 2-Equalization. " << std::endl;
        std::cout << "\t 3-Equalize and clamp. " << std::endl;
        std::cout << "\t 4-Gamma curve. " << std::endl;
        std::cout << "\t 5-Clamp and gamma curve. " << std::endl;
        std::cout << "\t 6-Reinhard 2002. " << std::endl;
        std::cout << "\t 7-Mantiuk 2008. " << std::endl;
        std::cin >> option;

        if (option == '1') {
            std::cout << "Applying clamping..." << std::endl;
            clampAndGammaCurve(img, 1.0f, 1.0f);

        } else if (option == '2') {
            std::cout << "Applying equalization..." << std::endl;
            clampAndGammaCurve(img, maxValue, 1.0f);

        } else if (option == '3') {
            std::cout << "Enter a value v = [0," << maxValue << "]" << std::endl;
            std::cin >> v;
            assert(v >= 0 && v <= maxValue);
            std::cout << "Applying equalize and clamp..." << std::endl;
            clampAndGammaCurve(img, v, 1.0f);
        
        } else if (option == '4'){
            std::cout << "Applying gamma curve..." << std::endl;
            clampAndGammaCurve(img, maxValue, 1.0f/2.2f);

        } else if (option == '5') {
            std::cout << "Enter a value v = [0," << maxValue << "]" << std::endl;
            std::cin >> v;
            assert(v >= 0 && v <= maxValue);
            std::cout << "Applying clamp and gamma curve..." << std::endl;
            clampAndGammaCurve(img, v, 1.0f/2.2f);

        } else if (option == '6') {
            std::cout << "Enter a value v = [0," << maxValue << "]" << std::endl;
            std::cin >> v;
            //assert(v >= 0 && v <= maxValue);
            std::cout << "Applying Reinhard 2002..." << std::endl;
            Reinhard(img, v);

        } else if (option == '7') {
            std::cout << "Enter a value v = [0," << maxValue << "]" << std::endl;
            std::cin >> v;
            assert(v >= 0 && v <= maxValue);
            std::cout << "Applying Mantiuk 2008..." << std::endl;
            Mantiuk(img, v,0.6f);

        } else {
            std::cout << "Opcion invalida" << std::endl;
            return 1;
        }

        writePPM(img, outFile);
=======
    // Create output filename in case is not given by the user
    if (outFile.empty()) {
        outFile = createOutFilename(inFile);
    }
>>>>>>> 8fe03c560fecc9f2f536abd6f6460a44411d73dd

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