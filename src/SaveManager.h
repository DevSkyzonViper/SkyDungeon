#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H


//==================================================================================
// INCLUDES OF MY OWN LIBRARIES
//==================================================================================
#include "TerminalUI.h"



//==================================================================================
// STRUCT DEFINITIONS
//==================================================================================

// The inventory of a player
struct Inventory
{
    int place[9];
};

// The attributes of a player
struct Attributes {
    int maxHP;
    int HP;
    int baseDamage;
    int maxMana;
    int mana;
    int defense;
    int speed;
};

// The player itself
struct Player
{
    std::string name;
    int level;
    int exp;
    int playerClass;
    int coins;
    Attributes atr;
    Inventory inv;
};

// The complete save game
struct SaveGame
{
    int saveSlot;
    Player player;
};



//==================================================================================
// GLOBAL VARIABLES
//==================================================================================
extern SaveGame save; //Current savegame



//==================================================================================
// GENERAL FUNCTION DEFINITIONS
//==================================================================================

// This function trys to load the save game
bool loadSaveGame(); // Return value is for error handling

// This function trys to save the current save game
bool saveCurrentGame(); // Return value is for error handling

// This function trys to create a new save-game in the given slot
bool createNewSaveGame(int slotToCreate); // Return value is for error handling

// This function trys to delete the save-game for the given slot
bool deleteSaveGame(int slotToDelete); // Return value is for error handling

// Creates a new player, customizeable by the user
void playerCreation(Window &window);




#endif //SAVE_MANAGER_H