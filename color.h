// Copyright 2018, Vahid Kazemi

#ifndef COLOR_H_
#define COLOR_H_

#include <math.h>
#include <stdint.h>

#include "./math.h"
#include "./vec3.h"
#include "./vec4.h"

struct RGBA {
  RGBA() = default;
  RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
  : r(r), g(g), b(b), a(a) {}

  uint8_t r, g, b, a;
};

inline Vec3f GammaCorrect(const Vec3f& c, float gamma) {
  float e = 1 / gamma;
  return Vec3f(powf(c.x, e), powf(c.y, e), powf(c.z, e));
}

inline RGBA Vec3fToRGBA(const Vec3f& c) {
  return RGBA(
    (uint8_t)(Saturate(c.x) * 255.99),
    (uint8_t)(Saturate(c.y) * 255.99),
    (uint8_t)(Saturate(c.z) * 255.99),
    255);
}

inline RGBA NormalToRGBA(const Vec3f& n) {
  return Vec3fToRGBA(n * 0.5f + Vec3f(0.5f, 0.5f, 0.5f));
}

#endif  // COLOR_H_
