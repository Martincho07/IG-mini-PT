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
#include <memory>

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
    // if (MAX < 1) {
    //     ErrorExit("Unsupported max value: ", MAX);
    // }

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

    std::cout << "Loaded PPM file: " << file << ", [" << width << "px x " << height << "px], color res: " << colorResolution
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

    std::cout << "Written PPM file: " << file << std::endl;
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

    std::cout << "Written HDR file: " << file << std::endl;
    return true;
}

std::vector<Triangle> readPLY(const std::string file, std::shared_ptr<Material> brdf) {

    if (!checkFileExtension(file, "ply")) {
        ErrorExit("Input file must have .ply extension");
    }

    std::ifstream is(file, std::ios::in);
    if (!is.is_open()) {
        ErrorExit("Could not open file: ", file);
    }

    // Make sure that the file format is ply
    std::string keyword;

    is >> keyword;
    if (keyword != "ply") {
        ErrorExit("Invalid PPM file, the magic number should be 'P3'");
    }

    // Read format line
    std::string type, version;
    is >> keyword >> type >> version;
    if (keyword != "format") {
        ErrorExit("Missing file PLY format line");
    }
    if (type != "ascii") {
        ErrorExit("Unsupported PLY type: ", type);
    }
    if (version != "1.0") {
        ErrorExit("Unsupported PLY version: ", version);
    }

    // Read until 'end_header'
    std::string line;
    int numVerts, numFaces;
    bool smooth = false;
    is >> keyword;
    while (!is.eof() && keyword != "end_header") {
        if (keyword == "comment") {
            // ignore the rest of the line
            std::getline(is, line);
        } else if (keyword == "element") {
            std::string elementType;
            is >> elementType;
            // std::cout << "elementType: " << elementType << std::endl;
            if (elementType == "vertex") {
                is >> numVerts;
                // std::cout << numVerts << std::endl;
                is.ignore(256, '\n');

                // Vertex information
                std::string px, py, pz;
                std::getline(is, px);
                // std::cout << px << std::endl;
                std::getline(is, py);
                // std::cout << py << std::endl;
                std::getline(is, pz);
                // std::cout << pz << std::endl;
                if (px != "property float x" ||
                    py != "property float y" ||
                    pz != "property float z") {
                    ErrorExit("Unsupported vertex properties");
                }

                // Check if the model has vertex normals
                int position = is.tellg();
                std::getline(is, px);
                std::getline(is, py);
                std::getline(is, pz);
                // std::cout << px << std::endl;
                // std::cout << py << std::endl;
                // std::cout << pz << std::endl;
                if (px != "property float nx" ||
                    py != "property float ny" ||
                    pz != "property float nz") {
                    is.seekg(position);
                } else {
                    // std::cout << "smooth";
                    smooth = true;
                }

                // TODO: Check for aditional UV mapping data
            } else if (elementType == "face") {
                is >> numFaces;
                std::string pf;
                is.ignore(256, '\n');
                std::getline(is, pf);
                // std::cout << numFaces << " " << pf << std::endl;
                if (pf != "property list uchar uint vertex_indices" && pf != "property list uchar int vertex_indices") {
                    // std::cout << numFaces << " " << pf << std::endl;
                    ErrorExit("Unsupported face properties");
                }
            } else {
                // std::cout << numVerts << " " << numFaces << std::endl;
                ErrorExit("Unsupported element type in PLY file: ", elementType);
            }
        } else {
            ErrorExit("Unsupported keyword in PLY file: ", keyword);
        }
        is >> keyword;
    }

    if (is.eof()) {
        ErrorExit("Data section on the PLY file is empty");
    }

    if (numVerts == 0 || numFaces == 0) {
        ErrorExit("Invalid PLY header");
    }

    std::cout << "Loaded PLY file: " << file
              << ", vertices: " << numVerts << ", faces: " << numFaces
              << (smooth ? " (smooth)" : " (not smooth)") << std::endl;

    // Read vertices info
    std::vector<Point3> vertices;
    std::vector<Vector3> vertexNormals;

    if (!smooth) {
        for (int i = 0; i < numVerts; i++) {
            float x, y, z;
            is >> x >> y >> z;
            vertices.push_back(Point3(x, y, z));
            // std::cout << vertices[i] << std::endl;
        }
    } else {
        for (int i = 0; i < numVerts; i++) {
            float x, y, z, nx, ny, nz;
            is >> x >> y >> z >> nx >> ny >> nz;
            vertices.push_back(Point3(x, y, z));
            vertexNormals.push_back(Vector3(nx, ny, nz));
            // std::cout << vertices[i] << std::endl;
        }
    }

    // Read faces info
    // Each face is a triangle that connects 3 vertices
    std::vector<Triangle> faces;

    int fSize;
    for (int i = 0; i < numFaces; i++) {
        // Read number of vertices of the polygon
        is >> fSize;
        if (fSize != 3) {
            ErrorExit("Unsupported list size: ", fSize, ". Only triangles are supported");
        }
        // These are the indexes of the vertices in the previous vector
        float a, b, c;
        is >> a >> b >> c;
        if (!smooth) {
            faces.push_back(Triangle(vertices[a], vertices[b], vertices[c], brdf));
        } else {
            faces.push_back(Triangle(vertices[a], vertices[b], vertices[c],
                                     vertexNormals[a], vertexNormals[b], vertexNormals[c], brdf));
        }
        // std::cout << a << " " << b << " " << c << " " << std::endl;
    }

    // std::cout << faces[1522].v1 << " " << faces[1522].v2 << " " << faces[1522].v3 << std::endl;
    // std::cout << faces[755].v1 << " " << faces[755].v2 << " " << faces[755].v3 << std::endl;

    // std::cout << "Terminado de leer PLY" << std::endl;
    // std::cout << "Numero de triangulos: " << faces.size() << std::endl;

    // TODO: Mirar cómo hacer lo del color
    return faces;
}
