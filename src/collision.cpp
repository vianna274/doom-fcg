#include "collision.hpp"
#include <utility>
#include <algorithm>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "enemy.hpp"
#include "wall.hpp"

namespace collision
{
    //Clips a line to check if theres is a hit in that dimension and if it is in the same interval
    //as the other dimensions
    bool ClipLine(int d, const glm::vec3 bbox_min, const glm::vec3 bbox_max, const glm::vec4& v0,
                  const glm::vec4& v1, float& flow, float& fhigh){
        float max = v1[d], min = v0[d], fdimlow, fdimhigh;

        fdimlow = (bbox_min[d] - min) / (max - min);
        fdimhigh = (bbox_max[d] - min) / (max - min);

        if(fdimlow > fdimhigh) std::swap(fdimlow, fdimhigh);

        if((fdimhigh < flow) || (fdimlow > fhigh)) return false;

        flow = std::max(flow, fdimlow);
        fhigh = std::min(fhigh, fdimhigh);
        
        return flow < fhigh;
    }

    //Checks if the three clipped dimensions hit anything
    bool LineAABBIntersection(const glm::vec3 bbox_min, const glm::vec3 bbox_max, const glm::vec4& v0,
                              const glm::vec4& v1, float& flow, float& fhigh){
        return ((ClipLine(0, bbox_min, bbox_max, v0, v1, flow, fhigh)) && (ClipLine(1, bbox_min, bbox_max, v0, v1, flow, fhigh))
                && (ClipLine(2, bbox_min, bbox_max, v0, v1, flow, fhigh)));
    }

    //Upperlevel function to check which objects have been hit and choose which one is effectively
    //hit
    bool TraceLine(const glm::vec4& v0, const glm::vec4& v1, const Enemy e, const std::vector<Wall> walls){
        glm::vec3 min = e.getBBoxMin();
        glm::vec3 max = e.getBBoxMax();

        float flowest = 1;
        //Needs to fix this, maybe other function
        for(auto x : walls) {
            float flow = 0, fhigh = 1;
            if(LineAABBIntersection(x.bbox_min, x.bbox_max, v0, v1, flow, fhigh) && flow < flowest)
                flowest = flow;
        }

        float flow = 0, fhigh = 1;
        bool hit = LineAABBIntersection(min, max, v0, v1, flow, fhigh);
        //return  hit && (flowest > flow);
        return  hit;
    }
}
