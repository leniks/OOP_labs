#include <iostream>
#include <string>
#include <cmath>

bool logic(int, std::string);

auto main() -> int{
    std::string day {};
    int num {};
    std::cin >> day >> num;
    
    std::cout << logic(num, day);
}

bool logic(int num, std::string day){
    if(day == "monday"){
        if(num == 12){
            return true;
        } else return false;
    } else 
    
    if(day == "tuesday"){
        if(num > 95){
            return true;
        } else return false;
    } else 
    
    if(day == "wednesday"){
        if(num == 34){
            return true;
        } else return false;
    } else 
    
    if(day == "thursday"){
        if(num == 0){
            return true;
        } else return false;
    } else 
    
    if(day == "friday"){
        if(num % 2 == 0){
            return true;
        } else return false;
    } else 
    
    if(day == "saturday"){
        if(num == 56){
            return true;
        } else return false;
    } else 
    
    if(day == "sunday"){
        if(num == 666 or num == -666){
            return true;
        } else return false;
    }
}