// Copyright 2018, Vahid Kazemi

#ifndef IMAGE_H_
#define IMAGE_H_

#include "./color.h"

template<class T>
class Image {
 public:
  Image() : width_(0), height_(0) {}

  Image(int width, int height)
  : width_(width), height_(height), pixels_(width_ * height_) {}

  Image(Image&& image)
  : width_(image.width_), height_(image.height_) {
    pixels_ = std::move(image.pixels_);
  }

  void SetSize(int width, int height) {
    width_ = width;
    height_ = height;
    pixels_.resize(width * height);
  }

  T& operator[](int i) {
    return pixels_[i];
  }

  const T& operator()(int x, int y) const {
    return pixels_[x + y * width_];
  }

  T& operator()(int x, int y) {
    return pixels_[x + y * width_];
  }

  void Clear(T value) {
    pixels_.assign(width_ * height_, value);
  }

  const T* Data() const {
    return pixels_.data();
  }

  int Width() const { return width_; }
  int Height() const { return height_; }

 private:
  int width_, height_;
  std::vector<T> pixels_;
};

bool ReadImage(const char* filename, Image<RGBA>* image);
bool WriteImage(const char* filename, const Image<RGBA>& image);

// ex: min_re = -2, float max_re = 1, min_im = -1.2, max_iterations = 30
void Mandelbrot(float min_re, float max_re, float min_im, int max_iterations,
                Image<RGBA>* image);

#endif  // IMAGE_H_
