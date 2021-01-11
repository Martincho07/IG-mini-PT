#include "BVH.hpp"
#include "error.hpp"

// Box comparing functions
// https://raytracing.github.io/books/RayTracingTheNextWeek.html
inline bool compare_box(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b, int axis) {
    AABB bb_a = a->bounding_box();
    AABB bb_b = b->bounding_box();

    return bb_a.pmin[axis] < bb_b.pmin[axis];
}

bool x_compare_box(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
    return compare_box(a, b, 0);
}

bool y_compare_box(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
    return compare_box(a, b, 1);
}

bool z_compare_box(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
    return compare_box(a, b, 2);
}

// constructor
BVH::BVH(std::vector<std::shared_ptr<Shape>> &shapes, int start, int end, int max_leaves) {
    //Shape();

    assert(max_leaves >= 1);

    // Crear la jerarquía

    // Primero se construye la bounding box
    std::vector<std::shared_ptr<Shape>> subv = std::vector<std::shared_ptr<Shape>>(shapes.begin() + start, shapes.begin() + end);
    build_bounding_box(subv);

    Error("bounding box", bb.pmin, ", ", bb.pmax);
    // std::cout << "bounding box: " << bb.pmin << ", " << bb.pmax << std::endl;

    // Elegir el comparador dependiendo de la dimensión
    int axis = bb.max_axis();
    auto comparator = (axis == 0)   ? x_compare_box
                      : (axis == 1) ? y_compare_box
                                    : z_compare_box;

    int size = end - start;
    int mid = start + (size + 1) / 2;

    // Si el vector de shapes ya tiene max_leaves elementos, estas son las hojas
    if (size <= max_leaves) {
        is_leaf = true;
        std::cout << size << std::endl;
        leaves = subv;
    } else {
        is_leaf = false;
        // Seguro que el size es mayor o igual que 2

        // ErrorExit("Entrado no hoja");

        // Dividir por la mediana
        std::nth_element(shapes.begin() + start,
                         shapes.begin() + mid,
                         shapes.begin() + end,
                         comparator);

        // Todos los elementos menores o iguales que la mediana van a la izquierda
        left = std::make_shared<BVH>(shapes, start, mid, max_leaves);

        // Todos los elementos mayores que la mediana van a la derecha
        right = std::make_shared<BVH>(shapes, mid, end, max_leaves);
    }
}

void BVH::build_bounding_box(const std::vector<std::shared_ptr<Shape>> &shapes) {
    bb = AABB();
    for (auto shape : shapes) {
        AABB sb = shape->bounding_box();
        // std::cout << sb.pmin << ", " << sb.pmax << std::endl;
        bb = union_box(bb, shape->bounding_box());
    }
    // std::cout << "Bounding box al final" << bb.pmin << ", " << bb.pmax << std::endl;
}

float BVH::intersect(const Ray &ray, SurfaceInteraction &si) const {
    // Si no se interseca con la bounding box, no hay intersección
    if (!bb.intersect(ray)) {
        // ErrorExit("Entrado no interseca")
        return false;
    }

    // Si es un nodo hoja, realizar la intersección con los elementos
    if (is_leaf) {
        return shapes_first_intersection(leaves, ray, si);
    }

    // Es un nodo intermedio
    // std::cout << "Entrado" << std::endl;

    SurfaceInteraction sileft;
    SurfaceInteraction siright;

    bool hit_left = left->intersect(ray, sileft);
    bool hit_right = right->intersect(ray, siright);

    // Si han chocado los dos, devolver el que tiene t más pequeño
    // Si ha chocado sólo uno, devolver ese
    if (hit_left && hit_right) {
        si = sileft.t < siright.t ? sileft : siright;
        return true;
    } else if (hit_left) {
        si = sileft;
        return true;
    } else if (hit_right) {
        si = siright;
        return true;
    }

    return false;
}

AABB BVH::bounding_box() const {
    return bb;
}
