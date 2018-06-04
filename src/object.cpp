#include "object.hpp"
#include <glm/vec4.hpp>
#include <cstdio>
using namespace glm;

Object::Object(vec3 position, float xwidth, float zwidth, mat4 model) {
  this->position = position;
  this->xwidth = xwidth;
  this->zwidth = zwidth;
}
vec3 Object::getPosition() {
  return position;
}

void Object::setPosition(vec3 newPosition) {
  position = newPosition;
}

float Object::getXwidth() {
  return xwidth;
}

float Object::getZwidth() {
  return zwidth;
}

vec4 Object::getModel() {
  return model;
}

void Object::setXwidth(float newXwidth) {
  xwidth = newXwidth;
}

void Object::setZwidth(float newZwidth) {
  zwidth = newZwidth;
}

void Object::setModel(vec4 newModel) {
  model = newModel;
}

namespace ObjectStatic {
  bool collisionBetween(Object* obj, vec3 pos) {
    float firstX = obj->getPosition().x - obj->getXwidth()/2;
    float firstZ = obj->getPosition().z - obj->getZwidth()/2;

    float lastX = obj->getPosition().x + obj->getXwidth()/2;
    float lastZ = obj->getPosition().z + obj->getZwidth()/2;
    if ((pos.x >= firstX  && pos.x <= lastX ) &&
        (pos.z >= firstZ  && pos.z <= lastZ)) {
      return true;
    }

    return false;
  }
}
