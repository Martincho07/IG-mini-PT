/*********************************************************************************
 * Tone mapping operands
 *
 * File: transform.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 21/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "color.hpp"
#include <iostream>

class ToneMappingOperator {
  public:
    ToneMappingOperator(){};
    virtual ~ToneMappingOperator(){};
    virtual RGB operator()(const RGB &c) const = 0;

    virtual std::ostream &format(std::ostream &op) const = 0;
    friend std::ostream &operator<<(std::ostream &os, const ToneMappingOperator &op) {
        return op.format(os);
    }
};

class Exposure : public ToneMappingOperator {
  private:
    float step;

  public:
    Exposure(float _step) : step(_step){};
    ~Exposure(){};
    RGB operator()(const RGB &c) const override;
    std::ostream &format(std::ostream &op) const override;
};

class Clamp : public ToneMappingOperator {
  public:
    float value;
    Clamp(float _value) : value(_value){};
    ~Clamp(){};
    RGB operator()(const RGB &c) const override;
    std::ostream &format(std::ostream &op) const override;
};

class Equalize : public ToneMappingOperator {
  public:
    float value;
    Equalize(float _value) : value(_value){};
    ~Equalize(){};
    RGB operator()(const RGB &c) const override;
    std::ostream &format(std::ostream &op) const override;
};

class ClampAndEqualize : public ToneMappingOperator {

  public:
    Clamp clamping;
    Equalize equalization;
    ClampAndEqualize(float _value)
        : clamping(_value), equalization(_value){};
    ~ClampAndEqualize(){};
    RGB operator()(const RGB &c) const override;
    std::ostream &format(std::ostream &op) const override;
};

class GammaCurve : public ToneMappingOperator {

  public:
    Equalize equalization;
    float gamma, inv_gamma;
    GammaCurve(float _value, float _gamma)
        : equalization(_value), gamma(_gamma), inv_gamma(1.0f / _gamma){};
    ~GammaCurve(){};
    RGB operator()(const RGB &c) const override;
    std::ostream &format(std::ostream &op) const override;
};

class ClampAndGammaCurve : public ToneMappingOperator {

  public:
    GammaCurve gamma_curve;
    Clamp clamping;
    ClampAndGammaCurve(float _value, float _gamma)
        : clamping(_value), gamma_curve(_value, _gamma){};
    ~ClampAndGammaCurve(){};
    RGB operator()(const RGB &c) const override;
    std::ostream &format(std::ostream &op) const override;
};

class Reinhard02 : public ToneMappingOperator {
    // White preserving luminance based Reinhard
  private:
    // Factor that depends on the key of the image
    // Normal image: 0.18
    // Vary up to: 0.36 and 0.72
    // Vary down to: 0.09 0.045
    float a;
    // Log average world luminance of the image
    float avg_L_w;
    // Smallest luminance that will be mapped to white
    float white_L;
    Clamp clamping;

  public:
    Reinhard02(float _a, float _avg_L_w, float _white_L)
        : a(_a), avg_L_w(_avg_L_w), white_L(_white_L), clamping(1.0f){};
    ~Reinhard02(){};
    RGB operator()(const RGB &c) const override;
    std::ostream &format(std::ostream &op) const override;
};

class Mantiuk08 : public ToneMappingOperator {
  private:
    float a, s, avg_L_w, min_L;

  public:
    Mantiuk08(float _a, float _s, float _avg_L_w, float _min_L)
        : a(_a), s(_s), avg_L_w(_avg_L_w), min_L(_min_L){};
    ~Mantiuk08(){};
    RGB operator()(const RGB &c) const override;
    std::ostream &format(std::ostream &op) const override;
};
