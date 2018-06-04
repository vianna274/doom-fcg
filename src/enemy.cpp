#include <cstdio>
#include <GLFW/glfw3.h>  // Criação de janelas do sistema operacional
#include "player.hpp"
#include "enemy.hpp"
#include "support.h"

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
}

void Enemy::setPosition (vec4 newPosition) {
  position = newPosition;
}

void Enemy::move(vec4 u, vec4 w, vec4 playerPos) {
  lastPosition = position;
  if(!attackEnable && (glfwGetTime() - timeLastAttack) >= delay)
    attackEnable = true;

  if (!chasePlayer(playerPos))
    return;

  if (playerPos.x > position.x) {
    if (playerPos.z > position.z) {
      position.x = position.x + speed;
      position.z = position.z + speed;
    } else {
      position.x = position.x + speed;
      position.z = position.z - speed;
    }
  } else {
    if (playerPos.z > position.z) {
      position.x = position.x - speed;
      position.z = position.z + speed;
    } else {
      position.x = position.x - speed;
      position.z = position.z - speed;
    }
  }
}

void Enemy::unmove() {
  position = lastPosition;
}

void Enemy::setSpeed(float newSpeed) {
  speed = newSpeed;
}

vec4 Enemy::getPosition() {
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

void Enemy::hit(Player* player) {
  if (attackEnable) {
    player->setHealth(player->getHealth() - damage);
    timeLastAttack = glfwGetTime();
    attackEnable = false;
  }
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
