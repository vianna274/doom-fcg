#include "wall.hpp"
#include "object.hpp"

using namespace glm;

bool Wall::collision(vec3 otherPosition) {
  Object *dummy = this;
  if (ObjectStatic::collisionBetween(dummy, otherPosition)) {
    return true;
  }
  return false;
}

void Wall::draw() {};
