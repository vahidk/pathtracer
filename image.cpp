// Copyright 2018, Vahid Kazemi

#include <stdio.h>

#include "./image.h"

void WriteImageToPPM(const Image<RGBA>& image, const char* filename) {
  FILE *fp = fopen(filename, "w");
  fprintf(fp, "P3\n");
  fprintf(fp, "%d %d\n", image.Width(), image.Height());
  fprintf(fp, "%d\n", 255);
  for (int j = 0; j < image.Height(); ++j) {
    for (int i = 0; i < image.Width(); ++i) {
      RGBA color = image(i, j);
      fprintf(fp, "%d\t%d\t%d\t", color.r, color.g, color.b);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}
