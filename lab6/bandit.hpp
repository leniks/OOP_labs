#pragma once

#include "npc.hpp"
#include "visitor.hpp"

class Bandit : public NPC {
public:
    Bandit(const std::string &name, int x, int y);
    Bandit(const std::string &name, std::istream &is);

    void print() override;
    
    bool is_bandit() const;

    std::string getType() const override;

    bool fight(std::shared_ptr<Squirrel> other) override;
    bool fight(std::shared_ptr<Elf> other) override;    
    bool fight(std::shared_ptr<Bandit> other) override;

    void save(std::ostream &os) override;

    bool accept(Visitor &visitor) override;

    friend std::ostream &operator<<(std::ostream &os, Bandit &bandit);
};