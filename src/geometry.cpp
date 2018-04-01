// Copyright 2018, Vahid Kazemi

#include "./geometry.h"

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
  if (t <= start || t >= end) {
    t = b + sqrtf(d);
  }
  if (t <= start || t >= end) {
    return false;
  }
  Vec3f p = PointAt(ray, t);
  result->t = t;
  result->position = p;
  result->normal = (p - center) / radius;
  return true;
}
