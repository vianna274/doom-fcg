#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "player.hpp"

using namespace glm;

Player::Player (vec4 newPosition, float newSpeed) {
  position = newPosition;
  speed = newSpeed;
}

void Player::setPosition (vec4 newPosition) {
  position = newPosition;
}

void Player::move(glm::vec4 u,glm::vec4 w) {
  // You need to add or sub W or U vector to player_pos
  if (w_player_moving) {
    position.x = position.x - speed * w.x;
    position.z = position.z - speed * w.z;
  }
  if (s_player_moving) {
    position.x = position.x + speed * w.x;
    position.z = position.z + speed * w.z;
  }
  if (a_player_moving) {
    position.x = position.x - speed * u.x;
    position.z = position.z - speed * u.z;
  }
  if (d_player_moving) {
    position.x = position.x + speed * u.x;
    position.z = position.z + speed * u.z;
  }
}

void Player::setA(bool opt) {
  a_player_moving = opt;
}

void Player::setD(bool opt) {
  d_player_moving = opt;
}

void Player::setS(bool opt) {
  s_player_moving = opt;
}

void Player::setW(bool opt) {
  w_player_moving = opt;
}

void Player::setSpeed(float newSpeed) {
  speed = newSpeed;
}

vec4 Player::getPosition() {
  return position;
}

float Player::getSpeed() {
  return speed;
}
