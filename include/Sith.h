#pragma once
#include "Character.h"
#include <string>
#include <vector>

class Sith : public Character {
    private:
        int ID;
        std::string characterName;
        std::string language;
        std::string dialect;
    public:
        Sith(int ID, std::string characterName, std::string language, std::string dialect);

        std::string getCharacterName() override;
};