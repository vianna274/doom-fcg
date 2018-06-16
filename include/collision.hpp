#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "enemy.hpp"

#ifndef _collision_h
#define _collision_h

namespace collision
{
    bool TraceLine(const glm::vec4& v0, const glm::vec4& v1, const Enemy e);
}

#endif
