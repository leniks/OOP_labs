#pragma once

#include <cstring>
#include <iostream>
#include <algorithm>

class Four
{
public:
    Four(); 
    size_t getSize() const;
    unsigned char* getNumber() const;

    Four(const size_t & n, unsigned char t = 0);
    Four(const std::initializer_list< unsigned char> &t);
    Four(const std::string t);
    Four(const Four& other);
    Four(Four&& other) noexcept;
    
    std::ostream &print(std::ostream &os);

    Four operator=(const Four &other);                 
    Four operator+(const Four &other) const;          
    Four operator-(const Four &other) const;           
    bool operator==(const Four &other) const;           
    bool operator!=(const Four &other) const;           
    bool operator<(const Four &other) const;            
    bool operator<=(const Four &other) const;            
    bool operator>(const Four other) const;              
    bool operator>=(const Four other) const;             

    ~Four() noexcept; 
private:
    size_t size;
    unsigned char *number;
};

bool isFour(const char &c);
