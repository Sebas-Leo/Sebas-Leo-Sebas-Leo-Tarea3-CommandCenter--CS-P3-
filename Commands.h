#ifndef COMMANDS_H
#define COMMANDS_H

#include "Entity.h"
#include <list>
#include <string>

void statusCmd(Entity& e, const std::list<std::string>& args);


class HealLimited {
    Entity& target;
    int maxUsos;
    int usados;
public:
    HealLimited(Entity& e, int maxUsos) : target(e), maxUsos(maxUsos), usados(0) {}
    void operator()(const std::list<std::string>& args);

    int getUsados() const { return usados; }
    int getRestantes() const { return maxUsos - usados; }
};


class DamageTracker {
    Entity& target;
    int veces;
    int totalDano;
public:
    DamageTracker(Entity& e) : target(e), veces(0), totalDano(0) {}
    void operator()(const std::list<std::string>& args);

    int getVeces() const { return veces; }
    int getTotalDano() const { return totalDano; }
};

#endif
