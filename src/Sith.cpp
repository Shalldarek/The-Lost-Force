#include <iostream>
#include "../include/Sith.h"

Sith::Sith(int ID, std::string characterName, std::string language, std::string dialect, int angerLevel) : ID(ID), characterName(characterName), language(language), dialect(dialect), angerLevel(angerLevel) {

}

std::string Sith::getCharacterName() const{
    return characterName;
}