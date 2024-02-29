#include "npc.hpp"
#include "squirrel.hpp"
#include "elf.hpp"

#include "bandit.hpp"

Bandit::Bandit(const std::string &name, int x, int y) : NPC(BanditType, name, x, y) {}
Bandit::Bandit(const std::string &name, std::istream &is) : NPC(BanditType, name, is) {}

void Bandit::print() {
    std::cout << *this;
}

bool Bandit::is_bandit() const {
    return true;
}

bool Bandit::fight(std::shared_ptr<Squirrel> other) {
    fight_notify(other, true);
    return true;
}

bool Bandit::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false);
    return false;
}

bool Bandit::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Bandit>(this,[](Bandit*){}));
}

bool Bandit::fight(std::shared_ptr<Bandit> other) {
    fight_notify(other, false);
    return false;
}

void Bandit::save(std::ostream &os) {
    os << BanditType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Bandit &bandit) {
    os << "bandit: " << *static_cast<NPC *>(&bandit) << std::endl;
    return os;
}