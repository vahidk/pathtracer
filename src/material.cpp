// Copyright 2018, Vahid Kazemi

#include <math.h>
#include <algorithm>

#include "./material.h"
#include "./math.h"
#include "./rand.h"

Lambertian::Lambertian(const Vec3f& albedo) : albedo_(albedo) {}

bool Lambertian::Scatter(const Ray& ray, const TraceResult& result,
              Vec3f* attenuation, Ray* scattered) const {
  Vec3f rnd = Random::PointInUnitSphere();
  *scattered = Ray(result.position, Normal(result.normal + rnd));
  *attenuation = albedo_;
  return true;
}

Metal::Metal(const Vec3f& albedo, float fuzz)
  : albedo_(albedo), fuzz_(std::min(fuzz, 0.5f)) {}

bool Metal::Scatter(const Ray& ray, const TraceResult& result,
                    Vec3f* attenuation, Ray* scattered) const {
  Vec3f reflection = Reflect(ray.direction, result.normal);
  Vec3f rnd = fuzz_ * Random::PointInUnitSphere();
  *scattered = Ray(result.position, Normal(reflection + rnd));
  *attenuation = albedo_;
  return Dot(ray.direction, result.normal) < 0;
}

Dielectric::Dielectric(float ri) : ri_(ri) {}

float schlick(float cosine, float ri) {
  float r0 = Square((1 - ri) / (1 + ri));
  return r0 + (1 - r0) * powf(1 - cosine, 5.f);
}

bool Dielectric::Scatter(const Ray& ray, const TraceResult& result,
                         Vec3f* attenuation, Ray* scattered) const {
  float ratio;
  float cosine;
  float ddn = Dot(ray.direction, result.normal);
  if (ddn > 0) {
    ratio = ri_;
    cosine = sqrtf(1 - ri_ * ri_ * (1 - ddn * ddn));
  } else {
    ratio = 1 / ri_;
    cosine = -ddn;
  }

  Vec3f refraction;
  float reflect_prob;
  if (Refract(ray.direction, result.normal, ratio, &refraction)) {
    reflect_prob = schlick(cosine, ri_);
  } else {
    reflect_prob = 1.0f;
  }

  if (Random::Uniform() <= reflect_prob) {
    Vec3f reflection = Reflect(ray.direction, result.normal);
    *scattered = Ray(result.position, reflection);
  } else {
    *scattered = Ray(result.position, refraction);
  }
  *attenuation = Vec3f(1, 1, 1);
  return true;
}
