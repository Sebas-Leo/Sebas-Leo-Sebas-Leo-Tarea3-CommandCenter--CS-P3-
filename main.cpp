#include "Entity.h"
#include "CommandCenter.h"
#include "Commands.h"

#include <iostream>
#include <list>
#include <string>

int main() {
    Entity hero("Sigmund", 0, 0, 100, 1);
    CommandCenter cc(hero);

    std::cout << "\n=== 1) Registrando comandos ===\n";

    cc.registerCommand("status", [&hero](const std::list<std::string>& args) {
        statusCmd(hero, args);
    });

    cc.registerCommand("move", [&hero](const std::list<std::string>& args) {
        if (args.size() != 2) throw std::invalid_argument("move necesita 2 argumentos (dx dy)");
        auto it = args.begin();
        int dx = std::stoi(*it++);
        int dy = std::stoi(*it);
        hero.move(dx, dy);
    });

    cc.registerCommand("levelup", [&hero](const std::list<std::string>& args) {
        if (!args.empty()) throw std::invalid_argument("levelup no lleva argumentos");
        hero.levelUp();
    });

    cc.registerCommand("reset", [&hero](const std::list<std::string>& args) {
        if (!args.empty()) throw std::invalid_argument("reset no lleva argumentos");
        hero.reset();
    });

    HealLimited healL(hero, 3);
    cc.registerCommand("heal_limited", std::ref(healL));

    DamageTracker dmg(hero);
    cc.registerCommand("damage", std::ref(dmg));

    cc.listCommands();

    std::cout << "\n=== 2) Funcion libre: status (3 ejemplos) ===\n";
    std::list<std::string> vacio;

    cc.execute("status", vacio);
    cc.execute("status", {"sobra"});
    hero.move(5, 5);
    cc.execute("status", vacio);

    std::cout << "\n=== 3) Lambdas: move, levelup, reset (ejemplos varios) ===\n";

    cc.execute("move", {"10", "20"});
    cc.execute("move", {"-3", "7"});
    cc.execute("move", {"solo_uno"});
    cc.execute("levelup", vacio);
    cc.execute("levelup", vacio);
    cc.execute("reset", vacio);

    std::cout << "\n=== 4) Functores: heal_limited y damage ===\n";

    cc.execute("damage", {"30"});
    cc.execute("heal_limited", {"10"});
    cc.execute("heal_limited", {"10"});
    cc.execute("heal_limited", {"10"});
    cc.execute("heal_limited", {"10"});

    std::cout << "heal_limited: usados=" << healL.getUsados()
              << " restantes=" << healL.getRestantes() << "\n";

    cc.execute("damage", {"15"});
    cc.execute("damage", {"5"});
    cc.execute("damage", {"xyz"});

    std::cout << "damage: veces=" << dmg.getVeces()
              << " total=" << dmg.getTotalDano() << "\n";

    std::cout << "\n=== 5) Casos invalidos ===\n";

    cc.execute("fly", vacio);
    cc.execute("move", vacio);
    cc.execute("damage", {"-50"});

    std::cout << "\n=== 6) Macros ===\n";

    std::list<MacroStep> m1;
    m1.push_back({"heal_limited", {"20"}});
    m1.push_back({"status", {}});
    cc.registerMacro("heal_and_status", m1);

    std::list<MacroStep> m2 = {
        {"move", {"1", "0"}},
        {"move", {"0", "1"}},
        {"move", {"-1", "0"}},
        {"move", {"0", "-1"}},
        {"status", {}}
    };
    cc.registerMacro("patrol", m2);

    std::list<MacroStep> m3 = {
        {"damage", {"25"}},
        {"damage", {"10"}},
        {"levelup", {}},
        {"status", {}}
    };
    cc.registerMacro("combat_round", m3);

    cc.executeMacro("heal_and_status");
    cc.executeMacro("patrol");
    cc.executeMacro("combat_round");

    std::cout << "\n=== 7) Macro con comando inexistente (debe detenerse) ===\n";

    std::list<MacroStep> roto = {
        {"status", {}},
        {"fly", {}},
        {"levelup", {}}
    };
    cc.registerMacro("macro_roto", roto);
    cc.executeMacro("macro_roto");

    std::cout << "\n=== 8) Eliminacion dinamica ===\n";

    cc.removeCommand("levelup");
    cc.execute("levelup", vacio);
    cc.removeCommand("levelup");
    cc.executeMacro("combat_round");

    std::cout << "\n=== 9) Estado final + historial ===\n";
    std::cout << "estado final: " << hero.toString() << "\n";
    cc.showHistory();

    return 0;
}
