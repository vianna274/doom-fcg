#include "gun.hpp"

Gun::Gun(char const * name, int id) {
  this->name = name;
  this->id = id;
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
