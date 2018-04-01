// Copyright 2018, Vahid Kazemi

#ifndef VEC3_H_
#define VEC3_H_

#include <math.h>
#include <iostream>

template<class T>
struct Vec3 {
  Vec3() = default;
  Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

  union {
    struct {
      T x, y, z;
    };
    T v[3];
  };
};

template<class T>
Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b) {
  return Vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<class T>
Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b) {
  return Vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<class T>
Vec3<T> operator-(const Vec3<T>& v) {
  return Vec3<T>(-v.x, -v.y, -v.z);
}

template<class T>
Vec3<T> operator*(const Vec3<T>& a, const Vec3<T>& b) {
  return Vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template<class T>
Vec3<T> operator*(const Vec3<T>& v, T f) {
  return Vec3<T>(v.x * f, v.y * f, v.z * f);
}

template<class T>
Vec3<T> operator*(T f, const Vec3<T>& v) {
  return v * f;
}

template<class T>
Vec3<T> operator/(const Vec3<T>& a, T f) {
  return a * (1.0f / f);
}

template<class T>
T Dot(const Vec3<T>& a, const Vec3<T>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<class T>
Vec3<T> Cross(const Vec3<T>& a, const Vec3<T>& b) {
  return Vec3<T>(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}

template<class T>
T SquaredLength(const Vec3<T>& v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

template<class T>
T Length(const Vec3<T>& v) {
  return sqrtf(SquaredLength(v));
}

template<class T>
Vec3<T> Normal(const Vec3<T>& v) {
  return v / Length(v);
}

template<class T>
Vec3<T> Reflect(const Vec3<T>& v, const Vec3<T>& n) {
  return v - 2 * Dot(v, n) * n;
}

template<class T>
bool Refract(const Vec3<T>& v, const Vec3<T>& n, float ratio, Vec3<T>* ref) {
  float cos_theta = Dot(v, n);
  T d = 1 - ratio * ratio * (1 - cos_theta * cos_theta);
  if (d > 0) {
    *ref = ratio * v - (cos_theta * ratio + sqrtf(d)) * n;
    return true;
  } else {
    return false;
  }
}

template<class T>
std::istream& operator>>(std::istream& is, Vec3<T>& v) {
  is >> v.x >> v.y >> v.z;
  return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& v) {
  os << v.x << " " << v.y << " " << v.z;
  return os;
}

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

#endif  // VEC3_H_
