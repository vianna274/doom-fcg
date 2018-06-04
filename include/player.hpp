#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef _player_h
#define _player_h

using namespace glm;

class Player {
    vec4 position, lastPosition;
    bool w_player_moving;
    bool a_player_moving;
    bool s_player_moving;
    bool d_player_moving;
    float speed;

  public:
    Player(vec4 newPosition, float speed);
    void setA(bool opt);
    void setW(bool opt);
    void setS(bool opt);
    void setD(bool opt);
    void setPosition(vec4 newPosition);
    void move(vec4 u,vec4 w);
    void unmove();
    void jump(float height);
    void die();
    void setSpeed(float newSpeed);
    float getSpeed();
    vec4 getPosition();
};

#endif
