#include <iostream>
#include "../include/Jedi.h"

Jedi::Jedi(int ID, std::string characterName, std::string language, std::string dialect, std::string lightsaberColor) : ID(ID), characterName(characterName), language(language), dialect(dialect), lightsaberColor(lightsaberColor) {

}

std::string Jedi::getCharacterName() const {
    return characterName;
}

std::string Jedi::getLanguage() const{
    return language;
}

std::string Jedi::getDialect() const{
    return dialect;
}

int Jedi::getStuds() const{
    return studs;
}

void Jedi::addStuds(int amount) {
    if (amount <= 0) {
        std::cout << "Amount must be higher than 0" << std::endl;
    } else {
        studs += amount;
    }
}

std::string Jedi::getLightsaberColor() const{
    return lightsaberColor;
}