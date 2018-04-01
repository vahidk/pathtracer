// Copyright 2018, Vahid Kazemi

#ifndef MAT3_H_
#define MAT3_H_

#include "./vec4.h"

template<class T>
struct Mat3 {
  union {
    struct {
      T m11, m12, m13;
      T m21, m22, m23;
      T m31, m32, m33;
    };
    struct {
      Vec3<T> rows[3];
    };
    T v[9];
  };

  Mat3() { }
  Mat3(
    T m11, T m12, T m13,
    T m21, T m22, T m23,
    T m31, T m32, T m33) :
    m11(m11), m12(m12), m13(m13),
    m21(m21), m22(m22), m23(m23),
    m31(m31), m32(m32), m33(m33) { }
  Mat3(const Vec3<T>& row1, const Vec3<T>& row2, const Vec3<T>& row3) {
    rows[0] = row1;
    rows[1] = row2;
    rows[2] = row3;
  }

  Mat3(const Mat3& m) {
    memcpy(v, m.v, sizeof(v));
  }

  const Vec3<T>& operator[](int i) const {
    return rows[i];
  }

  Vec3<T>& operator[](int i) {
    return rows[i];
  }

  Vec3<T> Column(int i) const {
    return Vec3<T>(v[i], v[i + 3], v[i + 6]);
  }

  void SetColumn(int i, const Vec3<T>& iv) {
    v[i    ] = iv.x;
    v[i + 3] = iv.y;
    v[i + 6] = iv.z;
  }

  static Mat3 Identity() {
    return Mat3(1, 0, 0,
                0, 1, 0,
                0, 0, 1);
  }

  static Mat3 Scale(float s) {
    return Mat3(s, 0, 0,
                0, s, 0,
                0, 0, s);
  }

  static Mat3 Translation(const Vec3<T>& v) {
    return Mat3(1, 0, v.x,
                0, 1, v.y,
                0, 0, v.z);
  }

  static Mat3 RotationX(float r) {
    return Mat3(1, 0, 0,
                0, cosf(r), -sinf(r),
                0, sinf(r), cosf(r));
  }

  static Mat3 RotationY(float r) {
    return Mat3(cosf(r), 0, sinf(r),
                0, 1, 0,
                -sinf(r), 0, cosf(r));
  }

  static Mat3 RotationZ(float r) {
    return Mat3(cosf(r), -sinf(r), 0,
                sinf(r), cosf(r), 0,
                0, 0, 1);
  }

  static Mat3 Rotation(const Vec3f& v) {
    return Mat3(
      cosf(v.x) * cosf(v.y),
      cosf(v.x) * sinf(v.y) * sinf(v.z) - sinf(v.x) * cosf(v.z),
      cosf(v.x) * sinf(v.y) * cosf(v.z) + sinf(v.x) * sinf(v.z),
      sinf(v.x) * cosf(v.y),
      sinf(v.x) * sinf(v.y) * sinf(v.z) + cosf(v.x) * cosf(v.z),
      sinf(v.x) * sinf(v.y) * cosf(v.z) - cosf(v.x) * sinf(v.z),
      -sinf(v.y),
      cosf(v.y) * sinf(v.z),
      cosf(v.y) * cosf(v.z));
  }
};

template<class T>
Mat3<T> operator+(const Mat3<T>& a, const Mat3<T>& b) {
  return Mat3<T>(
    a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13,
    a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23,
    a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33);
}

template<class T>
Mat3<T> operator-(const Mat3<T>& a, const Mat3<T>& b) {
  return Mat3<T>(
    a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13,
    a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23,
    a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33);
}

template<class T>
Mat3<T> operator*(const Mat3<T>& m, const T s) {
  return Mat3<T>(
    m.m11 * s, m.m12 * s, m.m13 * s,
    m.m21 * s, m.m22 * s, m.m23 * s,
    m.m31 * s, m.m32 * s, m.m33 * s);
}

template<class T>
Vec3<T> operator*(const Mat3<T>& m, const Vec3<T>& v) {
  return Vec3<T>(
    m.m11 * v.x + m.m12 * v.y + m.m13 * v.z,
    m.m21 * v.x + m.m22 * v.y + m.m23 * v.z,
    m.m31 * v.x + m.m32 * v.y + m.m33 * v.z);
}

template<class T>
Mat3<T> operator*(const Mat3<T>& a, const Mat3<T>& b) {
  return Mat3<T>(
    a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31,
    a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32,
    a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,
    a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31,
    a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32,
    a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,
    a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31,
    a.m32 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32,
    a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33);
}

template<class T>
Mat3<T> operator/(const Mat3<T>& m, const T s) {
  return m * (1.0 / s);
}

typedef Mat3<float> Mat3f;

#endif  // MAT3_H_
