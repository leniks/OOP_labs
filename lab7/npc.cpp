#include "npc.hpp"
#include "bandit.hpp"
#include "elf.hpp"
#include "squirrel.hpp"
#include "observer.hpp"

NPC::NPC(NpcType t, const std::string &_name, int _x, int _y) : type(t), name(_name), x(_x), y(_y) {}

NPC::NPC(NpcType t, const std::string &_name, std::istream &is) : type(t), name(_name) {
    is >> name;
    is >> x;
    is >> y;
}

const std::string& NPC::getName() const { 
    return name; 
}
NpcType NPC::getType() {
    std::lock_guard<std::mutex> lck(mtx);
    return type;
}

std::pair<int,int> NPC::position() {
    std::lock_guard<std::mutex> lck(mtx);
    return {x, y};

}
void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto &o : observers)
        o->on_fight(std::shared_ptr<NPC>(this, [](NPC *) {}), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) {
    auto [other_x, other_y] = other->position();
    std::lock_guard<std::mutex> lck(mtx);
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

void NPC::move(int shift_x, int shift_y, int max_x, int max_y) {
    std::lock_guard<std::mutex> lck(mtx);

    if ((x + shift_x >= 0) && (x + shift_x <= max_x))
        x+= shift_x;
    if ((y + shift_y >= 0) && (y + shift_y <= max_y))
        y+= shift_y;
}

bool NPC::is_alive() {
    std::lock_guard<std::mutex> lck(mtx);
    return alive;
}

void NPC::must_die() {
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}

std::shared_ptr<NPC> factory(const std::string &name, std::istream &is, const std::string &filename) {
    std::shared_ptr<NPC> result;
    int type = 0;
    if (is >> type) {
        switch (type) {
            case ElfType:
                result = std::make_shared<Elf>(name, is);
                break;
            case SquirrelType:
                result = std::make_shared<Squirrel>(name, is);
                break;
            case BanditType:
                result = std::make_shared<Bandit>(name, is);
                break;
        }
    } else {
        std::cerr << "wrong NPC type: " << type << std::endl;
    } 
    if (result) {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get(filename));
    }
    return result;
}

std::shared_ptr<NPC> factory(NpcType type, const std::string &name, int x, int y, const std::string &filename) {
    std::shared_ptr<NPC> result;
    switch (type) {
        case ElfType:
            result = std::make_shared<Elf>(name, x, y);
            break;
        case SquirrelType:
            result = std::make_shared<Squirrel>(name, x, y);
            break;
        case BanditType:
            result = std::make_shared<Bandit>(name, x, y);
            break;
        default:
            break;
    } 
    if (result) {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get(filename));
    }
    return result;
}

void save(const set_t &array, const std::string &filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string &name, const std::string &filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(factory(name, is, filename));
        is.close();
    } else {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    }
    return result;
}

set_t fight(const set_t &array, size_t distance) {
    set_t dead_list;
    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) && attacker->is_close(defender, distance) &&defender->accept(attacker)) {
                dead_list.insert(defender);
            }
    return dead_list;
}

std::ostream &operator<<(std::ostream &os, const set_t &array) {
    for (auto &n : array)
        n->print();
    return os;
}