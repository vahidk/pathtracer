// Copyright 2018, Vahid Kazemi

#ifndef VEC2_H_
#define VEC2_H_

#include <math.h>
#include <iostream>

template<class T>
struct Vec2 {
  Vec2() = default;
  Vec2(T x, T y) : x(x), y(y) {}

  union {
    struct {
      T x, y;
    };
    T v[2];
  };
};

template<class T>
Vec2<T> operator+(const Vec2<T>& v) const {
  return Vec2<T>(x + v.x, y + v.y);
}

template<class T>
Vec2<T> operator+(T s) const {
  return Vec2<T>(x + s, y + s);
}

template<class T>
Vec2<T> operator-(const Vec2<T>& v) const {
  return Vec2<T>(x - v.x, y - v.y);
}

template<class T>
Vec2<T> operator-(T s) const {
  return Vec2<T>(x - s, y - s);
}

template<class T>
Vec2<T> operator-() const {
  return Vec2<T>(-x, -y);
}

template<class T>
Vec2<T> operator*(const Vec2<T>& v) const {
  return Vec3(x * v.x, y * v.y);
}

template<class T>
Vec2<T> operator*(T s) const {
  return Vec2<T>(x * s, y * s);
}

template<class T>
Vec2<T> operator/(T s) const {
  return *this * (1.0 / s);
}

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;

#endif  // VEC2_H_
