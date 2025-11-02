#ifndef IL_HPP
#define IL_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>

struct Item {
    std::string category;
    std::string name;
};

struct ItemList {
    int id;
    Item item;
};


//Items and List
extern ItemList* itemList;
extern Item woodenSword;
extern Item stoneSword;
extern Item ironSword;
extern Item steelSword;
extern Item woodenBow;

// Initialisierung
void initItemList();

#endif