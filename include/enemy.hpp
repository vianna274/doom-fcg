#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "player.hpp"

#ifndef _enemy_h
#define _enemy_h

using namespace glm;

class Enemy {
    vec4 position, lastPosition;
    const char * name;
    int id;
    float speed, vision, damage, health, delay, timeLastAttack;
    bool attackEnable;
  public:
    Enemy(vec4 position, float speed, const char * name, int id, float vision,
          float damage, float health);
    void setPosition(vec4 newPosition);
    void move(vec4 u, vec4 w, vec4 playerPos);
    void unmove();
    void die();
    void setSpeed(float newSpeed);
    float getSpeed();
    vec4 getPosition();
    int chasePlayer(vec4 playerPos);
    char const * getName();
    void setName(char const * newName);
    int getId();
    void setId(int newId);
    float getDamage();
    float getHealth();
    void setHealth(float newHealth);
    void hit(Player* player);
};

#endif