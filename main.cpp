// Copyright 2018, Vahid Kazemi

#include <functional>
#include <random>

#include "./raytracer.h"

int main() {
  Scene scene;

  Sphere sphere_g(Vec3f(0, -1000, -1), 999.5);
  Lambertian material_g(Vec3f(0.5f, 0.5f, 0.5f));
  Object object_g = { &sphere_g, &material_g };
  scene.AddObject(&object_g);

  Sphere sphere_a(Vec3f(-1.6, 0, -1), 0.5);
  Lambertian material_a(Vec3f(0.5f, 0.5f, 0.5f));
  Object object_a = { &sphere_a, &material_a };
  scene.AddObject(&object_a);

  Sphere sphere_b(Vec3f(0.0, 0.0, -1), 0.5);
  Metal material_b(Vec3f(0.8f, 0.8f, 0.8f), 0.5f);
  Object object_b = { &sphere_b, &material_b };
  scene.AddObject(&object_b);

  Sphere sphere_c(Vec3f(1.6, 0.0, -1), 0.5);
  Dielectric material_c(1.33f);
  Object object_c = { &sphere_c, &material_c };
  scene.AddObject(&object_c);

  Camera camera(Vec3f(0, 0, 1), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 90, 1.33f);

  Raytracer raytracer(640, 480, 64, 50);
  const Image<RGBA>& image = raytracer.Render(scene, camera);

  WriteImageToPPM(image, "output.ppm");

  return 0;
}
