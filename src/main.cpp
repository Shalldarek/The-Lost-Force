#include <iostream>
#include "../include/Sith.h"
#include "../include/Jedi.h"

int main() {
    Sith* darth_vader = new Sith(1, "Darth Vader", "German", "Austrian German", 99);
    Jedi* luke_skywalker = new Jedi(2, "Luke Skywalker", "English", "British English", "Green");


    std::cout << darth_vader->getCharacterName() << std::endl;
              
    std::cout << luke_skywalker->getCharacterName() << std::endl;

    delete darth_vader;
    delete luke_skywalker;

    return 0;
}