#pragma once

#include "npc.hpp"

class Elf : public NPC {
public:
    Elf(const std::string &name, int x, int y);
    Elf(const std::string &name, std::istream &is);

    bool is_elf() const;

    void print() override;

    bool fight(std::shared_ptr<Squirrel> other) override;
    bool fight(std::shared_ptr<Elf> other) override;    
    bool fight(std::shared_ptr<Bandit> other) override;

    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> visitor) override;

    friend std::ostream &operator<<(std::ostream &os, Elf &elf);
};