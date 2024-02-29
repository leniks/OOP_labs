#include "factory.hpp"
#include "visitor.hpp"
#include "observer.hpp"
#include "squirrel.hpp"
#include "elf.hpp"
#include "bandit.hpp"

std::shared_ptr<NPC> factory(const std::string &name, std::istream &is, const std::string &filename) {
    std::shared_ptr<NPC> result;
    int type = 0;
    if (is >> type) {
        switch (type) {
            case SquirrelType:
                result = std::make_shared<Squirrel>(name, is);
                break;
            case ElfType:
                result = std::make_shared<Elf>(name, is);
                break;
            case BanditType:
                result = std::make_shared<Bandit>(name, is);
                break;
            default:
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
        case SquirrelType:
            result = std::make_shared<Squirrel>(name, x, y);
            break;
        case ElfType:
            result = std::make_shared<Elf>(name, x, y);
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

set_t fight(const set_t &array, size_t distance) {
    set_t dead_list;
    for (const auto &attacker : array) {
        for (const auto &defender : array) {
            if ((attacker != defender) && (attacker->is_close(defender, distance))) {
                NPCVisitor visitor(attacker);
                bool success = defender->accept(visitor);
                if (success) {
                    dead_list.insert(defender);
                }
            }
        }
    }
    return dead_list;
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
    }
    else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

std::ostream &operator<<(std::ostream &os, const set_t &array) {
    for (auto &n : array)
        n->print();
    return os;
}