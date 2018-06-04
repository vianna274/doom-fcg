
#ifndef _wall_h
#define _wall_h
#include "object.hpp"
#include "support.h"

using namespace glm;

class Wall : public Object {
  public:
    Wall(vec3 position, float xwidth, float zwidth, mat4 model) : Object(position, xwidth, zwidth, model) {};
    bool collision(vec3 otherPosition);
    void draw();
};

#endif
