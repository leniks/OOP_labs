#include <gtest/gtest.h>

#include "npc.hpp"
#include "visitor.hpp"
#include "factory.hpp"
#include "squirrel.hpp"

#include "elf.hpp"
#include "bandit.hpp"

TEST(FightTest1, Fighting) {
    Elf elf("Elf", 10, 40);
    Squirrel squirrel("Squirrel", 5, 5);
    Bandit bandit("Bandit", 0, 50);

    EXPECT_TRUE(squirrel.fight(std::make_shared<Elf>(elf)));
    EXPECT_FALSE(squirrel.fight(std::make_shared<Bandit>(bandit)));
    EXPECT_FALSE(elf.fight(std::make_shared<Squirrel>(squirrel)));
    EXPECT_TRUE(elf.fight(std::make_shared<Bandit>(bandit)));
    EXPECT_FALSE(bandit.fight(std::make_shared<Elf>(elf)));
    EXPECT_TRUE(bandit.fight(std::make_shared<Squirrel>(squirrel)));
}

TEST(FightTest2, MainFighting) {
    testing::internal::CaptureStdout();
    
    set_t array;

    array.insert(factory(ElfType, "Elf1", 0, 50, "test_fight.txt")); // alive
    array.insert(factory(SquirrelType, "Squirrel1", 5, 5, "test_fight.txt")); //! killed
    array.insert(factory(BanditType, "Bandit1", 10, 40, "test_fight.txt"));  // alive

    array.insert(factory(ElfType, "Elf2", 60, 90, "test_fight.txt")); // alive
    array.insert(factory(SquirrelType, "Squirrel2", 25, 35, "test_fight.txt")); //! killed
    array.insert(factory(BanditType, "Bandit2", 0, 2, "test_fight.txt")); // alive

    array.insert(factory(ElfType, "Elf3", 20, 100, "test_fight.txt")); // alive
    array.insert(factory(SquirrelType, "Squirrel3", 40, 50, "test_fight.txt")); //! killed
    array.insert(factory(BanditType, "Bandit3", 80, 90, "test_fight.txt")); //! killed

    auto dead_list = fight(array, 20);
    for (auto &d : dead_list)
        array.erase(d);

    testing::internal::GetCapturedStdout();

    EXPECT_EQ(array.size(), 5);
}

TEST(VisitorTest, Visitor) {
    auto elf = std::make_shared<Elf>("Elf", 0, 5);
    auto squirrel = std::make_shared<Squirrel>("Squirrel", 10, 20);
    auto bandit = std::make_shared<Bandit>("Bandit", 5, 10);

    auto npcVisitor = std::make_shared<NPCVisitor>(elf);

    EXPECT_FALSE(squirrel->accept(*npcVisitor));
    EXPECT_FALSE(elf->accept(*npcVisitor));
    EXPECT_TRUE(bandit->accept(*npcVisitor));

    npcVisitor = std::make_shared<NPCVisitor>(squirrel);

    EXPECT_TRUE(elf->accept(*npcVisitor));
    EXPECT_FALSE(squirrel->accept(*npcVisitor));
    EXPECT_FALSE(bandit->accept(*npcVisitor));

    npcVisitor = std::make_shared<NPCVisitor>(bandit);

    EXPECT_FALSE(elf->accept(*npcVisitor));
    EXPECT_TRUE(squirrel->accept(*npcVisitor));
    EXPECT_FALSE(bandit->accept(*npcVisitor));
}

TEST(ObserverTest, Observer) {
    auto bandit = std::make_shared<Bandit>("Bandit", 0, 5);
    auto squirrel = std::make_shared<Squirrel>("Squirrel", 5, 10);
    
    testing::internal::CaptureStdout();

    auto textObserver = std::make_shared<TextObserver>();
    bandit->subscribe(textObserver);
    bandit->fight(squirrel);

    std::string textOutput = testing::internal::GetCapturedStdout();
    std::string expectedOutput = "\nMurder: --------\nbandit: Bandit {0, 5} \nsquirrel: Squirrel {5, 10} \nBandit killed Squirrel\n";

    EXPECT_EQ(textOutput, expectedOutput);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}