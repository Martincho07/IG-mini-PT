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
#include <iomanip>

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
        ErrorExit("Could not open file: ", file);
    }

    int height, width, colorResolution;
    float MAX = 1;

    // Make sure that the file format is P3
    std::string format;
    is >> format;
    if (format != "P3") {
        ErrorExit("Invalid PPM file, the magic number should be 'P3'");
    }

    // Get width and height
    readPPMComment(is, MAX);
    is >> width >> height;
    if (width < 1) {
        ErrorExit("Unsupported width: ", width);
    }
    if (height < 1) {
        ErrorExit("Unsupported height: ", height);
    }

    // Get colorResolution
    readPPMComment(is, MAX);

    is >> colorResolution;
    if (colorResolution < 1) {
        ErrorExit("Unsupported color resolution: ", colorResolution);
    }

    // Read last block of comments
    readPPMComment(is, MAX);
    if (MAX < 1) {
        ErrorExit("Unsupported max value: ", MAX);
    }

    // Read RGB tuples row by row
    // Each tuple is mutiplied by this factor to get the real RGB value
    float f = MAX / colorResolution;
    // float f = 1 / colorResolution;

    std::vector<RGB> v(width * height);
    for (int i = 0; i < width * height; i++) {
        is >> v[i];
        v[i] = v[i] * f;
    }

    Image img = Image(v, width, height);

    std::cout << "[" << width << "px x " << height << "px], color res: " << colorResolution
              << ", max value: " << MAX
              << ", range: [" << min(img) << ", " << max(img) << "]" << std::endl;

    is.close();
    return img;
};

bool writePPM(Image &img, const std::string file, float max, int colorResolution) {

    float m;
    std::ofstream os(file, std::ios::out);
    if (!os.is_open()) {
        Error("Could not open file: ", file);
        return false;
    }

    // HEADER
    os << "P3" << std::endl;
    os << "#MAX=" << max << std::endl;
    os << img.width << " " << img.height << std::endl;
    os << colorResolution << std::endl;

    // PIXEL DATA

    // Each pixel is multiplied before being stored
    float f = colorResolution / max;

    for (int i = 0; i < img.v.size(); i = i + img.width) {
        for (int n = 0; n < img.width; n++) {
            os << std::fixed << std::setprecision(0) << round(img.v[i + n] * f);
            n == img.width - 1 ? os << std::endl : os << "   ";
        }
    }
    os.close();
    return true;
};

bool writeHDR(const Image &img, const std::string file) {
    std::ofstream os(file, std::ios::out);
    if (!os.is_open()) {
        Error("Could not open file: ", file);
        return false;
    }

    // HEADER
    os << "#?RADIANCE" << std::endl;
    os << "FORMAT=32-bit_rle_rgbe" << std::endl;

    // RESOLUTION
    os << std::endl;
    os << "-Y " << img.height << " +X " << img.width << std::endl;

    // PIXEL DATA
    for (int i = 0; i < img.v.size(); i = i + img.width) {
        for (int n = 0; n < img.width; n++) {
            unsigned char rgbe[4];
            float2rgbe(img.v[i + n], rgbe);
            os << rgbe[0] << rgbe[1] << rgbe[2] << rgbe[3];
        }
    }
    return true;
}
