#pragma once

#include "npc.hpp"
#include "visitor.hpp"

class Elf : public NPC {
public:
    Elf(const std::string &name, int x, int y);
    Elf(const std::string &name, std::istream &is);

    void print() override;
    
    bool is_elf() const;

    std::string getType() const override;

    bool fight(std::shared_ptr<Squirrel> other) override;
    bool fight(std::shared_ptr<Elf> other) override;    
    bool fight(std::shared_ptr<Bandit> other) override;

    void save(std::ostream &os) override;

    bool accept(Visitor &visitor) override;

    friend std::ostream &operator<<(std::ostream &os, Elf &elf);
};