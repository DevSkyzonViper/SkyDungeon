#ifndef ITEM_LIST_H
#define ITEM_LIST_H


//==================================================================================
// INCLUDES OF GENERAL LIBRARIES
//==================================================================================
#include <string>



//==================================================================================
// STRUCT DEFINITIONS
//==================================================================================

struct Item {
    std::string category;
    std::string name;
};

struct ItemList {
    int id;
    Item item;
};



//==================================================================================
// GLOBAL VARIABLE DEFINITIONS
//==================================================================================
extern ItemList* itemList;
extern Item woodenSword;
extern Item stoneSword;
extern Item ironSword;
extern Item steelSword;
extern Item woodenBow;



//==================================================================================
// GENERAL FUNCTION DEFINITIONS
//==================================================================================

// Initialisierung
void initItemList();




#endif //ITEM_LIST_H