/*********************************************************************************
 * File
 *
 * File: file.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "file.hpp"
#include "error.hpp"

#include <cctype>

std::string createOutFilename(const std::string &file) {
    size_t i = file.find_last_of('/', file.length());

    i == std::string::npos ? i = 0 : i++;

    std::string outFile = file;
    return outFile.insert(i, OUT_ID);
}

bool checkFileExtension(const std::string &file, const std::string &ext) {
    std::string fileExt = "";
    size_t i = file.rfind('.', file.length());
    if (i != std::string::npos) {
        fileExt = file.substr(i + 1, file.length() - i);
    }
    return fileExt == ext;
}

namespace {
void readPPMComment(std::ifstream &is, float &max) {
    std::string comment;
    char p;
    // Eat whitespace
    while (p = is.peek(), std::isspace(p)) {
        is.get();
    }
    if (p == '#') {
        std::getline(is, comment);
        // Check if the comment is a max value declaration
        if (comment.substr(0, 5) == "#MAX=") {
            max = stof(comment.substr(5));
        }
        // Recursive call to read more comments
        readPPMComment(is, max);
    }
};
} // namespace

Image readPPM(std::string file) {
    if (!checkFileExtension(file, "ppm")) {
        ErrorExit("Input file must have .ppm extension");
    }

    std::ifstream is(file, std::ios::in);
    if (!is.is_open()) {
        ErrorExit("Could not open file");
    }

    int height, width, colorResolution;
    float max = 1;

    // Make sure that the file format is P3
    std::string format;
    is >> format;
    if (format != "P3") {
        ErrorExit("Invalid PPM file, the magic number should be 'P3'");
    }

    // Get width and height
    readPPMComment(is, max);
    is >> width >> height;
    if (width < 1) {
        ErrorExit("Unsupported width: ", width);
    }
    if (height < 1) {
        ErrorExit("Unsupported height: ", height);
    }

    // Get colorResolution
    readPPMComment(is, max);

    is >> colorResolution;
    if (colorResolution < 1) {
        ErrorExit("Unsupported color resolution: ", colorResolution);
    }

    // Read last block of comments
    readPPMComment(is, max);
    if (max < 1) {
        ErrorExit("Unsupported max value: ", max);
    }

    // Read RGB tuples row by row
    // Each tuple is mutiplied by this factor to get the real RGB value
    float f = max / colorResolution;
    // float f = 1 / colorResolution;

    std::vector<RGB> v(width * height);
    for (int i = 0; i < width * height; i++) {
        is >> v[i];
        v[i] = v[i] * f;
    }

    std::cout << colorResolution << " " << max << " " << width << " " << height << std::endl;
    is.close();
    return Image(v, colorResolution, max, width, height);
};

bool writePPM(const Image &img, const std::string file) {

    std::cout << img.width << " columnas" << std::endl;
    std::cout << img.height << " filas" << std::endl;
    std::cout << img.v.size() << " size" << std::endl;
    std::ofstream os(file, std::ios::out);
    if (!os.is_open()) {
        Error("Could not open file: ", file);
        return false;
    }

    os << "P3" << std::endl;
    os << img.width << " " << img.height << std::endl;
    os << "255" << std::endl;
    for (int i = 0; i < img.v.size(); i = i + img.width) {
        for (int n = 0; n < img.width; n++) {
            os << img.v[i + n];
            n == img.width - 1 ? os << std::endl : os << "   ";
        }
    }
    os.close();
    return true;
};
