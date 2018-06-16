#include "collision.hpp"
#include <utility>
#include <algorithm>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "enemy.hpp"

namespace collision
{
    bool ClipLine(int d, const glm::vec3 bbox_min, const glm::vec3 bbox_max, const glm::vec4& v0,
                  const glm::vec4& v1, float& flow, float& fhigh){
        float max = v1[d], min = v0[d], fdimlow, fdimhigh;

        //if(min > max)
            //std::swap(min, max);

        fdimlow = (bbox_min[d] - min) / (max - min);
        fdimhigh = (bbox_max[d] - min) / (max - min);
        std::cout << "fdlow:" << fdimlow << " fdhigh:" << fdimhigh  << " dim:" << d << std::endl;
        std::cout << "flow:" << flow << " fhigh:" << fhigh  << " dim:" << d << std::endl;

        if(fdimlow > fdimhigh) std::swap(fdimlow, fdimhigh);

        if((fdimhigh < flow) || (fdimlow > fhigh)) return false;

        flow = std::max(flow, fdimlow);
        fhigh = std::min(fhigh, fdimhigh);
        
        return flow < fhigh;
    }

    bool LineAABBIntersection(const glm::vec3 bbox_min, const glm::vec3 bbox_max, const glm::vec4& v0,
                              const glm::vec4& v1, float& flow, float& fhigh){
        return ((ClipLine(0, bbox_min, bbox_max, v0, v1, flow, fhigh)) && (ClipLine(1, bbox_min, bbox_max, v0, v1, flow, fhigh))
                && (ClipLine(2, bbox_min, bbox_max, v0, v1, flow, fhigh)));
    }

    bool TraceLine(const glm::vec4& v0, const glm::vec4& v1, const Enemy e){
        glm::vec3 min = e.getBBoxMin();
        glm::vec3 max = e.getBBoxMax();
        glm::vec4 pos = e.getPosition();
        float flow = 0, fhigh = 1;

        if(LineAABBIntersection(min, max, v0, v1, flow, fhigh)){
            std::cout << "flow:" << flow << " fhigh:" << fhigh  << std::endl;
            return true;
        }

        return false;
    }
}
