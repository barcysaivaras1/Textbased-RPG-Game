//
// Created by barcy on 26/05/2024.
//
#include "character.cpp";
#include <iostream>
class Combat {
public:
    //This should handle player choice and display all of their skills
    // **CURRENTLY ONLY DAMAGE**
    void player_turn(character &attacker, character &defender) {
        int damage = attacker.get_stats()["STR"];
        std::cout << "Damage Dealt : " << damage << "\n";
        defender.damageHealth(damage);
    }

};
