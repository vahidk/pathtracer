// Copyright 2018, Vahid Kazemi

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "./geometry.h"
#include "./ray.h"
#include "./vec3.h"

class Material {
 public:
  virtual bool Scatter(const Ray& ray, const TraceResult& result,
                       Vec3f* attenuation, Ray* scattered) const = 0;
};

class Lambertian : public Material {
 public:
  explicit Lambertian(const Vec3f& albedo);

  bool Scatter(const Ray& ray, const TraceResult& result,
               Vec3f* attenuation, Ray* scattered) const override;

 private:
  Vec3f albedo_;
};

class Metal : public Material {
 public:
  explicit Metal(const Vec3f& albedo, float fuzz);

  bool Scatter(const Ray& ray, const TraceResult& result,
               Vec3f* attenuation, Ray* scattered) const override;

 private:
  Vec3f albedo_;
  float fuzz_;
};

class Dielectric : public Material {
 public:
  explicit Dielectric(float ri);

  bool Scatter(const Ray& ray, const TraceResult& result,
               Vec3f* attenuation, Ray* scattered) const override;

 private:
  float ri_;
};

#endif  // MATERIAL_H_
