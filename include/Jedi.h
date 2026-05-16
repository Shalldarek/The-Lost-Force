#pragma once
#include "Character.h"
#include <string>

class Jedi : public Character {
    private:
        int ID;
        std::string characterName;
        std::string language;
        std::string dialect;
        int studs;
        std::string lightsaberColor; 

    public:
        Jedi(int ID, std::string characterName, std::string language, std::string dialect, std::string lightsaberColor);

        std::string getCharacterName() const override;
        std::string getLanguage() const override;
        std::string getDialect() const override;
        int getStuds() const override;
        void addStuds(int amount) override;

        std::string getLightsaberColor() const;
};