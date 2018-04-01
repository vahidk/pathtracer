// Copyright 2018, Vahid Kazemi

#ifndef IMAGE_H_
#define IMAGE_H_

#include "./color.h"

template<class T>
class Image {
 public:
  Image(int width, int height) : width_(width), height_(height) {
    pixels_ = new T[width_ * height_];
  }

  Image(Image&& image)
  : width_(image.width_), height_(image.height_), pixels_(image.pixels_) {
    image.pixels_ = nullptr;
  }

  T operator()(int x, int y) const {
    return pixels_[x + y * width_];
  }

  T& operator()(int x, int y) {
    return pixels_[x + y * width_];
  }

  int Width() const { return width_; }
  int Height() const { return height_; }

 private:
  int width_, height_;
  T* pixels_;
};

void WriteImageToPPM(const Image<RGBA>& image, const char* filename);

#endif  // IMAGE_H_
