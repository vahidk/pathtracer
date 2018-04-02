// Copyright 2018, Vahid Kazemi

#include <stdint.h>
#include <stdio.h>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "./image.h"

bool ReadImage(const char* filename, Image<RGBA>* image) {
  int w, h, ch;
  stbi_set_flip_vertically_on_load(1);
  uint8_t *data = stbi_load(filename, &w, &h, &ch, 0);
  if (data == nullptr) {
    fprintf(stderr, "Image file not found: %s.", filename);
    return false;
  }

  if (ch != 1 && ch != 3 && ch != 4) {
    fprintf(stderr, "Unsupported image channels: %d", ch);
    return false;
  }

  image->SetSize(w, h);
  uint8_t* p = data;
  for (int j = 0; j < h; ++j) {
    for (int i = 0; i < w; ++i) {
      if (ch == 1) {
        (*image)(i, j) = RGBA(p[0], p[0], p[0], 255);
      } else if (ch == 3) {
        (*image)(i, j) = RGBA(p[0], p[1], p[2], 255);
      } else if (ch == 4) {
        (*image)(i, j) = RGBA(p[0], p[1], p[2], p[3]);
      }
      p += ch;
    }
  }
  stbi_image_free(data);
  return true;
}

bool WriteImage(const char* filename, const Image<RGBA>& image) {
  stbi_write_jpg(filename, image.Width(), image.Height(), 4, image.Data(), 100);
  return true;
}

void Mandelbrot(float min_re, float max_re, float min_im, int max_iterations,
                Image<RGBA>* image) {
  float max_im = min_im + (max_re - min_re) * image->Height() / image->Width();
  float re_factor = (max_re - min_re) / (image->Height() - 1);
  float im_factor = (max_im - min_im) / (image->Width() - 1);

  for (int y = 0; y < image->Height(); ++y) {
    float c_im = max_im - y * im_factor;
    for (int x = 0; x < image->Width(); ++x) {
      float c_re = min_re + x * re_factor;
      float z_re = c_re, z_im = c_im;
      bool is_inside = true;
      int n = 0;
      for (; n < max_iterations; ++n) {
        float z_re2 = z_re * z_re, z_im2 = z_im * z_im;
        if (z_re2 + z_im2 > 4) {
          is_inside = false;
          break;
        }
        z_im = 2 * z_re * z_im + c_im;
        z_re = z_re2 - z_im2 + c_re;
      }

      if (is_inside) {
        (*image)(x, y) = RGBA(kColorWhite);
      } else {
        (*image)(x, y) = RGBA(n << 11);
      }
    }
  }
}
