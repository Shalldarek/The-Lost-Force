#include <iostream>
#include "../include/Sith.h"

Sith::Sith(int ID, std::string characterName, std::string language, std::string dialect) : ID(ID), characterName(characterName), language(language), dialect(dialect) {

}

std::string Sith::getCharacterName() {
    return characterName;
}