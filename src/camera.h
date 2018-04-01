// Copyright 2018, Vahid Kazemi

#ifndef CAMERA_H_
#define CAMERA_H_

#include "./ray.h"
#include "./vec3.h"

class Camera {
 public:
  Camera(const Vec3f& from, const Vec3f& to, const Vec3f& up,
        float fovy, float aspect, float aperture, float focus_dist);

  Ray GetRay(float u, float v) const;

 private:
  Vec3f origin_;
  Vec3f lower_left_;
  Vec3f horizontal_;
  Vec3f vertical_;
  float width_;
  float height_;
  float lens_radius_;
};

#endif  // CAMERA_H_
