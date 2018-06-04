#ifndef _gun_h
#define _gun_h

class Gun {
    char const * name;
    int id;
  public:
    Gun(char const * name, int id);
    char const * getName();
    void setName(char const * newName);
    int getId();
    void setId(int newId);
};
#endif
