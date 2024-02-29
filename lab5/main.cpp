#include <iostream>
#include "observer.hpp"
#include "npc.hpp"
#include "visitor.hpp"
#include "factory.hpp"
#include "squirrel.hpp"
#include "elf.hpp"
#include "bandit.hpp"

int main() {
    set_t array;

    std::string NameArray[10] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };

    std::srand(time(NULL));
    for (size_t i = 0; i < 10; ++i) {
        array.insert(factory(NpcType(std::rand() % 3 + 1), NameArray[i], std::rand() % 100, std::rand() % 100, "log.txt"));
    }
    std::cout << "Saving ..." << std::endl;
    save(array, "log.txt");

    std::cout << "Fighting ..." << std::endl << array;

    for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 10) {
        auto dead_list = fight(array, distance);
        for (auto &d : dead_list)
            array.erase(d);
        std::cout << "\nFight stats ----------" << std::endl
                << "distance: " << distance << std::endl
                << "killed: " << dead_list.size() << std::endl
                << std::endl << std::endl;
    }

    std::cout << "Survivors:\n" << array;

    return 0;

}