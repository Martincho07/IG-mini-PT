/*********************************************************************************
 * BVH
 *
 * File: BVH.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

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

BVH::BVH(std::vector<std::shared_ptr<Shape>> &shapes, int start, int end, int max_leaves) {

    assert(max_leaves >= 1);

    // Create the hierarchy

    // First, construct the bounding box that surrounds all the shapes between start and end
    std::vector<std::shared_ptr<Shape>> subv = std::vector<std::shared_ptr<Shape>>(shapes.begin() + start, shapes.begin() + end);
    build_bounding_box(subv);

    // Choose the comparator depending on the largest dimension
    int axis = bb.max_axis();
    auto comparator = (axis == 0)   ? x_compare_box
                      : (axis == 1) ? y_compare_box
                                    : z_compare_box;

    int size = end - start;
    int mid = start + (size + 1) / 2;

    // If the shapes vector already has max_leaves elements, those are the leaves
    if (size <= max_leaves) {
        is_leaf = true;
        leaves = subv;
    } else {
        is_leaf = false;
        // size is greater than or equal to 2

        // Divide by the shapes by the median
        std::nth_element(shapes.begin() + start,
                         shapes.begin() + mid,
                         shapes.begin() + end,
                         comparator);

        // Every element less than or equal to the median goes to the left
        left = std::make_shared<BVH>(shapes, start, mid, max_leaves);

        // Every element greater than the median goes to the right
        right = std::make_shared<BVH>(shapes, mid, end, max_leaves);
    }
}

void BVH::build_bounding_box(const std::vector<std::shared_ptr<Shape>> &shapes) {
    bb = AABB();
    for (auto shape : shapes) {
        AABB sb = shape->bounding_box();
        bb = union_box(bb, shape->bounding_box());
    }
}

float BVH::intersect(const Ray &ray, SurfaceInteraction &si) const {
    // If the ray doesn't intersect with the bouding box, there is no intersection
    if (!bb.intersect(ray)) {
        // ErrorExit("Entrado no interseca")
        return false;
    }

    // If it's a leave node, try to intersect with each element
    if (is_leaf) {
        return shapes_first_intersection(leaves, ray, si);
    }

    // Internal node

    SurfaceInteraction sileft;
    SurfaceInteraction siright;

    bool hit_left = left->intersect(ray, sileft);
    bool hit_right = right->intersect(ray, siright);

    // If the ray hit with both childs, return the one that has lower t
    // If the ray only hit one of them, return it
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
