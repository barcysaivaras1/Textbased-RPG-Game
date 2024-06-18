//
// Created by barcy on 26/05/2024.
//
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <ctime>
#include <set>
#include <windows.h>

enum races  {Human,Elf,Orc,Lizard,Arachnid};
enum types {Warrior,Bandit,Traveller,Barbarian,Wizard};
enum skills{Attack,Heavy_Swing,Rock_Shoot,Fireball};

//Will probably need to store the set of skills available to a character
//Maybe store all available skills in combat or make a new class,so that we can call an object
//and retrieve what the skills should do?


class character {
    //This is class that will define what the player/enemy is
private:
    std::unordered_map<std::string,int> stat_sheet;
    int max_health;
    int current_health;
    //These two values will come in a further update
    //int experience;
    int max_mana;
    int current_mana;
    races race;
    types type;
    std::set<std::tuple <skills,std::string>> skill_list;


private:
    void add_skills() {
        //This will be called at the beginning of a characters creation
        //and when a character levels up
        //This defines how a skill is obtained

        //Every character has this
        if (skill_list.empty()) {
            skill_list.insert(std::make_tuple(Attack,"Attack"));
        }
        //Strength must be atleast 5 to have this
        if (this->stat_sheet["STR"] >=5) {
            skill_list.insert(std::make_tuple(Heavy_Swing,"Heavy Swing"));
        }
        //Intelligence must be atleast 2 to have this spell
        if(this->stat_sheet["INT"] >=2) {
            skill_list.insert(std::make_tuple(Rock_Shoot,"Rock Shoot"));
        }
        //Intelligence must be atleast 6 to have this spell
        if(this->stat_sheet["INT"] >=6) {
            skill_list.insert(std::make_tuple(Fireball,"Fireball"));
        }
    }
public:
    //A character object must be sent a valid race and a valid class
    character(races race,types type,bool player){
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
                stat_sheet["DEX"]+=3;
                break;
            case(Elf):
                stat_sheet["INT"]+=3;
                break;
            case(Orc):
                stat_sheet["STR"]+=3;
                break;
            case(Lizard):
                stat_sheet["CON"]+=3;
                break;
            case(Arachnid):
                stat_sheet["DEF"]+=3;
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


        //Health for player
        if (player) {
            current_health = (stat_sheet["CON"]*5)+25;
            max_health = current_health;
        }
        //Health for enemies
        //Rather than multiplying by a constant amount
        //I can later base their health off of how many fights the user had gone through
        else{
            current_health = (stat_sheet["CON"]*3);
        }

        //Mana amount
        current_mana = stat_sheet["INT"]*2;
        max_mana = current_mana;

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
    bool useMana(int amount) {
        bool canUseSpell = false;
        if (current_mana >= amount) {
            current_mana-=amount;
            canUseSpell = true;
        }
        else {
            std::cout << "**************NOT ENOUGH MANA**************\n";
        }
        return canUseSpell;

    }

    //Returns current health value
    int getHealth() {
        return this->current_health;
    }
    //Returns current Mana value
    int getMana() {
        return this->current_mana;
    }

    std::set<std::tuple <skills,std::string>> get_skills() {
        return skill_list;
    }
    //This will display all of the characters stats
    void display_stats() {
        std::cout << "-----------Your Stats-----------\n";
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
                std::cout << "                 ,#####,\n";
                std::cout << "                 #_   _#\n";
                std::cout << "                 |a` `a|\n";
                std::cout << "                 |  u  |\n";
                std::cout << "                 \\  =  /\n";
                std::cout << "                 |\\___/|\n";
                std::cout << "        ___ ____/:     :\\____ ___\n";
                std::cout << "      .'   `.-===-\\   /-===-.`   '.\n";
                std::cout << "     /      .-\"\"\"\"\"-.-\"\"\"\"\"-.      \\\n";
                std::cout << "    /'             =:=             '\\\n";
                std::cout << "  .'  ' .:    o   -=:=-   o    :. '  `.\n";
                std::cout << "  (.'   /'. '-.....-'-.....-' .\\   '.)\n";
                std::cout << "  /' ._/   \".     --:--     .\"   \\_. '\\\n";
                std::cout << " |  .'|      \".  ---:---  .\"      |'.  |\n";
                std::cout << " |  : |       |  ---:---  |       | :  |\n";
                std::cout << "  \\ : |       |_____._____|       | : /\n";
                std::cout << "  /   (       |----|------|       )   \\\n";
                std::cout << " /... .|      |    |      |      |. ...\\\n";
                std::cout << "|::::/''     /     |       \\     ''\\::::|\n";
                std::cout << "'\"\"\"\"       /'    .L_      `\\       \"\"\"\"'\n";
                break;
            case Elf:
                std::cout << "            ..-.--..\n";
                std::cout << "           ,','.-`.-.`.\n";
                std::cout << "          :.',;'     `.\.\n";
                std::cout << "          ||//----,-.--\\|\n";
                std::cout << "        \\`:|/-----`-'--||'/\n";
                std::cout << "         \\\\|:    |:'\n";
                std::cout << "          `||      \\   |!\n";
                std::cout << "          |!|          ;|\n";
                std::cout << "          !||:.   --  /|!\n";
                std::cout << "         /||!||:.___.|!||\\\n";
                std::cout << "        /|!|||!|    |!||!\\\\:.\n";
                std::cout << "     ,'//!||!||!`._.||!||,:\\\\\\\n";
                std::cout << "    : :: |!|||!| SSt|!||! |!::\n";
                std::cout << "    | |! !||!|||`---!|!|| ||!|\n";
                std::cout << "    | || |!|||!|    |!||! |!||\n";
                break;
            case Orc:
                std::cout << "                       _,.---''```````'-.\n";
                std::cout << "                    ,-'`                  `-._\n";
                std::cout << "                 ,-`                   __,-'`,\\\n";
                std::cout << "                /             _       /,'  ,|/ \\\n";
                std::cout << "              ,'         ,''-<_`'.    |  ,' |   \\\n";
                std::cout << "             /          / _    `  `.  | / \\ |\\  |\n";
                std::cout << "             |         (  |`'-,---, `'  \\_|/ |  |\n";
                std::cout << "             |         |`  \\  \\|  /  __,    _ \\ |\n";
                std::cout << "             |         |    `._\\,'  '    ,-`_\\ \\|\n";
                std::cout << "             |         |        ,----      /|   )\n";
                std::cout << "             \\         \\       / --.      {/   /|\n";
                std::cout << "              \\         | |       `.\         / |\n";
                std::cout << "               \\        / `-.                 | /\n";
                std::cout << "                `.     |     `-        _,--V`)\\/        _,-\n";
                std::cout << "                  `,   |           /``V_,.--`  \\.  _,-'`\n";
                std::cout << "                   /`--'`._        `-'`         )`'\n";
                std::cout << "                  /        `-.            _,.-'`\n";
                std::cout << "                              `-.____,.-'`\n";
                break;
            case Lizard:
                std::cout << "          _   _\n";
                std::cout << "          (.)-(.)\n";
                std::cout << "          /  \"  \\\n";
                std::cout << "         /\\'---'/\\\n";
                std::cout << "       /|  `\"'`  |\\\n";
                std::cout << "      // \\       / \\\\\n";
                std::cout << "     /|\\ /  /^\\  \\ /|\\\n";
                std::cout << "        / .'   '. \\\n";
                std::cout << "        \\ (     ) /\n";
                std::cout << "       /  |     |  \\\n";
                std::cout << " jgs  /   |     |   \\\n";
                std::cout << "     '-'-'       '-'-'\n";
                break;
            case Arachnid:
                std::cout << "           ____                      ,\n";
                std::cout << "          /---.'.__             ____//\n";
                std::cout << "               '--.\\           /.---'\n";
                std::cout << "          _______  \\\\         //\n";
                std::cout << "        /.------.\\  \\|      .'/  ______\n";
                std::cout << "       //  ___  \\ \\ ||/|\\  //  _/_----.\\__\n";
                std::cout << "      |/  /.-.\\  \\ \\:|< >|// _/.'..\\   '--'\n";
                std::cout << "         //   \\'..| \\'..|.'/ /_/ /  \\\\\n";
                std::cout << "        //     \\ \\_\\/\" ' ~\\-'.-'    \\\\\n";
                std::cout << "       //       '-._| :H: |'-.__     \\\\\n";
                std::cout << "      //           (/'===\\')'-._\\     ||\n";
                std::cout << "      ||                        \\\\    \\|\n";
                std::cout << "      ||                         \\\\    '\n";
                std::cout << "snd   |/                          \\\\\n";
                std::cout << "                                   ||\n";
                std::cout << "                                   ||\n";
                std::cout << "                                   \\\\\n";
                std::cout << "                                    '\n";
                break;
            default:
                std::cout << "Invalid Character\n";

        }
    }
};