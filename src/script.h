// Copyright 2018, Vahid Kazemi

#ifndef SCRIPT_H_
#define SCRIPT_H_

extern "C" {
#include <lua.h>
}

#include "./raytracer.h"

class Script {
 public:
  Script();
  ~Script();

  bool Run(const char* filename);

 private:
  lua_State* lua_state_;
  Raytracer raytracer_;
  Scene scene_;
  Camera camera_;
};

#endif  // SCRIPT_H_
