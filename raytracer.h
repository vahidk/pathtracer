// Copyright 2018, Vahid Kazemi

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <float.h>
#include <functional>
#include <random>
#include <vector>

#include "./camera.h"
#include "./color.h"
#include "./image.h"
#include "./math.h"
#include "./rand.h"
#include "./ray.h"
#include "./scene.h"
#include "./vec3.h"

class Raytracer {
 public:
  Raytracer(int width, int height, int num_samples, int max_depth) :
    num_samples_(num_samples),
    max_depth_(50),
    image_(width, height) {}

  Vec3f Trace(const Scene& scene, const Ray& ray, int depth) {
    TraceResult result;
    const Object* obj = scene.Trace(ray, 0.001, FLT_MAX, &result);

    if (obj != nullptr) {
      Vec3f attenuation;
      Ray scattered;
      if (depth < max_depth_ &&
          obj->material->Scatter(ray, result, &attenuation, &scattered)) {
        Vec3f ref_color = Trace(scene, scattered, depth);
        return ref_color * attenuation;
      } else {
        return Vec3f(0, 0, 0);
      }
    } else {
      float t = (ray.direction.y + 1) * 0.5;
      return Lerp(Vec3f(1, 1, 1), Vec3f(0.3, 0.74, 1.0), t);
    }
  }

  const Image<RGBA>& Render(const Scene& scene, const Camera& camera) {
    float inv_width = 1.0f / image_.Width();
    float inv_height = 1.0f / image_.Height();
    for (int j = 0; j < image_.Height(); ++j) {
      for (int i = 0; i < image_.Width(); ++i) {
        Vec3f color(0, 0, 0);
        for (int k = 0; k < num_samples_; ++k) {
          Ray ray = camera.GetRay(
            (i + Random::Uniform()) * inv_width,
            1 - (j + Random::Uniform()) * inv_height);
          color = color + Trace(scene, ray, 0);
        }
        color = color / static_cast<float>(num_samples_);
        image_(i, j) = Vec3fToRGBA(GammaCorrect(color, 2.0f));
      }
    }
    return image_;
  }

 private:
  int num_samples_;
  int max_depth_;
  Image<RGBA> image_;
};

#endif  // RAYTRACER_H_
