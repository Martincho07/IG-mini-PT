/*********************************************************************************
 * BVH
 *
 * File: BVH.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

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

    BVH() {}

    BVH(std::vector<std::shared_ptr<Shape>> &shapes, int start, int end, int max_leaves);

    float intersect(const Ray &ray, SurfaceInteraction &si) const;

    AABB bounding_box() const;

  private:
    // Returns the bounding box that surrounds all the shapes
    void build_bounding_box(const std::vector<std::shared_ptr<Shape>> &shapes);
};
