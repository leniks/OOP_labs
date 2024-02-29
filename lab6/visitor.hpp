#pragma once

#include <memory>

class NPC;
class Squirrel;
class Elf;
class Bandit;

class Visitor {
public:
    virtual ~Visitor() = default;

    virtual bool visit(Squirrel& squirrel) = 0;
    virtual bool visit(Elf& elf) = 0;
    virtual bool visit(Bandit& bandit) = 0;
};

class NPCVisitor : public Visitor {
public:
    NPCVisitor(std::shared_ptr<NPC> attacker);
    
    bool visit(Squirrel& squirrel) override;
    bool visit(Elf& elf) override;
    bool visit(Bandit& bandit) override;

private:
    std::shared_ptr<NPC> attacker_;
};