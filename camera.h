// Copyright 2018, Vahid Kazemi

#ifndef CAMERA_H_
#define CAMERA_H_

#include <math.h>

#include "./ray.h"
#include "./vec3.h"

class Camera {
 public:
  Camera(const Vec3f& from, const Vec3f& to, const Vec3f& up,
        float fovy, float aspect) {
    float theta = fovy * M_PI / 180.0f;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    Vec3f dir = Normal(to - from);
    Vec3f x = Normal(Cross(dir, up));
    Vec3f y = Normal(Cross(x, dir));
    origin_ = from;
    lower_left_ = from + dir - x * half_width - y * half_height;
    horizontal_ = 2.0f * half_width * x;
    vertical_ = 2.0f * half_height * y;
  }

  Ray GetRay(float u, float v) const {
    Vec3f pos = lower_left_ + horizontal_ * u + vertical_ * v;
    return Ray(origin_, Normal(pos - origin_));
  }

 private:
  Vec3f origin_;
  Vec3f lower_left_;
  Vec3f horizontal_;
  Vec3f vertical_;
};

#endif  // CAMERA_H_
