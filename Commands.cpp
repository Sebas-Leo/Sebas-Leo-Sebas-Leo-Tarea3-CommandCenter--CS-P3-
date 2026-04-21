#include "Commands.h"
#include <iostream>
#include <stdexcept>

void statusCmd(Entity& e, const std::list<std::string>& args) {
    if (!args.empty()) {
        throw std::invalid_argument("status no lleva argumentos");
    }
    std::cout << "  >> " << e.toString() << "\n";
}


void HealLimited::operator()(const std::list<std::string>& args) {
    if (usados >= maxUsos) {
        throw std::runtime_error("ya no quedan usos de heal_limited");
    }
    if (args.size() != 1) {
        throw std::invalid_argument("heal_limited necesita 1 argumento");
    }

    int cant;
    try {
        cant = std::stoi(args.front());
    } catch (...) {
        throw std::invalid_argument("se esperaba un numero entero");
    }
    if (cant < 0) {
        throw std::invalid_argument("la cantidad no puede ser negativa");
    }

    target.heal(cant);
    usados++;
}


void DamageTracker::operator()(const std::list<std::string>& args) {
    if (args.size() != 1) {
        throw std::invalid_argument("damage necesita 1 argumento");
    }

    int cant;
    try {
        cant = std::stoi(args.front());
    } catch (...) {
        throw std::invalid_argument("se esperaba un numero entero");
    }
    if (cant < 0) {
        throw std::invalid_argument("la cantidad no puede ser negativa");
    }

    target.damage(cant);
    veces++;
    totalDano += cant;
}
