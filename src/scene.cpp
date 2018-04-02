// Copyright 2018, Vahid Kazemi

#include <float.h>

#include "./scene.h"

void Scene::AddObject(const Object* obj) {
  objects_.push_back(obj);
}

void Scene::Clear() {
  objects_.clear();
}

const Object* Scene::Trace(const Ray& ray, float start, float end,
                           TraceResult* result) const {
  const Object* obj = nullptr;
  result->t = FLT_MAX;
  for (const Object* cur_obj : objects_) {
    TraceResult cur_result;
    if (cur_obj->geometry->Trace(ray, start, end, &cur_result) &&
        cur_result.t < result->t) {
      obj = cur_obj;
      *result = cur_result;
    }
  }
  return obj;
}
