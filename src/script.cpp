// Copyright 2018, Vahid Kazemi

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include "./script.h"

#define GetFloat GetScalar<float>
#define GetInt GetScalar<int>

// Common methods

template<class T>
T GetScalar(lua_State *ls, int n) {
  return static_cast<T>(lua_tonumber(ls, n));
}

Vec3f GetVec3f(lua_State *ls, int n) {
  return Vec3f(GetFloat(ls, n),
               GetFloat(ls, n + 1),
               GetFloat(ls, n + 2));

}

template<class T>
T* GetPointer(lua_State* ls, const char* name, int n) {
  return *(T**)luaL_checkudata(ls, n, name);
}

template<class T>
T* GetGlobalPointer(lua_State* ls, const char* name) {
  lua_getglobal(ls, name);
  return (T*)lua_topointer(ls, -1);
}

// Geometry

int NewSphere(lua_State* ls) {
  Vec3f origin = GetVec3f(ls, 1);
  float r = GetFloat(ls, 4);
  Geometry* g = new Sphere(origin, r);
  *(Geometry**)lua_newuserdata(ls, sizeof(Geometry*)) = g;
  luaL_getmetatable(ls, "Geometry");
  lua_setmetatable(ls, -2);
  return 1;
}

int NewPlane(lua_State* ls) {
  Vec3f normal = GetVec3f(ls, 1);
  float d = GetFloat(ls, 4);
  Geometry* g = new Plane(normal, d);
  *(Geometry**)lua_newuserdata(ls, sizeof(Geometry*)) = g;
  luaL_getmetatable(ls, "Geometry");
  lua_setmetatable(ls, -2);
  return 1;
}

int GCGeometry(lua_State* ls) {
  delete GetPointer<Geometry>(ls, "Geometry", 1);
  return 0;
}

void RegisterGeometry(lua_State* ls) {
  luaL_Reg funcs[] = {
      { "sphere", NewSphere },
      { "plane", NewPlane },
      { "__gc", GCGeometry },
      { NULL, NULL }
  };

  luaL_newmetatable(ls, "Geometry");
  luaL_setfuncs(ls, funcs, 0);
  lua_pushvalue(ls, -1);
  lua_setfield(ls, -1, "__index");
  lua_setglobal(ls, "Geometry");
}

// Material

int NewLambertian(lua_State* ls) {
  Vec3f albedo = GetVec3f(ls, 1);
  Material* material = new Lambertian(albedo);
  *(Material**)lua_newuserdata(ls, sizeof(Material*)) = material;
  luaL_getmetatable(ls, "Material");
  lua_setmetatable(ls, -2);
  return 1;
}

int NewMetal(lua_State* ls) {
  Vec3f albedo = GetVec3f(ls, 1);
  float fuzz = GetFloat(ls, 4);
  Material* material = new Metal(albedo, fuzz);
  *(Material**)lua_newuserdata(ls, sizeof(Material*)) = material;
  luaL_getmetatable(ls, "Material");
  lua_setmetatable(ls, -2);
  return 1;
}

int NewDielectric(lua_State* ls) {
  float ri = GetFloat(ls, 1);
  Material* material = new Dielectric(ri);
  *(Material**)lua_newuserdata(ls, sizeof(Material*)) = material;
  luaL_getmetatable(ls, "Material");
  lua_setmetatable(ls, -2);
  return 1;
}

int GCMaterial(lua_State* ls) {
  delete GetPointer<Object>(ls, "Material", 1);
  return 0;
}

void RegisterMaterial(lua_State* ls) {
  luaL_Reg funcs[] = {
      { "lambertian", NewLambertian },
      { "metal", NewMetal },
      { "dielectric", NewDielectric },
      { "__gc", GCMaterial },
      { NULL, NULL }
  };

  luaL_newmetatable(ls, "Material");
  luaL_setfuncs(ls, funcs, 0);
  lua_pushvalue(ls, -1);
  lua_setfield(ls, -1, "__index");
  lua_setglobal(ls, "Material");
}

// Object

int NewObject(lua_State* ls) {
  Geometry* g = GetPointer<Geometry>(ls, "Geometry", 1);
  Material* m = GetPointer<Material>(ls, "Material", 2);
  Object* obj = new Object(g, m);

  *(Object**)lua_newuserdata(ls, sizeof(Object*)) = obj;
  luaL_getmetatable(ls, "Object");
  lua_setmetatable(ls, -2);
  return 1;
}
int GCObject(lua_State* ls) {
  delete GetPointer<Object>(ls, "Object", 1);
  return 0;
}

void RegisterObject(lua_State* ls) {
  luaL_Reg funcs[] = {
      { "new", NewObject },
      { "__gc", GCObject },
      { NULL, NULL }
  };

  luaL_newmetatable(ls, "Object");
  luaL_setfuncs(ls, funcs, 0);
  lua_pushvalue(ls, -1);
  lua_setfield(ls, -1, "__index");
  lua_setglobal(ls, "Object");
}

// Other functions

int SetSize(lua_State* ls) {
  int width = GetInt(ls, 1);
  int height = GetInt(ls, 2);

  Pathtracer* pathtracer = GetGlobalPointer<Pathtracer>(ls, "pathtracer_");
  pathtracer->SetSize(width, height);
  return 0;
}

int SetPerspective(lua_State* ls) {
  float fovy = GetFloat(ls, 1);
  float aspect = GetFloat(ls, 2);
  float aperture = GetFloat(ls, 3);
  float focus_dist = GetFloat(ls, 4);

  Camera* camera = GetGlobalPointer<Camera>(ls, "camera_");
  camera->SetPerspective(fovy, aspect, aperture, focus_dist);
  return 0;
}

int LookAt(lua_State* ls) {
  Vec3f from = GetVec3f(ls, 1);
  Vec3f to = GetVec3f(ls, 4);
  Vec3f up = GetVec3f(ls, 7);

  Camera* camera = GetGlobalPointer<Camera>(ls, "camera_");
  camera->LookAt(from, to, up);
  return 0;
}

int Clear(lua_State* ls) {
  Scene* scene = GetGlobalPointer<Scene>(ls, "scene_");
  scene->Clear();
  return 0;
}

int AddObject(lua_State* ls) {
  Object* obj = GetPointer<Object>(ls, "Object", 1);
  Scene* scene = GetGlobalPointer<Scene>(ls, "scene_");
  scene->AddObject(obj);
  return 0;
}

int Render(lua_State* ls) {
  const char* filename = lua_tostring(ls, 1);

  Pathtracer* pathtracer = GetGlobalPointer<Pathtracer>(ls, "pathtracer_");
  Scene* scene = GetGlobalPointer<Scene>(ls, "scene_");
  Camera* camera = GetGlobalPointer<Camera>(ls, "camera_");

  const Image<RGBA>& image = pathtracer->Render(*scene, *camera);
  WriteImage(filename, image);
  return 0;
}

// Script

Script::Script()
  : pathtracer_(640, 480, 64, 10),
    camera_(Vec3f(0, 0, 1), Vec3f(0, 0, 0), Vec3f(0, 1, 0), 45, 1.33f, 0, 1) {

  lua_state_ = luaL_newstate();
  luaL_openlibs(lua_state_);

  // Register objects
  RegisterGeometry(lua_state_);
  RegisterMaterial(lua_state_);
  RegisterObject(lua_state_);

  // Register functions
  lua_register(lua_state_, "set_size", SetSize);
  lua_register(lua_state_, "set_perspective", SetPerspective);
  lua_register(lua_state_, "look_at", LookAt);
  lua_register(lua_state_, "clear", Clear);
  lua_register(lua_state_, "add_object", AddObject);
  lua_register(lua_state_, "render", Render);

  // Push global variables
  lua_pushlightuserdata(lua_state_, &pathtracer_);
  lua_setglobal(lua_state_, "pathtracer_");

  lua_pushlightuserdata(lua_state_, &scene_);
  lua_setglobal(lua_state_, "scene_");

  lua_pushlightuserdata(lua_state_, &camera_);
  lua_setglobal(lua_state_, "camera_");
}

Script::~Script() {
  lua_close(lua_state_);
}

bool Script::Run(const char* filename) {
  int status = luaL_loadfile(lua_state_, filename);
  if (status) {
    fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(lua_state_, -1));
    return false;
  }
  status = lua_pcall(lua_state_, 0, 0, 0);
  if (status) {
    fprintf(stderr, "Failed to evaluate the script: %s\n",
            lua_tostring(lua_state_, -1));
    return false;
  }
  lua_gc(lua_state_, LUA_GCCOLLECT, 0);
  return true;
}
