#pragma once

#include <string>
#include <unordered_map>
#include <fstream>

#include "creature.h"

class CreatureHandler{
    public:
        std::unordered_map<ID, Creature> creatures;

        std::unordered_map<creatureCode, CreatureRule> crtRules;

        void loadRules(std::string path);
};