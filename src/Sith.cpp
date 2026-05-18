#include <iostream>
#include "../include/Sith.h"

Sith::Sith(int ID, std::string characterName, std::string language, std::string dialect, int angerLevel) : ID(ID), characterName(characterName), language(language), dialect(dialect), angerLevel(angerLevel) {

}

std::string Sith::getCharacterName() const{
    return characterName;
}

std::string Sith::getLanguage() const{
    return language;
}

std::string Sith::getDialect() const{
    return dialect;
}

int Sith::getStuds() const{
    return studs;
}

void Sith::addStuds(int amount) {
    if (amount <= 0) {
        std::cout << "Amount must be higher than 0" << std::endl;
    } else {
        studs += amount;
    }
}

void Sith::addVirtualStuds(int amount) {
    if (amount <= 0) {
        std::cout << "Amount must be higher than 0" << std::endl;
    } else {
        virtualStuds += amount;
    }
}

int Sith::getAngerLevel() const{
    return angerLevel;
}