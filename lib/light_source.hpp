/*********************************************************************************
 * Light sources
 *
 * File: light_source.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "color.hpp"
#include "geometry.hpp"
#include "scene.hpp"
#include "surface_interaction.hpp"

struct Scene;

struct LightSource {
    Scene *scene;
    RGB power;

    LightSource(Scene *_scene, RGB _power) : scene(_scene), power(_power) {}

    // Position of the light source
    virtual Point3 get_position() const = 0;

    // Returns true if the light is visible from p
    virtual bool is_visible(const Point3 &p) const = 0;

    // Returns the normalized incoming direction from light to p
    virtual Vector3 get_incoming_direction(const Point3 &p) const = 0;

    // Return the total incoming power from light to p
    virtual RGB get_incoming_light(const Point3 &p) const = 0;
};

struct PointLight : LightSource {
    Point3 position;

    PointLight(Scene *_scene, Point3 _position, RGB _power) : position(_position), LightSource(_scene, _power) {}

    Point3 get_position() const;
    bool is_visible(const Point3 &p) const;
    Vector3 get_incoming_direction(const Point3 &p) const;
    RGB get_incoming_light(const Point3 &p) const;
};
