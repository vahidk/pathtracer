// Copyright 2018, Vahid Kazemi

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "./ray.h"
#include "./vec3.h"

struct TraceResult {
  Vec3f position;
  Vec3f normal;
  float t;
};

class Geometry {
 public:
  virtual ~Geometry() {}

  virtual bool Trace(const Ray& ray, float start, float end,
                     TraceResult* result) const = 0;
};

class Sphere : public Geometry {
 public:
  Sphere(const Vec3f& center, float radius);

  bool Trace(const Ray& ray, float start, float end,
             TraceResult* result) const override;

 private:
  Vec3f center;
  float radius;
};

class Plane : public Geometry {
 public:
  Plane(const Vec3f& normal, float d);

  bool Trace(const Ray& ray, float start, float end,
             TraceResult* result) const override;

 private:
  Vec3f normal;
  float d;
};

#endif  // GEOMETRY_H_
