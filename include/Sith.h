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
        int virtualStuds;
        int studs; 
        int angerLevel; 

    public:
        Sith(int ID, std::string characterName, std::string language, std::string dialect, int angerLevel = 0);

        std::string getCharacterName() const override;
        std::string getLanguage() const override;
        std::string getDialect() const override;
        int getStuds() const override;
        void addStuds(int amount) override;
        void addVirtualStuds(int amount) override;
        int getAngerLevel() const;
};