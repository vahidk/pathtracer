// Copyright 2018, Vahid Kazemi

#ifndef CAMERA_H_
#define CAMERA_H_

#include "./ray.h"
#include "./vec3.h"

struct Camera {
  Camera(int width, int height, const Vec3f& origin = Vec3f(0, 0, 1))
  : width(width), height(height), origin(origin) {}

  Ray GetRay(float x, float y) const {
    float cx = 2 * (-0.5 + x / width) * width / height;
    float cy = +1.0 - 2.0 * y / height;
    return Ray(origin, Normal(Vec3f(cx, cy, 0.0f) - origin));
  }

  float width, height;
  Vec3f origin;
};

#endif  // CAMERA_H_
