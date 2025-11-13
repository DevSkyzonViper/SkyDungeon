#ifndef IL_H
#define IL_H

#include <string>




//----------------------------------------------------------------------------------------//
//                        All struct implementations for the items                        //
//----------------------------------------------------------------------------------------//


struct Item {
    std::string category;
    std::string name;
};

struct ItemList {
    int id;
    Item item;
};




//----------------------------------------------------------------------------------------//
//                             Global Variables for the Items                             //
//----------------------------------------------------------------------------------------//


//Items and List
extern ItemList* itemList;
extern Item woodenSword;
extern Item stoneSword;
extern Item ironSword;
extern Item steelSword;
extern Item woodenBow;




//----------------------------------------------------------------------------------------//
//                          Function declarations for the items                           //
//----------------------------------------------------------------------------------------//


// Initialisierung
void initItemList();

#endif