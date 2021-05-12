/*********************************************************************************
 * Integrator
 *
 * File: integrator.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "camera.hpp"
#include "color.hpp"
#include "scene.hpp"

class Integrator {
  protected:
    std::shared_ptr<Camera> camera;

  public:
    Integrator(std::shared_ptr<Camera> _camera) : camera(_camera) {}
    virtual RGB render(float x, float y, const Scene &scene) const = 0;
};

class PathTracingIntegrator : public Integrator {
  public:
    PathTracingIntegrator(std::shared_ptr<Camera> _camera) : Integrator(_camera) {}
    RGB render(float x, float y, const Scene &scene) const;
};

class RayTracingIntegrator : public Integrator {
  public:
    RayTracingIntegrator(std::shared_ptr<Camera> _camera) : Integrator(_camera) {}
    RGB render(float x, float y, const Scene &scene) const;
};

class NormalMapIntegrator : public Integrator {
  public:
    NormalMapIntegrator(std::shared_ptr<Camera> _camera) : Integrator(_camera) {}
    RGB render(float x, float y, const Scene &scene) const;
};
