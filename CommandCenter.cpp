#include "CommandCenter.h"
#include <iostream>
#include <sstream>

CommandCenter::CommandCenter(Entity& e) : entity(e) {}

void CommandCenter::registerCommand(const std::string& name, Command cmd) {
    std::map<std::string, Command>::iterator it = commands.find(name);
    if (it != commands.end()) {
        it->second = cmd;
        std::cout << "[aviso] '" << name << "' ya estaba registrado, se sobrescribio\n";
        return;
    }
    commands[name] = cmd;
}

bool CommandCenter::removeCommand(const std::string& name) {
    std::map<std::string, Command>::iterator it = commands.find(name);
    if (it == commands.end()) {
        std::cout << "[error] no existe el comando '" << name << "'\n";
        return false;
    }
    commands.erase(it);
    std::cout << "[ok] comando '" << name << "' eliminado\n";
    return true;
}

void CommandCenter::execute(const std::string& name, const std::list<std::string>& args) {
    std::map<std::string, Command>::iterator it = commands.find(name);
    if (it == commands.end()) {
        std::cout << "[error] comando no encontrado: '" << name << "'\n";
        return;
    }

    std::string antes = entity.toString();

    try {
        it->second(args);
    } catch (std::exception& e) {
        std::cout << "[error] " << name << ": " << e.what() << "\n";
        return;
    }

    std::string despues = entity.toString();

    std::ostringstream reg;
    reg << name << " -> " << antes << " => " << despues;
    history.push_back(reg.str());
}

void CommandCenter::registerMacro(const std::string& name, const std::list<MacroStep>& steps) {
    macros[name] = steps;
}

void CommandCenter::executeMacro(const std::string& name) {
    auto macroIt = macros.find(name);
    if (macroIt == macros.end()) {
        std::cout << "[error] macro no encontrado: '" << name << "'\n";
        return;
    }

    std::cout << ">> ejecutando macro '" << name << "'\n";

    std::list<MacroStep>& pasos = macroIt->second;
    for (std::list<MacroStep>::iterator it = pasos.begin(); it != pasos.end(); ++it) {
        if (commands.find(it->first) == commands.end()) {
            std::cout << "[error] macro '" << name << "' detenido: '"
                      << it->first << "' no existe\n";
            return;
        }
        execute(it->first, it->second);
    }
}

void CommandCenter::showHistory() const {
    std::cout << "---- historial ----\n";
    if (history.empty()) {
        std::cout << "(vacio)\n";
        return;
    }
    int i = 1;
    for (std::list<std::string>::const_iterator it = history.begin(); it != history.end(); ++it) {
        std::cout << i++ << ") " << *it << "\n";
    }
}

void CommandCenter::listCommands() const {
    std::cout << "---- comandos registrados ----\n";
    for (auto it = commands.begin(); it != commands.end(); ++it) {
        std::cout << " * " << it->first << "\n";
    }
}
