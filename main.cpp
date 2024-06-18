#include <iostream>
#include "Combat.cpp"
#include <windows.h>
#include <ctime>


int main() {
    std::cout << "*******************Creating a character*******************\n";
    races race;
    types type;
    int user_input;

    //Player creating their character
    do {
        std::cin.clear();
        fflush(stdin);
        std::cout << "Please select a race 1-5\n";
        std::cout << "1. Human\n";
        std::cout << "2. Elf\n";
        std::cout << "3. Orc\n";
        std::cout << "4. Lizard\n";
        std::cout << "5. Arachnid\n";
        std::cin >> user_input;
    }while(user_input < 1 && user_input < 5);
    race = (races)user_input;

    do {
        std::cin.clear();
        fflush(stdin);
        std::cout << "Please select a race 1-5\n";
        std::cout << "1. Warrior\n";
        std::cout << "2. Bandit\n";
        std::cout << "3. Traveller\n";
        std::cout << "4. Barbarian\n";
        std::cout << "5. Wizard\n";
        std::cin >> user_input;
    }while(user_input < 1 && user_input < 5);



    Combat fight;

    type = (types)user_input;
    //Player Object
    character Player(race,type,true);
    int battle_counter = 1;

    //The loop will break if the players health reaches 0 or below
    while(Player.getHealth() > 0) {
        //Number of arms generated, 1 - 4
        srand(time((NULL)));
        int race = rand() % 5;
        int type = rand() % 5;

        int turn_counter = 1;
        Player.display_stats();

        //Create an Enemy
        character Enemy((races)race,(types)type,false);
        std::cout << "Battle #" << battle_counter << "\n";
        //Combat will continue until the enemy dies
        do {
            std::cout << "************* Combat Turn " << turn_counter << " *************\n";
            Enemy.printArt();
            std::cout << "\n";
            std::cout << "Your Health : " << Player.getHealth() << "\n";
            std::cout << "Your Mana : " << Player.getMana() << "\n";
            std::cout << "\n";
            std::cout << "---------------Enemy Stats---------------\n";

            std::cout << "Enemy Health : " << Enemy.getHealth() << "\n";
            turn_counter+=1;
            std::cout << "\n";
            std::cout << "****PLAYER TURN****\n";
            fight.player_turn(Player,Enemy);
            std::cout << "\n";
            std::cout << "****ENEMY TURN****\n";
            fight.enemy_turn(Enemy,Player);
            //_sleep(1000);
        }while(Enemy.getHealth() > 0 & Player.getHealth() > 0);
        battle_counter+=1;
    }

    std::cout << "You have died, your adventure end here";

    std::cout << "\n\n";
    std::cout << " _    _.--.____.--._                            @@@@@@@@@@@@@@@@@@\n";
    std::cout << "( )=.-\":;:;:;;':;:;:;\"-._		      @@@@@@@@@@@@@@@@@@@@@@@\n";
    std::cout << " \\\\\\:;:;:;:;:;;:;::;:;:;:\\                  @@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    std::cout << "  \\\\\\:;:;:;:;:;;:;:;:;:;:;:\\                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    std::cout << "   \\\\\\:;::;:;:;:;:;::;:;:;:\\              @@@@@@@@@@@@@@@/      \\@@@/   @\n";
    std::cout << "    \\\\\\:;:;:;:;:;;:;::;:;:;:\\            @@@@@@@@@@@@@@@@\\      @@  @___@\n";
    std::cout << "     \\\\\\:;::;:;:;:;:;::;:;:;:\\           @@@@@@@@@@@@@ @@@@@@@@@@  | \\@@@@@\n";
    std::cout << "      \\\\\\;;:;:_:--:_:_:--:_;:;\\          @@@@@@@@@@@@@ @@@@@@@@@\\__@_/@@@@@\n";
    std::cout << "       \\\\\\_.-\"             \"-._\\          @@@@@@@@@@@@@@@/,/,/./'/_|.\\'\\,\\\n";
    std::cout << "        \\\\                                  @@@@@@@@@@@@@|  | | | | | | | |\n";
    std::cout << "         \\\\                                               \\_|_|_|_|_|_|_|_|\n";
    std::cout << "          \\\\\n";
    std::cout << "           \\\\\n";
    std::cout << "            \\\\\n";
    std::cout << "             \\\\\n";
    return 0;
}
