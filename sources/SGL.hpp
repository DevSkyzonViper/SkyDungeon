#ifndef SGL_HPP
#define SGL_HPP

#include <string>


//Struct declarations
struct Inventory {
    int place[9];
};

struct Attributes {
    int maxHP;
    int HP;
    int baseDamage;
    int maxMana;
    int mana;
    int defense;
    int speed;
};

struct Player {
    std::string name;
    int level;
    int exp;
    int playerClass;
    int coins;
    Attributes atr;
    Inventory inv;
};

struct SaveGame {
    int saveSlot;
    Player player;
};

extern SaveGame save;

//Function declarations

//This function trys to load the save game
void loadSaveGame(); //Return value is for error handling

//This function trys to save the current save game
bool saveCurrentGame(); //Return value is for error handling

//This function trys to create a new save-game in the given slot
bool createNewSaveGame(int slotToCreate); //Return value is for error handling

//This function trys to delete the save-game for the given slot
bool deleteSaveGame(int slotToDelete); //Return value is for error handling

//Creates a new player, customizeable by the user
void playerCreation(char* window);

#endif