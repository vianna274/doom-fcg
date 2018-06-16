
#ifndef _wall_h
#define _wall_h
#include "object.hpp"
#include "support.h"

using namespace glm;

class Wall : public Object {
  public:
    Wall(vec3 position, float xwidth, float zwidth, mat4 model) : Object(position, xwidth, zwidth, model)
    {
        bbox_min = vec3(this->Object::getPosition().x-this->Object::getXwidth()/2,
                             this->Object::getPosition().y-0.000001,
                             this->Object::getPosition().z-this->Object::getZwidth()/2);

        bbox_max = vec3(this->Object::getPosition().x+this->Object::getXwidth()/2,
                             this->Object::getPosition().y+0.000001,
                             this->Object::getPosition().z+this->Object::getZwidth()/2);

    };
    bool collision(vec3 otherPosition);
    vec3 bbox_min = vec3(0,0,0);
    vec3 bbox_max = vec3(0,0,0);
    void draw();
};

#endif
