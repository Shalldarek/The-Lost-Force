#include <iostream>
#include "../include/Jedi.h"

Jedi::Jedi(int ID, std::string characterName, std::string language, std::string dialect, std::string lightsaberColor) : ID(ID), characterName(characterName), language(language), dialect(dialect), lightsaberColor(lightsaberColor) {

}

std::string Jedi::getCharacterName() const {
    return characterName;
}