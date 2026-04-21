#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
private:
    std::string name;
    int x, y;
    int hp;
    int level;

public:
    Entity(const std::string& name, int x, int y, int hp, int level);

    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getHP() const { return hp; }
    int getLevel() const { return level; }

    void move(int dx, int dy);
    void heal(int amount);
    void damage(int amount);
    void levelUp();
    void reset();

    std::string toString() const;
};

#endif
