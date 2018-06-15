#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "enemy.hpp"

#ifndef _collision_h
#define _collision_h

namespace collision
{
    bool LineAABBIntersection(const glm::vec3 bbox_min, const glm::vec3 bbox_max,
                              const glm::vec4& v0, const glm::vec4& v1, glm::vec4& vecIntersection,
                              float& flFraction);

    bool TraceLine(const glm::vec4& v0, const glm::vec4& v1, glm::vec4& vecIntersection, const Enemy e);
}

#endif
