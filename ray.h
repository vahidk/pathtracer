// Copyright 2018, Vahid Kazemi

#ifndef RAY_H_
#define RAY_H_

#include "./vec3.h"

struct Ray {
  Ray() = default;
  Ray(const Vec3f& origin, const Vec3f& direction)
  : origin(origin), direction(direction) {}

  Vec3f origin;
  Vec3f direction;
};

inline Vec3f PointAt(const Ray& ray, float t) {
  return ray.direction * t + ray.origin;
}

#endif  // RAY_H_
