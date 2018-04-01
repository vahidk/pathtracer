// Copyright 2018, Vahid Kazemi

#ifndef MAT4_H_
#define MAT4_H_

#include "./vec4.h"

template<class T>
struct Mat4 {
  Mat4() = default;

  Mat4(T m11, T m12, T m13, T m14,
       T m21, T m22, T m23, T m24,
       T m31, T m32, T m33, T m34,
       T m41, T m42, T m43, T m44)
       : m11(m11), m12(m12), m13(m13), m14(m14),
         m21(m21), m22(m22), m23(m23), m24(m24),
         m31(m31), m32(m32), m33(m33), m34(m34),
         m41(m41), m42(m42), m43(m43), m44(m44) {}

  Mat4(const Vec4<T>& row1, const Vec4<T>& row2,
       const Vec4<T>& row3, const Vec4<T>& row4) {
    rows[0] = row1;
    rows[1] = row2;
    rows[2] = row3;
    rows[3] = row4;
  }

  Mat4(T x1, T x2, T x3, T x4)
  : m11(x1), m12(0), m13(0), m14(0),
    m21(0), m22(x2), m23(0), m24(0),
    m31(0), m32(0), m33(x3), m34(0),
    m41(0), m42(0), m43(0), m44(x4) {}

  explicit Mat4(T x)
  : m11(x), m12(0), m13(0), m14(0),
    m21(0), m22(x), m23(0), m24(0),
    m31(0), m32(0), m33(x), m34(0),
    m41(0), m42(0), m43(0), m44(x) {}

  const Vec4<T>& operator[](int i) const {
    return rows[i];
  }

  Vec4<T>& operator[](int i) {
    return rows[i];
  }

  Vec4<T> Column(int i) const {
    return Vec4<T>(v[i], v[i + 4], v[i + 8], v[i + 12]);
  }

  void SetColumn(int i, const Vec4<T>& iv) {
    v[i     ] = iv.x;
    v[i +  4] = iv.y;
    v[i +  8] = iv.z;
    v[i + 12] = iv.z;
  }

  static Mat4 Identity() {
    return Mat4(
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1);
  }

  static Mat4 Scale(float s) {
    return Mat4(
      s, 0, 0, 0,
      0, s, 0, 0,
      0, 0, s, 0,
      0, 0, 0, s);
  }

  static Mat4 Translation(const Vec3<T>& v) {
    return Mat4(
      1, 0, 0, v.x,
      0, 1, 0, v.y,
      0, 0, 1, v.z,
      0, 0, 0, 1);
  }

  static Mat4 RotationX(float r) {
    return Mat4(
      1, 0, 0, 0,
      0, cosf(r), -sinf(r), 0,
      0, sinf(r), cosf(r), 0,
      0, 0, 0, 1);
  }

  static Mat4 RotationY(float r) {
    return Mat4(
      cosf(r), 0, sinf(r), 0,
      0, 1, 0, 0,
      -sinf(r), 0, cosf(r), 0,
      0, 0, 0, 1);
  }

  static Mat4 RotationZ(float r) {
    return Mat4(
      cosf(r), -sinf(r), 0, 0,
      sinf(r), cosf(r), 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1);
  }

  static Mat4 Rotation(const Vec3f& v) {
    return Mat4(
      cosf(v.x) * cosf(v.y),
      cosf(v.x) * sinf(v.y) * sinf(v.z) - sinf(v.x) * cosf(v.z),
      cosf(v.x) * sinf(v.y) * cosf(v.z) + sinf(v.x) * sinf(v.z),
      0,
      sinf(v.x) * cosf(v.y),
      sinf(v.x) * sinf(v.y) * sinf(v.z) + cosf(v.x) * cosf(v.z),
      sinf(v.x) * sinf(v.y) * cosf(v.z) - cosf(v.x) * sinf(v.z),
      0,
      -sinf(v.y),
      cosf(v.y) * sinf(v.z),
      cosf(v.y) * cosf(v.z),
      0,
      0, 0, 0, 1);
  }

  static Mat4 LookAt(
    const Vec3<T>& eye, const Vec3<T>& center, const Vec3<T> up) {
    Vec3f z = Normal(eye - center);
    Vec3f x = Normal(Cross(up, z));
    Vec3f y = Normal(Cross(z, x));
    Mat4 m(x.x, x.y, x.z, 0,
           y.x, y.y, y.z, 0,
           z.x, z.y, z.z, 0,
           0, 0, 0, 1);
    return m * Translation(-center);
  }

  static Mat4 Perspective(float c) {
    return Mat4(
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, -1 / c, 1);
  }

  static Mat4 Viewport(int x, int y, int width, int height) {
    float hw = width * 0.5f, hh = height * 0.5f;
    return Mat4(
      hw, 0, 0, hw + x,
      0, hh, 0, hh + y,
      0, 0, 1, 0,
      0, 0, 0, 1);
  }

  union {
    struct {
      T m11, m12, m13, m14;
      T m21, m22, m23, m24;
      T m31, m32, m33, m34;
      T m41, m42, m43, m44;
    };
    struct {
      Vec4<T> rows[4];
    };
    T v[16];
  };
};

template<class T>
Mat4<T> operator+(const Mat4<T>& a, const Mat4<T>& b) {
  return Mat4<T>(
    a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13, a.m14 + b.m14,
    a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23, a.m24 + b.m24,
    a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33, a.m34 + b.m34,
    a.m41 + b.m41, a.m42 + b.m42, a.m43 + b.m43, a.m44 + b.m44);
}

template<class T>
Mat4<T> operator-(const Mat4<T>& a, const Mat4<T>& b) {
  return Mat4<T>(
    a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13, a.m14 - b.m14,
    a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23, a.m24 - b.m24,
    a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33, a.m34 - b.m34,
    a.m41 - b.m41, a.m42 - b.m42, a.m43 - b.m43, a.m44 - b.m44);
}

template<class T>
Mat4<T> operator*(const Mat4<T>& m, const T s) {
  return Mat4<T>(
    m.m11 * s, m.m12 * s, m.m13 * s, m.m14 * s,
    m.m21 * s, m.m22 * s, m.m23 * s, m.m24 * s,
    m.m31 * s, m.m32 * s, m.m33 * s, m.m34 * s,
    m.m41 * s, m.m42 * s, m.m43 * s, m.m44 * s);
}

template<class T>
Mat4<T> operator*(const T s, const Mat4<T>& m) {
  return m * s;
}

template<class T>
Vec4<T> operator*(const Mat4<T>& m, const Vec4<T>& v) {
  return Vec4<T>(
    m.m11 * v.x + m.m12 * v.y + m.m13 * v.z + m.m14 * v.w,
    m.m21 * v.x + m.m22 * v.y + m.m23 * v.z + m.m24 * v.w,
    m.m31 * v.x + m.m32 * v.y + m.m33 * v.z + m.m34 * v.w,
    m.m41 * v.x + m.m42 * v.y + m.m43 * v.z + m.m44 * v.w);
}

template<class T>
Mat4<T> operator*(const Mat4<T>& a, const Mat4<T>& b) {
  return Mat4<T>(
    a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41,
    a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42,
    a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43,
    a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44,
    a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41,
    a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42,
    a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43,
    a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44,
    a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41,
    a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42,
    a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43,
    a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44,
    a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41,
    a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42,
    a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43,
    a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44);
}

template<class T>
Mat4<T> operator/(const Mat4<T>& m, const T s) {
  return m * (1.0 / s);
}

template<class T>
T Determinant(const Mat4<T>& m) {
  return
    m.m14 * m.m23 * m.m32 * m.m41 - m.m13 * m.m24 * m.m32 * m.m41 -
    m.m14 * m.m22 * m.m33 * m.m41 + m.m12 * m.m24 * m.m33 * m.m41 +
    m.m13 * m.m22 * m.m34 * m.m41 - m.m12 * m.m23 * m.m34 * m.m41 -
    m.m14 * m.m23 * m.m31 * m.m42 + m.m13 * m.m24 * m.m31 * m.m42 +
    m.m14 * m.m21 * m.m33 * m.m42 - m.m11 * m.m24 * m.m33 * m.m42 -
    m.m13 * m.m21 * m.m34 * m.m42 + m.m11 * m.m23 * m.m34 * m.m42 +
    m.m14 * m.m22 * m.m31 * m.m43 - m.m12 * m.m24 * m.m31 * m.m43 -
    m.m14 * m.m21 * m.m32 * m.m43 + m.m11 * m.m24 * m.m32 * m.m43 +
    m.m12 * m.m21 * m.m34 * m.m43 - m.m11 * m.m22 * m.m34 * m.m43 -
    m.m13 * m.m22 * m.m31 * m.m44 + m.m12 * m.m23 * m.m31 * m.m44 +
    m.m13 * m.m21 * m.m32 * m.m44 - m.m11 * m.m23 * m.m32 * m.m44 -
    m.m12 * m.m21 * m.m33 * m.m44 + m.m11 * m.m22 * m.m33 * m.m44;
}

template<class T>
Mat4<T> Transpose(const Mat4<T>& m) {
  return Mat4<T>(
    m.m11, m.m21, m.m31, m.m41,
    m.m12, m.m22, m.m32, m.m42,
    m.m13, m.m23, m.m33, m.m43,
    m.m14, m.m24, m.m34, m.m44);
}

template<class T>
Mat4<T> Inverse(const Mat4<T>& m) {
    Mat4<T> i;
    i.m11 = m.m22  * m.m33 * m.m44 - m.m22  * m.m34 * m.m43 -
            m.m32  * m.m23  * m.m44 + m.m32  * m.m24  * m.m43 +
            m.m42 * m.m23  * m.m34 - m.m42 * m.m24  * m.m33;
    i.m21 = -m.m21  * m.m33 * m.m44 + m.m21  * m.m34 * m.m43 +
            m.m31  * m.m23  * m.m44 - m.m31  * m.m24  * m.m43 -
            m.m41 * m.m23  * m.m34 + m.m41 * m.m24  * m.m33;
    i.m31 = m.m21  * m.m32 * m.m44 - m.m21  * m.m34 * m.m42 -
            m.m31  * m.m22 * m.m44 + m.m31  * m.m24 * m.m42 +
            m.m41 * m.m22 * m.m34 - m.m41 * m.m24 * m.m32;
    i.m41 = -m.m21  * m.m32 * m.m43 + m.m21  * m.m33 * m.m42 +
            m.m31  * m.m22 * m.m43 - m.m31  * m.m23 * m.m42 -
            m.m41 * m.m22 * m.m33 + m.m41 * m.m23 * m.m32;
    i.m12 = -m.m12  * m.m33 * m.m44 + m.m12  * m.m34 * m.m43 +
            m.m32  * m.m13 * m.m44 - m.m32  * m.m14 * m.m43 -
            m.m42 * m.m13 * m.m34 + m.m42 * m.m14 * m.m33;
    i.m22 = m.m11  * m.m33 * m.m44 - m.m11  * m.m34 * m.m43 -
            m.m31  * m.m13 * m.m44 + m.m31  * m.m14 * m.m43 +
            m.m41 * m.m13 * m.m34 - m.m41 * m.m14 * m.m33;
    i.m32 = -m.m11  * m.m32 * m.m44 + m.m11  * m.m34 * m.m42 +
            m.m31  * m.m12 * m.m44 - m.m31  * m.m14 * m.m42 -
            m.m41 * m.m12 * m.m34 + m.m41 * m.m14 * m.m32;
    i.m42 = m.m11  * m.m32 * m.m43 - m.m11  * m.m33 * m.m42 -
            m.m31  * m.m12 * m.m43 + m.m31  * m.m13 * m.m42 +
            m.m41 * m.m12 * m.m33 - m.m41 * m.m13 * m.m32;
    i.m13 = m.m12  * m.m23 * m.m44 - m.m12  * m.m24 * m.m43 -
            m.m22  * m.m13 * m.m44 + m.m22  * m.m14 * m.m43 +
            m.m42 * m.m13 * m.m24 - m.m42 * m.m14 * m.m23;
    i.m23 = -m.m11  * m.m23 * m.m44 + m.m11  * m.m24 * m.m43 +
            m.m21  * m.m13 * m.m44 - m.m21  * m.m14 * m.m43 -
            m.m41 * m.m13 * m.m24 + m.m41 * m.m14 * m.m23;
    i.m33 = m.m11  * m.m22 * m.m44 - m.m11  * m.m24 * m.m42 -
            m.m21  * m.m12 * m.m44 + m.m21  * m.m14 * m.m42 +
            m.m41 * m.m12 * m.m24 - m.m41 * m.m14 * m.m22;
    i.m43 = -m.m11  * m.m22 * m.m43 + m.m11  * m.m23 * m.m42 +
            m.m21  * m.m12 * m.m43 - m.m21  * m.m13 * m.m42 -
            m.m41 * m.m12 * m.m23 + m.m41 * m.m13 * m.m22;
    i.m14 = -m.m12 * m.m23 * m.m34 + m.m12 * m.m24 * m.m33 +
            m.m22 * m.m13 * m.m34 - m.m22 * m.m14 * m.m33 -
            m.m32 * m.m13 * m.m24 + m.m32 * m.m14 * m.m23;
    i.m24 = m.m11 * m.m23 * m.m34 - m.m11 * m.m24 * m.m33 -
            m.m21 * m.m13 * m.m34 + m.m21 * m.m14 * m.m33 +
            m.m31 * m.m13 * m.m24 - m.m31 * m.m14 * m.m23;
    i.m34 = -m.m11 * m.m22 * m.m34 + m.m11 * m.m24 * m.m32 +
            m.m21 * m.m12 * m.m34 - m.m21 * m.m14 * m.m32 -
            m.m31 * m.m12 * m.m24 + m.m31 * m.m14 * m.m22;
    i.m44 = m.m11 * m.m22 * m.m33 - m.m11 * m.m23 * m.m32 -
            m.m21 * m.m12 * m.m33 + m.m21 * m.m13 * m.m32 +
            m.m31 * m.m12 * m.m23 - m.m31 * m.m13 * m.m22;
    float det = m.m11 * i.m11 + m.m12 * i.m21 + m.m13 * i.m31 + m.m14 * i.m41;
    return i / det;
}

typedef Mat4<float> Mat4f;

#endif  // MAT4_H_
