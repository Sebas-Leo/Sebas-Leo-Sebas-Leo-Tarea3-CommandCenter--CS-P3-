#ifndef COMMAND_CENTER_H
#define COMMAND_CENTER_H

#include "Entity.h"
#include <functional>
#include <list>
#include <map>
#include <string>
#include <utility>

using Command = std::function<void(const std::list<std::string>&)>;

using MacroStep = std::pair<std::string, std::list<std::string>>;

class CommandCenter {
private:
    Entity& entity;
    std::map<std::string, Command> commands;
    std::map<std::string, std::list<MacroStep>> macros;
    std::list<std::string> history;

public:
    CommandCenter(Entity& e);

    void registerCommand(const std::string& name, Command cmd);
    bool removeCommand(const std::string& name);
    void execute(const std::string& name, const std::list<std::string>& args);

    void registerMacro(const std::string& name, const std::list<MacroStep>& steps);
    void executeMacro(const std::string& name);

    void showHistory() const;
    void listCommands() const;
};

#endif
