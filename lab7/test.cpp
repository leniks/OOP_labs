#include <gtest/gtest.h>

#include "npc.hpp"
#include "observer.hpp"
#include "elf.hpp"
#include "squirrel.hpp"
#include "bandit.hpp"

TEST(FightTest1, ElfVsSquirrel) {
    auto elf = factory(ElfType, "Elf", 0, 0, "test_fight.txt");
    auto squirrel = factory(SquirrelType, "Squirrel", 1, 1, "test_fight.txt"); //! will be alive
    ASSERT_TRUE(elf->accept(squirrel));
    ASSERT_TRUE(squirrel->is_alive());
}

TEST(FightTest1, ElfVsBandit) {
    testing::internal::CaptureStdout();

    auto elf = factory(ElfType, "Elf", 0, 0, "test_fight.txt");
    auto bandit = factory(BanditType, "Bandit", 1, 1, "test_fight.txt"); //! will be killed
    ASSERT_TRUE(bandit->accept(elf));
    bandit->must_die();

    ASSERT_TRUE(elf->is_alive());
    ASSERT_FALSE(bandit->is_alive());

    testing::internal::GetCapturedStdout();
}

TEST(FightTest2, MainFighting) {
    testing::internal::CaptureStdout();
    
    set_t NPCs;
    NPCs.insert(factory(ElfType, "Elf1", 15, 15, "test_fight.txt")); //* alive
    NPCs.insert(factory(ElfType, "Elf2", 10, 10, "test_fight.txt")); //! killed
    NPCs.insert(factory(SquirrelType, "Squirrel1", 50, 50, "test_fight.txt")); //! killed
    NPCs.insert(factory(SquirrelType, "Squirrel2", 30, 30, "test_fight.txt")); //! killed
    NPCs.insert(factory(BanditType, "Bandit1", 40, 40, "test_fight.txt")); //* alive
    NPCs.insert(factory(BanditType, "Bandit2", 5, 5, "test_fight.txt"));  //! killed
    ASSERT_EQ(6, NPCs.size());

    set_t NPCsKilled;

    for (auto& attacker : NPCs) {
        for (auto& defender : NPCs) {
            if (attacker->is_alive())
                if (defender->is_alive())
                    if (defender->accept(attacker)) {
                        defender->must_die();
                        NPCsKilled.insert(defender);
                    }
        }
    }
    for (const auto& npc : NPCsKilled) {
        NPCs.erase(npc);
    }

    testing::internal::GetCapturedStdout();
    ASSERT_EQ(2, NPCs.size());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}