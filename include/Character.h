#pragma once
#include <string>
#include <vector>

class Character {
    protected:
        virtual std::string getCharacterName() const = 0;
        virtual std::string getLanguage() const = 0;
        virtual std::string getDialect() const = 0;
        virtual int getStuds() const = 0;
        virtual void addStuds(int amount) = 0;
    public:
        virtual ~Character() = default;
};