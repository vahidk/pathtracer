// Copyright 2018, Vahid Kazemi

#ifndef MATH_H_
#define MATH_H_

template<class T>
T Lerp(T from, T to, float ratio) {
  return from * (1 - ratio) + to * ratio;
}

template<class T>
T Clamp(T value, T minimum, T maximum) {
  if (value < minimum) return minimum;
  if (value > maximum) return maximum;
  return value;
}

template<class T>
T Saturate(T value) {
  return Clamp<T>(value, 0, 1);
}

template<class T>
T SafeDivide(T a, T b) {
  if (b == 0) return 0;
  return a / b;
}

template<class T>
T Square(T x) {
  return x * x;
}

template<class T>
T Sign(T x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

#endif  // MATH_H_
