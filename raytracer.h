// Copyright 2018, Vahid Kazemi

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "./camera.h"
#include "./image.h"
#include "./ray.h"
#include "./scene.h"
#include "./vec3.h"

class Raytracer {
 public:
  Raytracer(int width, int height, int num_samples, int max_depth);

  Vec3f Trace(const Scene& scene, const Ray& ray, int depth);

  const Image<RGBA>& Render(const Scene& scene, const Camera& camera);

 private:
  int num_samples_;
  int max_depth_;
  Image<RGBA> image_;
};

#endif  // RAYTRACER_H_
