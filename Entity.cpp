#include "Entity.h"
#include <sstream>

Entity::Entity(const std::string& name, int x, int y, int hp, int level)
    : name(name), x(x), y(y), hp(hp), level(level) {}

void Entity::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Entity::heal(int amount) {
    if (amount < 0) return;
    hp += amount;
    if (hp > 100) hp = 100;
}

void Entity::damage(int amount) {
    if (amount < 0) return;
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Entity::levelUp() {
    level++;
}

void Entity::reset() {
    x = 0;
    y = 0;
    hp = 100;
    level = 1;
}

std::string Entity::toString() const {
    std::ostringstream os;
    os << name << " [pos=(" << x << "," << y << "), hp=" << hp << ", lvl=" << level << "]";
    return os.str();
}
