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



        //Conditions 0 - No Mana so we need to loop
        //Conditions 1 - Extra turn
        bool conditions[2];
        do {
            std::cin.clear();
            fflush(stdin);

            int player_skill_choice;
            std::cin >> player_skill_choice;

            //Skill is used in this function call
            use_skill(array_of_skills[player_skill_choice-1],attacker,defender,conditions);
        }while(conditions[0]);

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
     void use_skill(skills skill, character &attacker,character &defender,bool conditions[]) {
        bool successful_turn = true;
        double damage;


        //Later refactor so that i resuse code more
        //There is a lot of duplicated code
        switch (skill) {
            case Attack:
                damage = 5;
                defender.damageHealth(damage);
                break;
            case Heavy_Swing:
                damage = round(attacker.get_stats()["STR"] * 1.5);
                std::cout << damage << "\n";
                defender.damageHealth((int)damage);
                break;
            case Rock_Shoot:
                damage = 7;
                successful_turn = attacker.useMana(1);
                if(successful_turn) {
                    conditions[0] = false;
                    defender.damageHealth(damage);
                }
                break;
            case Fireball:
                damage = 12;
                successful_turn = attacker.useMana(2);
                if(successful_turn) {
                    conditions[0] = false;
                    defender.damageHealth(damage);
                }
                break;
            case Quick_Jabs:
                damage = round(attacker.get_stats()["DEX"] * 1.25);
                std::cout << damage << "\n";
                defender.damageHealth((int)damage);
                break;
            }

        //No Mana
        if(!successful_turn) {
            conditions[0] = true;
        }
        else {
            conditions[0] = false;
        }
    }
};
