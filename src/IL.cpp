#include "IL.h"



//----------------------------------------------------------------------------------------//
//                             Global Variables for the Items                             //
//----------------------------------------------------------------------------------------//


Item woodenSword;
Item stoneSword;
Item ironSword;
Item steelSword;
Item woodenBow;
ItemList* itemList;




//----------------------------------------------------------------------------------------//
//                          Function declarations for the items                           //
//----------------------------------------------------------------------------------------//


// Initialisierung der Items
void initItemList()
{
    //Settings for the wooden Sword
    woodenSword.category = "sword";
    woodenSword.name = "Wooden Sword";

    //Settings for the stone Sword
    stoneSword.category = "sword";
    stoneSword.name = "Stone Sword";

    //Settings for the iron Sword
    ironSword.category = "sword";
    ironSword.name = "Iron Sword";

    //Settings for the steel Sword
    steelSword.category = "sword";
    steelSword.name = "Steel Sword";

    //Settings for the steel Sword
    woodenBow.category = "bow";
    woodenBow.name = "Wooden Bow";
    
    itemList = new ItemList[5]
    {
        {1, woodenSword},
        {2, stoneSword},
        {3, ironSword},
        {4, steelSword},
        {5, woodenBow}
    };
}


