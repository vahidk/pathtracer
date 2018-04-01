// Copyright 2018, Vahid Kazemi

#define _USE_MATH_DEFINES
#include <math.h>

#include "./camera.h"
#include "./rand.h"

Camera::Camera(const Vec3f& from, const Vec3f& to, const Vec3f& up,
      float fovy, float aspect, float aperture, float focus_dist) {
  float theta = fovy * M_PI / 180.0f;
  float half_height = tan(theta / 2) * focus_dist;
  float half_width = aspect * half_height;
  Vec3f dir = Normal(to - from);
  Vec3f x = Normal(Cross(dir, up));
  Vec3f y = Normal(Cross(x, dir));
  origin_ = from;
  lower_left_ = from + dir * focus_dist - half_width * x - half_height * y;
  horizontal_ = x;
  vertical_ = y;
  width_ = 2.0f * half_width;
  height_ = 2.0f * half_height;
  lens_radius_ = aperture / 2.0f;
}

Ray Camera::GetRay(float u, float v) const {
  Vec3f rnd = Random::PointInUnitDisk() * lens_radius_;
  Vec3f from = origin_ + horizontal_ * rnd.x + vertical_ * rnd.y;
  Vec3f to = lower_left_ +
              horizontal_ * width_ * u +
              vertical_ * height_ * v;
  return Ray(from, Normal(to - from));
}
