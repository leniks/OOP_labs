#include "npc.hpp"

NPC::NPC(NpcType t, const std::string &_name, int _x, int _y) : type(t), name(_name), x(_x), y(_y) {}

NPC::NPC(NpcType t, const std::string &_name, std::istream &is) : type(t), name(_name) {
    is >> name;
    is >> x;
    is >> y;
}

const std::string& NPC::getName() const { 
    return name; 
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto &o : observers) {
        o->on_fight(shared_from_this(), defender, win);
    }
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const {
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2))
        return true;
    else
        return false;
}

void NPC::save(std::ostream &os) {
    os << name << " {" << x << ", " << y << "} " << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    os << npc.name << " {" << npc.x << ", " << npc.y << "} ";
    return os;
}