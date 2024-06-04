//
// Created by barcy on 26/05/2024.
//
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <ctime>
#include <set>

enum races  {Human,Elf,Orc,Lizard,Arachnid};
enum types {Warrior,Bandit,Traveller,Barbarian,Wizard};
enum skills{Attack,Heavy_Swing};

//Will probably need to store the set of skills available to a character
//Maybe store all available skills in combat or make a new class,so that we can call an object
//and retrieve what the skills should do?


class character {
    //This is class that will define what the player/enemy is
private:
    std::unordered_map<std::string,int> stat_sheet;
    int max_health;
    int current_health;
    races race;
    types type;
    std::set<skills> skill_list;

private:
    void add_skills() {
        if (skill_list.empty()) {
            skill_list.insert(Attack);
            std::cout << "Added Attack to the list!\n";
        }
        if (this->stat_sheet["STR"] >=5) {
            skill_list.insert(Heavy_Swing);
            std::cout << "Added Heavy_Swing to the list!\n";
        }
    }
public:
    //A character object must be sent a valid race and a valid class
    character(races race,types type){
        this->race = race;
        this->type = type;
        //Every character starts with these base stats
        stat_sheet["STR"] = 2;
        stat_sheet["DEX"] = 2;
        stat_sheet["INT"] = 2;
        stat_sheet["CON"] = 2;
        stat_sheet["DEF"] = 2;

        //Additional Stats Based on race
        switch(this->race) {
            case(Human):
                stat_sheet["DEX"]+=1;
                break;
            case(Elf):
                stat_sheet["INT"]+=1;
                break;
            case(Orc):
                stat_sheet["STR"]+=1;
                break;
            case(Lizard):
                stat_sheet["CON"]+=1;
                break;
            case(Arachnid):
                stat_sheet["DEF"]+=1;
                break;
            default:
                std::cout << "INVALID RACE";
        }
        //Additional Stats based on type
        switch (this->type) {
            case(Warrior):
                stat_sheet["DEF"]+=3;
                break;
            case(Bandit):
                stat_sheet["DEX"]+=3;
                break;
            case(Traveller):
                stat_sheet["CON"]+=3;
                break;
            case(Barbarian):
                stat_sheet["STR"]+=3;
                break;
            case(Wizard):
                stat_sheet["INT"]+=3;
                break;
        }

        //Mutation Generation
        //Number of arms generated, 1 - 4
        srand(time((NULL)));
        int num_arms = rand() % 4 +1;

        //Number of heads generated, 1 - 2
        int num_heads = rand() % 2 + 1;

        //Number of legs generated, 2 - 6
        int num_legs = rand() % 5 + 2;


        //Stat changes based on mutations
        stat_sheet["STR"]+=num_arms;
        stat_sheet["INT"]+=num_heads;
        stat_sheet["DEX"]+=num_legs;


        //Health amount
        current_health = stat_sheet["CON"]*5;

        //Adding Skills to the list based on the users stats
        this->add_skills();
    }

    std::unordered_map<std::string,int> get_stats() {
        return stat_sheet;
    }
    //Reduces health
    void damageHealth(int amount) {
        this->current_health-=amount;
    }
    //Increases health
    void healHealth(int amount) {
        int h = current_health;
        h+=amount;
        if (h>max_health) {
            this->current_health = max_health;
        }
        else {
            this->current_health+=amount;
        }
    }
    //Returns current health value
    int getHealth() {
        return this->current_health;
    }
    //This will display all of the characters stats
    void display_stats() {
        std::cout << "Strength : " << stat_sheet["STR"] << "\n";
        std::cout << "Dexterity : " << stat_sheet["DEX"] << "\n";
        std::cout << "Intelligence : " << stat_sheet["INT"] << "\n";
        std::cout << "Constitution : " << stat_sheet["CON"] << "\n";
        std::cout << "Defence : " << stat_sheet["DEF"] << "\n";
    }

    //Prints the ascii art of the character
    enum races  {Human,Elf,Orc,Lizard,Arachnid};
    void printArt(){
        switch(this->race) {
            case Human:
                break;
            case Elf:
                break;
            case Orc:
                break;
            case Lizard:
                break;
            case Arachnid:
                break;
            default:
                std::cout << "Invalid Character\n";

        }
    }
};