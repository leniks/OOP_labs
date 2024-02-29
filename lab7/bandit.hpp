#pragma once

#include "npc.hpp"

class Bandit : public NPC {
public:
    Bandit(const std::string &name, int x, int y);
    Bandit(const std::string &name, std::istream &is);

    bool is_bandit() const;

    void print() override;
    
    bool fight(std::shared_ptr<Squirrel> other) override;
    bool fight(std::shared_ptr<Elf> other) override;    
    bool fight(std::shared_ptr<Bandit> other) override;

    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> visitor) override;


    friend std::ostream &operator<<(std::ostream &os, Bandit &bandit);
};