#ifndef _gun_h
#define _gun_h
#include <SFML/Audio.hpp>

class Gun {
    char const * name;
    int id, bullets, reloads, maxBullets;
    float lastShot, lastReload, delayFire, delayReload;
  public:
    Gun();
    Gun(char const * name, int id, int bullets, int reloads, float delayFire, float delayReload);
    char const * getName();
    void setName(char const * newName);
    int getId();
    void setId(int newId);
    void setBullets(int newBullets);
    int getBullets();
    void setReloads(int newReloads);
    int getReloads();
    void setDelayFire(float newDelayFire);
    float getDelayFire();
    void setDelayReload(float newDelayReload);
    float getDelayReload();
    bool shoot();
    bool reload();
};
#endif
