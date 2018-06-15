#include "collision.hpp"
#include <utility>
#include <algorithm>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "enemy.hpp"

namespace collision
{
    bool ClipLine(int d, const glm::vec3 bbox_min, const glm::vec3 bbox_max, const glm::vec4& v0,
                  const glm::vec4& v1, float& f_low, float& f_high){
        float f_dim_low, f_dim_high;

        f_dim_low = (bbox_min[d] - v0[d])/(v1[d] - v0[d]);
        f_dim_high = (bbox_max[d] - v0[d])/(v1[d] - v0[d]);

        if (f_dim_high < f_dim_low)
            std::swap(f_dim_high, f_dim_low);

        if (f_dim_high < f_low)
            return false;

        if (f_dim_low > f_high)
            return false;

        f_low = std::max(f_dim_low, f_low);
        f_high = std::min(f_dim_high, f_high);

        if (f_low > f_high)
            return false;

        return true;
    }

    bool LineAABBIntersection(const glm::vec3 bbox_min, const glm::vec3 bbox_max, const glm::vec4& v0,
                              const glm::vec4& v1, glm::vec4& vecIntersection, float& flFraction){
        float f_low = 0;
        float f_high = 1;

        if (!ClipLine(0, bbox_min, bbox_max, v0, v1, f_low, f_high))
            return false;

        if (!ClipLine(1, bbox_min, bbox_max, v0, v1, f_low, f_high))
            return false;

        if (!ClipLine(2, bbox_min, bbox_max, v0, v1, f_low, f_high))
            return false;

        glm::vec4 b;
        b.x = v1.x - v0.x;
        b.y = v1.y - v0.y;
        b.z = v1.z - v0.z;

        vecIntersection.x = v0.x + b.x * f_low;
        vecIntersection.y = v0.y + b.y * f_low;
        vecIntersection.z = v0.z + b.z * f_low;

        flFraction = f_low;

        return true;
    }

    bool TraceLine(const glm::vec4& v0, const glm::vec4& v1, glm::vec4& vecIntersection,
                   const Enemy e){
        float flLowestFraction = 1;

        glm::vec4 vecTestIntersection;
        float flTestFraction;

        glm::vec3 min = e.getBBoxMin();
        glm::vec3 max = e.getBBoxMax();
        glm::vec4 pos = e.getPosition();

        min = glm::vec3(min.x + pos.x, min.y + pos.y, min.z + pos.z);
        max = glm::vec3(max.x + pos.x, max.y + pos.y, max.z + pos.z);
        if(LineAABBIntersection(min, max, v0, v1, vecTestIntersection, flTestFraction) && flTestFraction < flLowestFraction)
        {
            vecIntersection = vecTestIntersection;
            flLowestFraction = flTestFraction;
        }

        if (flLowestFraction < 1)
            return true;

        return false;
    }
}
