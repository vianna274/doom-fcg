#include <cstdio>
#include <GLFW/glfw3.h>  // Criação de janelas do sistema operacional
#include "player.hpp"
#include "enemy.hpp"
#include "support.h"
#include "object.hpp"

#define CUBE_SIZE_B 0.3
#define CUBE_SIZE_C 0.5

using namespace glm;

Enemy::Enemy(vec4 position, float speed, const char * name, int id, float vision,
      float damage, float health) {
  this->position = position;
  this->speed = speed;
  this->name = name;
  this->id = id;
  this->vision = vision;
  this->damage = damage;
  this->health = health;
  this->delay = 3;
  this->timeLastAttack = 0;
  this->attackEnable = true;
  this->direction = vec4(0,0,1,0);
  this->bbox_min = vec3(0,0,0);
  this->bbox_max = vec3(0,0,0);
  if(this->id == 6){ //If it is the cow
      this->h = CUBE_SIZE_C; // Height
      this->w = CUBE_SIZE_C; // Width
      this->d = CUBE_SIZE_C; // Depth
  }
  else{ //Bunny
      this->h = CUBE_SIZE_B; // Height
      this->w = CUBE_SIZE_B; // Width
      this->d = CUBE_SIZE_B; // Depth
  }
}

void Enemy::updateBBox(){
    bbox_min.x = position.x - w;
    bbox_min.y = position.y - h;
    bbox_min.z = position.z - d;

    bbox_max.x = position.x + w;
    bbox_max.y = position.y + h;
    bbox_max.z = position.z + d;
}

vec3 Enemy::getBBoxMax() const {
    return bbox_max;
}

void Enemy::setBBoxMax(vec3 n_bbox_max) {
    this->bbox_max = n_bbox_max;
}

void Enemy::setBBoxMin(vec3 n_bbox_min) {
    this->bbox_min = n_bbox_min;
}

vec3 Enemy::getBBoxMin() const {
    return bbox_min;
}

vec4 Enemy::getDirection() const {
    return direction;
}

void Enemy::setDirection(vec4 direction) {
    this->direction = direction;
}
void Enemy::setPosition (vec4 newPosition) {
  position = newPosition;
}

void Enemy::move(vec4 u, vec4 w, vec4 playerPos) {
  lastPosition = position;
  vec4 newPosition;
  if(!attackEnable && (glfwGetTime() - timeLastAttack) >= delay)
    attackEnable = true;

  if (!chasePlayer(playerPos))
    return;

  newPosition = (playerPos - position) * speed;
  position.x += newPosition.x;
  position.z += newPosition.z;

  if (ObjectStatic::inRange(getPosition(), playerPos, 1.0f))
    unmove();
}

void Enemy::unmove() {
  position = lastPosition;
}

void Enemy::setSpeed(float newSpeed) {
  speed = newSpeed;
}

vec4 Enemy::getPosition() const {
  return position;
}

float Enemy::getSpeed() {
  return speed;
}

char const * Enemy::getName() {
    return name;
}

void Enemy::setName(char const * newName) {
  name = newName;
}

int Enemy::getId() {
  return id;
}

void Enemy::setId(int newId) {
  id = newId;
}

float Enemy::getDamage() {
  return damage;
}

float Enemy::getHealth() {
  return health;
}

bool Enemy::hit(Player* player) {
  if (attackEnable) {
    player->setHealth(player->getHealth() - damage);
    timeLastAttack = glfwGetTime();
    attackEnable = false;
    return true;
  }
  return false;
}

int Enemy::chasePlayer(vec4 playerPos) {
  if ((playerPos.x - position.x) > vision ||
      (playerPos.x - position.x) < -vision ||
      (playerPos.z - position.z) < -vision ||
      (playerPos.z - position.z) > vision)
     return 0;
  else
    return 1;
}

void Enemy::setHealth(float newHealth) {
  health = newHealth;
}
