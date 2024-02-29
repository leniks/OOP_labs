#pragma once

#include <memory>
#include <string>
#include <fstream>

class NPC;

class IFightObserver {
public:
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
    virtual ~IFightObserver() = default;
};

class TextObserver : public IFightObserver {
public:
    static std::shared_ptr<IFightObserver> get();
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
};

class FileObserver : public IFightObserver {
private:
    std::ofstream file;
public:
    FileObserver(const std::string &filename);
    static std::shared_ptr<IFightObserver> get(const std::string &filename);
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
    ~FileObserver();
};