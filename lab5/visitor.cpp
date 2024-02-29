#include "npc.hpp"
#include "visitor.hpp"
#include "squirrel.hpp"
#include "elf.hpp"
#include "bandit.hpp"

NPCVisitor::NPCVisitor(std::shared_ptr<NPC> attacker) : attacker_(attacker) {}

bool NPCVisitor::visit(Elf& elf) {
    return attacker_->fight(std::make_shared<Elf>(elf));
}

bool NPCVisitor::visit(Squirrel& squirrel) {
    return attacker_->fight(std::make_shared<Squirrel>(squirrel));
}

bool NPCVisitor::visit(Bandit& bandit) {
    return attacker_->fight(std::make_shared<Bandit>(bandit));
}