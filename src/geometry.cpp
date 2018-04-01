// Copyright 2018, Vahid Kazemi

#include "./geometry.h"
#include "./math.h"

Sphere::Sphere(const Vec3f& center, float radius)
: center(center), radius(radius) {}

bool Sphere::Trace(const Ray& ray, float start, float end,
                   TraceResult* result) const {
  Vec3f v = center - ray.origin;
  float b = Dot(ray.direction, v);
  float c = SquaredLength(v) - radius * radius;
  float d = b * b - c;
  if (d <= 0) {
    return false;
  }
  float t = b - sqrtf(d);
  float sign = 1.0f;
  if (t <= start || t >= end) {
    t = b + sqrtf(d);
    sign = -1.0f;
  }
  if (t <= start || t >= end) {
    return false;
  }
  Vec3f p = PointAt(ray, t);
  result->t = t;
  result->position = p;
  result->normal = sign * (p - center) / radius;
  return true;
}

Plane::Plane(const Vec3f& normal, float d) : normal(Normal(normal)), d(d) {}

bool Plane::Trace(const Ray& ray, float start, float end,
                  TraceResult* result) const {
  float dp = Dot(normal, ray.direction);
  if (dp == 0.0f) {
    return false;
  }

  float t = (d - Dot(normal, ray.origin)) / dp;
  if (t <= start || t >= end) {
    return false;
  }

  result->t = t;
  result->position = PointAt(ray, t);
  result->normal = -Sign(dp) * normal;
  return true;
}
