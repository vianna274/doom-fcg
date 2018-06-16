#include "gun.hpp"
#include <GLFW/glfw3.h>

Gun::Gun() {

}
Gun::Gun(char const * name, int id, int bullets, int reloads, float delayFire, float delayReload) {
  this->name = name;
  this->id = id;
  this->reloads = reloads;
  this->delayFire = delayFire;
  this->delayReload = delayReload;
  this->bullets = bullets;
  this->maxBullets = bullets;
  this->lastShot = 0.0f;
}

char const * Gun::getName() {
    return name;
}

void Gun::setName(char const * newName) {
  name = newName;
}

int Gun::getId() {
  return id;
}

void Gun::setId(int newId) {
  id = newId;
}

void Gun::setBullets(int newBullets) {
  bullets = newBullets;
}

int Gun::getBullets() {
  return bullets;
}

void Gun::setReloads(int newReloads) {
    reloads = newReloads;
}

int Gun::getReloads() {
  return reloads;
}

void Gun::setDelayFire(float newDelayFire) {
  delayFire = newDelayFire;
}

float Gun::getDelayFire() {
  return delayFire;
}

void Gun::setDelayReload(float newDelayReload) {
  delayReload = newDelayReload;
}

float Gun::getDelayReload() {
  return delayReload;
}

bool Gun::shoot() {
  if (bullets > 0 && (glfwGetTime() - lastShot >= delayFire)) {
    lastShot = glfwGetTime();
    bullets--;
    return true;
  }
  return false;
}

bool Gun::reload() {
  if (reloads > 0) {
    bullets = maxBullets;
    reloads--;
    return true;
  }
  return false;
}
