#include <iostream>
#include <string>
#include <cmath>
#include "logic.h"

auto main() -> int{
    std::string day {};
    int num {};
    std::cin >> day >> num;
    
    std::cout << std::boolalpha << logic(num, day);
}

