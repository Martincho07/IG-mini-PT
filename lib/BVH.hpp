#pragma once

#include "AABB.hpp"
#include "geometry.hpp"
#include "shape.hpp"

#include <limits>
#include <vector>

struct BVH {
    AABB bb;
    std::vector<std::shared_ptr<Shape>> leaves;
    bool is_leaf;
    std::shared_ptr<BVH> left, right;

    // void get_primitives(vector<Object3D *> &objects);

    // BVH() : Shape(), left(0), right(0) {}
    BVH() {}

    BVH(std::vector<std::shared_ptr<Shape>> &shapes, int start, int end, int max_leaves);

    float intersect(Ray &ray, SurfaceInteraction &si) const;

    AABB bounding_box() const;

  private:
    // Returns the bounding box that surrounds the shapes
    void build_bounding_box(const std::vector<std::shared_ptr<Shape>> &shapes);

    /*
    void order_objects(vector<Object3D *> &objects) const;
    void split_objects(vector<Object3D *> &objects,
                       vector<Object3D *> &obj1, vector<Object3D *> &obj2) const;
  */
};
