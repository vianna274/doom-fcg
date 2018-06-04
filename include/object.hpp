#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#ifndef _object_h
#define _object_h

using namespace glm;

class Object {
    vec3 position;
    float xwidth, zwidth;
    vec4 model;
  public:
    Object(vec3 position, float xwidth, float zwidth, mat4 model);
    vec3 getPosition();
    void setPosition(vec3 newPosition);
    float getXwidth();
    float getZwidth();
    vec4 getModel();
    void setXwidth(float newXwidth);
    void setZwidth(float newZwidth);
    void setModel(vec4 newModel);
    virtual void draw() = 0;
};

namespace ObjectStatic {
  bool collisionBetween(Object* obj, vec3 pos);
  bool inRange(vec3 main, vec3 aiming, float range);
}
#endif
