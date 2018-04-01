// Copyright 2018, Vahid Kazemi

#ifndef VEC4_H_
#define VEC4_H_

#include <math.h>
#include <iostream>

#include "./vec3.h"

template<class T>
struct Vec4 {
  Vec4() = default;
  Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
  Vec4(const Vec3<T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}

  union {
    struct {
      T x, y, z, w;
    };
    T v[4];
  };
};

template<class T>
Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b) {
  return Vec4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

template<class T>
Vec4<T> operator-(const Vec4<T>& a, const Vec4<T>& b) {
  return Vec4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

template<class T>
Vec4<T> operator-(const Vec4<T>& v) {
  return Vec4<T>(-v.x, -v.y, -v.z, -v.w);
}

template<class T>
Vec4<T> operator*(const Vec4<T>& a, const Vec4<T>& b) {
  return Vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

template<class T>
Vec4<T> operator*(const Vec4<T>& v, T f) {
  return Vec4<T>(v.x * f, v.y * f, v.z * f, v.w * f);
}

template<class T>
Vec4<T> operator*(T f, const Vec4<T>& v) {
  return v * f;
}

template<class T>
Vec4<T> operator/(const Vec4<T>& a, T f) {
  return a * (1.0f / f);
}

template<class T>
T Dot(const Vec4<T>& a, const Vec4<T>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template<class T>
T SquaredLength(const Vec4<T>& v) {
  return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

template<class T>
T Length(const Vec4<T>& v) {
  return sqrtf(SquaredLength(v));
}

template<class T>
Vec4<T> Normal(const Vec4<T>& v) {
  return v / Length(v);
}

template<class T>
std::istream& operator>>(std::istream& is, Vec4<T>& v) {
  is >> v.x >> v.y >> v.z >> v.w;
  return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Vec4<T>& v) {
  os << v.x << " " << v.y << " " << v.z << " " << v.w;
  return os;
}

typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;

#endif  // VEC4_H_
