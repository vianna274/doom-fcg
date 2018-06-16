#include "collision.hpp"
#include <utility>
#include <algorithm>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "enemy.hpp"

namespace collision
{
    bool ClipLine(int d, const glm::vec3 bbox_min, const glm::vec3 bbox_max, const glm::vec4& v0,
                  const glm::vec4& v1, float& flow, float& fhigh){
        float max = v1[d], min = v0[d], fdimlow, fdimhigh;

        if(min > max)
            std::swap(min, max);

        fdimlow = (bbox_min[d] - min) / (max - min);
        fdimhigh = (bbox_max[d] - min) / (max - min);

        if(fdimlow > fdimhigh) std::swap(fdimlow, fdimhigh);

        if((fdimhigh < flow) || (fdimlow > fhigh)) return false;

        flow = std::max(flow, fdimlow);
        fhigh = std::min(fhigh, fdimhigh);
        
        return flow > fhigh;
    }

    bool LineAABBIntersection(const glm::vec3 bbox_min, const glm::vec3 bbox_max, const glm::vec4& v0,
                              const glm::vec4& v1){
        float flow = 0, fhigh = 1;

        return ((ClipLine(0, bbox_min, bbox_max, v0, v1, flow, fhigh)) && (ClipLine(1, bbox_min, bbox_max, v0, v1, flow, fhigh))
                && (ClipLine(2, bbox_min, bbox_max, v0, v1, flow, fhigh)));
    }

    bool TraceLine(const glm::vec4& v0, const glm::vec4& v1, const Enemy e){
        glm::vec3 min = e.getBBoxMin();
        glm::vec3 max = e.getBBoxMax();
        glm::vec4 pos = e.getPosition();

        min = glm::vec3(min.x + pos.x, min.y + pos.y, min.z + pos.z);
        max = glm::vec3(max.x + pos.x, max.y + pos.y, max.z + pos.z);
        if(LineAABBIntersection(min, max, v0, v1))
            return true;

        return false;
    }
}
