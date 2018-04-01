// Copyright 2018, Vahid Kazemi

#ifndef SCENE_H_
#define SCENE_H_

#include <algorithm>
#include <float.h>
#include <vector>

#include "./math.h"
#include "./rand.h"
#include "./ray.h"
#include "./vec3.h"

struct TraceResult {
  Vec3f position;
  Vec3f normal;
  float t;
};

class Material {
 public:
  virtual bool Scatter(const Ray& ray, const TraceResult& result,
                       Vec3f* attenuation, Ray* scattered) const = 0;
};

class Lambertian : public Material {
 public:
  explicit Lambertian(const Vec3f& albedo) : albedo_(albedo) {}

  bool Scatter(const Ray& ray, const TraceResult& result,
               Vec3f* attenuation, Ray* scattered) const override {
    Vec3f rnd = Random::PointInUnitSphere();
    *scattered = Ray(result.position, Normal(result.normal + rnd));
    *attenuation = albedo_;
    return true;
  }

 private:
  Vec3f albedo_;
};

class Metal : public Material {
 public:
  explicit Metal(const Vec3f& albedo, float fuzz)
    : albedo_(albedo), fuzz_(std::min(fuzz, 0.5f)) {}

  bool Scatter(const Ray& ray, const TraceResult& result,
               Vec3f* attenuation, Ray* scattered) const override {
    Vec3f reflection = Reflect(ray.direction, result.normal);
    Vec3f rnd = fuzz_ * Random::PointInUnitSphere();
    *scattered = Ray(result.position, Normal(reflection + rnd));
    *attenuation = albedo_;
    return Dot(ray.direction, result.normal) < 0;
  }

 private:
  Vec3f albedo_;
  float fuzz_;
};

class Dielectric : public Material {
 public:
  explicit Dielectric(float ri) : ri_(ri) {}

  bool Scatter(const Ray& ray, const TraceResult& result,
               Vec3f* attenuation, Ray* scattered) const override {
    Vec3f normal;
    float ratio;
    float cos_theta;
    if (Dot(ray.direction, result.normal) > 0) {
      normal = -result.normal;
      ratio = ri_;
      cos_theta = ri_ * Dot(ray.direction, result.normal);
    } else {
      normal = result.normal;
      ratio = 1 / ri_;
      cos_theta = -Dot(ray.direction, result.normal);
    }

    Vec3f refraction;
    float reflect_prob;
    if (Refract(ray.direction, normal, ratio, &refraction)) {
      reflect_prob = schlick(cos_theta, ri_);
    } else {
      reflect_prob = 1.0f;
    }

    if (Random::Uniform() < reflect_prob) {
      Vec3f reflection = Reflect(ray.direction, result.normal);
      *scattered = Ray(result.position, reflection);
    } else {
      *scattered = Ray(result.position, refraction);
    }
    *attenuation = Vec3f(1, 1, 1);
    return true;
  }

 private:
  float schlick(float cos_theta, float ri) const {
    float r0 = Square((1 - ri) / (1 + ri));
    return r0 + (1 - r0) * powf(1 - cos_theta, 5.f);
  }

  float ri_;
};

class Geometry {
 public:
  virtual bool Trace(const Ray& ray, float start, float end,
                     TraceResult* result) const = 0;
};

class Sphere : public Geometry {
 public:
  Sphere() = default;
  Sphere(const Vec3f& center, float radius)
  : center(center), radius(radius) {}

  bool Trace(const Ray& ray, float start, float end,
             TraceResult* result) const override {
    Vec3f v = center - ray.origin;
    float b = Dot(ray.direction, v);
    float c = SquaredLength(v) - radius * radius;
    float d = b * b - c;
    if (d <= 0) {
      return false;
    }
    float t = b - sqrtf(d);
    if (t <= start || t > end) {
      return false;
    }
    Vec3f p = PointAt(ray, t);
    result->t = t;
    result->position = p;
    result->normal = Normal(p - center);
    return true;
  }

 private:
  Vec3f center;
  float radius;
};

struct Object {
  Geometry* geometry;
  Material* material;
};

class Scene {
 public:
  Scene() = default;

  void AddObject(const Object* obj) {
    objects_.push_back(obj);
  }

  const Object* Trace(const Ray& ray, float start, float end,
                      TraceResult* result) const {
    const Object* obj = nullptr;
    result->t = FLT_MAX;
    for (const Object* cur_obj : objects_) {
      TraceResult cur_result;
      if (cur_obj->geometry->Trace(ray, start, end, &cur_result) &&
          cur_result.t < result->t) {
        obj = cur_obj;
        *result = cur_result;
      }
    }
    return obj;
  }

 private:
  std::vector<const Object*> objects_;
};

#endif  // SCENE_H_
