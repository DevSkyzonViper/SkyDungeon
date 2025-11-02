#include "SGL.hpp"
#include <iostream>
#include <fstream>

SaveGame save;

//This function trys to load the save game
void loadSaveGame() //Return value is for error handling
{
    std::string line; //The line extracted of the used file

    //Trying to open the save-file
    std::ifstream saveSlot("save/slot_1.sav");
    if(!saveSlot.is_open())
    {
        //There is no created file with that number
        std::cout << "No save-file / SaveFile corrupt" << std::endl;
        
        save.saveSlot = 0;
    }
    else
    {
        //Load the players saveGameFile data
        std::getline(saveSlot, line); //Save-slot
        save.saveSlot = std::stoi(line);
        std::getline(saveSlot, save.player.name); //Player-Name
        std::getline(saveSlot, line); //Player-Level
        save.player.level = std::stoi(line);
        std::getline(saveSlot, line); //Player-Exp
        save.player.exp = std::stoi(line);
        std::getline(saveSlot, line); //Player-Class
        save.player.playerClass = std::stoi(line);
        std::getline(saveSlot, line); //Players-Coins
        save.player.coins = std::stoi(line);

        //Load the players attribute data
        std::getline(saveSlot, line); //Players-MaxHP
        save.player.atr.maxHP = std::stoi(line);
        std::getline(saveSlot, line); //Players-HP
        save.player.atr.HP = std::stoi(line);
        std::getline(saveSlot, line); //Players-Base-Damage
        save.player.atr.baseDamage = std::stoi(line);
        std::getline(saveSlot, line); //Players-Max-Mana
        save.player.atr.maxMana = std::stoi(line);
        std::getline(saveSlot, line); //Players-Mana
        save.player.atr.mana = std::stoi(line);
        std::getline(saveSlot, line); //Players-Defense
        save.player.atr.defense = std::stoi(line);
        std::getline(saveSlot, line); //Players-Speed
        save.player.atr.speed = std::stoi(line);

        //Load the inventory saveGameFile data
        std::getline(saveSlot, line); //Inv-Place-1
        save.player.inv.place[0] = std::stoi(line);
        std::getline(saveSlot, line); //Inv-Place-2
        save.player.inv.place[1] = std::stoi(line);
        std::getline(saveSlot, line); //Inv-Place-3
        save.player.inv.place[2] = std::stoi(line);
        std::getline(saveSlot, line); //Inv-Place-4
        save.player.inv.place[3] = std::stoi(line);
        std::getline(saveSlot, line); //Inv-Place-5
        save.player.inv.place[4] = std::stoi(line);
        std::getline(saveSlot, line); //Inv-Place-6
        save.player.inv.place[5] = std::stoi(line);
        std::getline(saveSlot, line); //Inv-Place-7
        save.player.inv.place[6] = std::stoi(line);
        std::getline(saveSlot, line); //Inv-Place-8
        save.player.inv.place[7] = std::stoi(line);
        std::getline(saveSlot, line); //Inv-Place-9
        save.player.inv.place[8] = std::stoi(line);
    }

    //Close the save-file
    saveSlot.close();
}

//This function trys to save the current save game
bool saveCurrentGame() //Return value is for error handling
{
    std::ofstream saveGameFile("save/slot_1.sav");
    if(!saveGameFile.is_open())
    {
        std::cout << "No save-file for slot 1." << std::endl;
        return false;
    }

    //Writing file headert
    saveGameFile << save.saveSlot << "\n";

    //Saving player-data
    saveGameFile << save.player.name << "\n";
    saveGameFile << save.player.level << "\n";
    saveGameFile << save.player.exp << "\n";
    saveGameFile << save.player.playerClass << "\n";
    saveGameFile << save.player.coins << "\n";

    //Saving player-attribute-data
    saveGameFile << save.player.atr.maxHP << "\n";
    saveGameFile << save.player.atr.HP << "\n";
    saveGameFile << save.player.atr.baseDamage << "\n";
    saveGameFile << save.player.atr.maxMana << "\n";
    saveGameFile << save.player.atr.mana << "\n";
    saveGameFile << save.player.atr.defense << "\n";
    saveGameFile << save.player.atr.speed << "\n";

    //Saving inventory-data
    saveGameFile << save.player.inv.place[0] << "\n";
    saveGameFile << save.player.inv.place[1] << "\n";
    saveGameFile << save.player.inv.place[2] << "\n";
    saveGameFile << save.player.inv.place[3] << "\n";
    saveGameFile << save.player.inv.place[4] << "\n";
    saveGameFile << save.player.inv.place[5] << "\n";
    saveGameFile << save.player.inv.place[6] << "\n";
    saveGameFile << save.player.inv.place[7] << "\n";
    saveGameFile << save.player.inv.place[8] << "\n";

    return true;
}

//This function trys to create a new save-game in the given slot
bool createNewSaveGame(int slotToCreate) //Return value is for error handling
{
    std::ofstream saveGameFile("save/slot_"+ std::to_string(slotToCreate) +".sav");
    if(!saveGameFile.is_open())
    {
        std::cout << "Error creating save-file " << slotToCreate << "." << std::endl;
        return false;
    }

    //Writing file header
    saveGameFile << 1 << "\n";

    //Saving player-data
    saveGameFile << "none" << "\n";
    saveGameFile << 1 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";

    //Saving player-attribute-data
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";

    //Saving inventory-data
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";

    return true;
}

//This function trys to delete the save-game for the given slot
bool deleteSaveGame(int slotToDelete) //Return value is for error handling
{
    std::ofstream saveGameFile("save/slot_"+ std::to_string(slotToDelete) +".sav");
    if(!saveGameFile.is_open())
    {
        std::cout << "Error creating save-file " << slotToDelete << "." << std::endl;
        return false;
    }

    //Writing file header
    saveGameFile << 0 << "\n";

    //Saving player-data
    saveGameFile << "none" << "\n";
    saveGameFile << 1 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";

    //Saving player-attribute-data
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";

    //Saving inventory-data
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";
    saveGameFile << 0 << "\n";

    return true;
}

//Creates a new player, customizeable by the user
void playerCreation(char* window)
{
    char buffer[13];
    char cls = window[2016];
    std::cout << cls << std::endl;

    int index = 0;
    for(int i = 1; i < 13 && index < 12; i++)
    {
        if(window[1794 + i] != '_')
        {
            buffer[index++] = window[1794 + i];
        }
        else
        {
            break;
        }
    }

    buffer[index] = '\0';

    //Putting the choosen name into the loaded save
    save.player.name = std::string(buffer);

    //Setting the basics of the player
    save.player.level = 1;
    save.player.exp = 0;
    save.player.coins = 0;

    //Emptying the players inventory
    save.player.inv.place[0] = 0;
    save.player.inv.place[0] = 0;
    save.player.inv.place[0] = 0;
    save.player.inv.place[0] = 0;
    save.player.inv.place[0] = 0;
    save.player.inv.place[0] = 0;
    save.player.inv.place[0] = 0;
    save.player.inv.place[0] = 0;
    save.player.inv.place[0] = 0;

    
    if(cls == '1')
    {
        //Setting the class and atrributes to Knight
        save.player.playerClass = 1;
        save.player.atr.maxHP = 120;
        save.player.atr.HP = 120;
        save.player.atr.baseDamage = 5;
        save.player.atr.maxMana = 0;
        save.player.atr.mana = 0;
        save.player.atr.defense = 1;
        save.player.atr.speed = 10;
    }
    else if(cls == '2')
    {
        //Setting the class and atrributes to Wizard
        save.player.playerClass = 2;
        save.player.atr.maxHP = 100;
        save.player.atr.HP = 100;
        save.player.atr.baseDamage = 3;
        save.player.atr.maxMana = 15;
        save.player.atr.mana = 15;
        save.player.atr.defense = 0;
        save.player.atr.speed = 13;
    }
    else if(cls == '3')
    {
        //Setting the class and atrributes to Healer
        save.player.playerClass = 3;
        save.player.atr.maxHP = 120;
        save.player.atr.HP = 120;
        save.player.atr.baseDamage = 2;
        save.player.atr.maxMana = 10;
        save.player.atr.mana = 10;
        save.player.atr.defense = 0;
        save.player.atr.speed = 12;
    }
    else if(cls == '4')
    {
        //Setting the class and atrributes to Rogue
        save.player.playerClass = 4;
        save.player.atr.maxHP = 105;
        save.player.atr.HP = 105;
        save.player.atr.baseDamage = 4;
        save.player.atr.maxMana = 0;
        save.player.atr.mana = 0;
        save.player.atr.defense = 1;
        save.player.atr.speed = 16;
    }
}