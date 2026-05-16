#include <iostream>
#include "../include/Sith.h"

int main() {
    Sith* darth_vader = new Sith(1, "Darth Vader", "German", "Austrian German");
    std::cout << darth_vader->getCharacterName() << std::endl;
    return 0;
}