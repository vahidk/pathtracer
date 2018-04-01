// Copyright 2018, Vahid Kazemi

#include <stdint.h>
#include <stdio.h>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "../3rdparty/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../3rdparty/stb/stb_image_write.h"

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
