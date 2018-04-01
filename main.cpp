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
  Lambertian material_a(Vec3f(0.5f, 0.5f, 0.9f));
  Object object_a = { &sphere_a, &material_a };
  scene.AddObject(&object_a);

  Sphere sphere_b(Vec3f(0.0, 0.0, -1), 0.5);
  Metal material_b(Vec3f(0.85f, 0.64f, 0.12f), 0.5f);
  Object object_b = { &sphere_b, &material_b };
  scene.AddObject(&object_b);

  Sphere sphere_c(Vec3f(1.6, 0.0, -1), 0.5);
  Dielectric material_c(1.33f);
  Object object_c = { &sphere_c, &material_c };
  scene.AddObject(&object_c);

  Sphere sphere_d(Vec3f(-1.2, 0.0, 0.0f), 0.5);
  Dielectric material_d(0.5f);
  Object object_d = { &sphere_d, &material_d };
  scene.AddObject(&object_d);

  Vec3f from(4, 0, 2);
  Vec3f to(0, 0, -1);
  Vec3f up(0, 1, 0);
  Camera camera(from, to, up, 45, 1.33f, 0.5f, Length(to - from));

  Raytracer raytracer(640, 480, 64, 50);
  const Image<RGBA>& image = raytracer.Render(scene, camera);

  WriteImageToPPM(image, "output.ppm");

  return 0;
}
