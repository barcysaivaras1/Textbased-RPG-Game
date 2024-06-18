//
// Created by barcy on 26/05/2024.
//
#include "character.cpp"
#include <iostream>
#include <tuple>
#include <cmath>

class Combat {
public:
    //This should handle player choice and display all of their skills
    //This will be turn based
    // **CURRENTLY ONLY DAMAGE**
    void player_turn(character &attacker, character &defender) {

        std::cout << "**********List of Available Skills**********\n";
        int counter = 0;

        //This array will store the skills that are in the skill list so that we can
        //access the skills using an index
        skills array_of_skills[attacker.get_skills().size()];
        for(std::tuple<skills,std::string> skill : attacker.get_skills()) {
            array_of_skills[counter] = std::get<0>(skill);
            counter+=1;
            std::cout << counter << ". " << std::get<1>(skill) << "\n";
        }
        std::cout << "Please choose a skill\n";

        bool successful_turn = true;
        do {
            std::cin.clear();
            fflush(stdin);

            int player_skill_choice;
            std::cin >> player_skill_choice;

            //Skill is used in this function call
            successful_turn = use_skill(array_of_skills[player_skill_choice-1],attacker,defender);
        }while(!successful_turn);

    }

    //This is for the enemy turn
    //This should just be randomly generated, maybe implement a simple AI to make better decisions
    void enemy_turn(character &attacker,character &defender) {
        int damage = 2;
        std::cout << "Damage Dealt : " << damage << "\n";
        defender.damageHealth(damage);
    }



    //Skills
    //What a skill does is defined here
    bool use_skill(skills skill, character &attacker,character &defender) {
        bool successful_turn = true;
        double damage;
        switch (skill) {
            case Attack:
                damage = 5;
                defender.damageHealth(damage);
                break;
            case Heavy_Swing:
                damage = round(attacker.get_stats()["STR"] * 1.25);
                std::cout << damage << "\n";
                defender.damageHealth((int)damage);
                break;
            case Rock_Shoot:
                damage = 7;
                successful_turn = attacker.useMana(1);
                if(successful_turn) {
                    defender.damageHealth(damage);
                }
                break;
            case Fireball:
                damage = 12;
                successful_turn = attacker.useMana(2);
                if(successful_turn) {
                    defender.damageHealth(damage);
                }
                break;
        }
        return successful_turn;
    }
};
