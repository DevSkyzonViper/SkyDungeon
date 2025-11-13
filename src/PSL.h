#ifndef PSL_H
#define PSL_H

#include "PSL.h"
#include "TRL.h"
#include "SGL.h"
#include "IL.h"



//Global Variable deklarations
//to know, where we currently are
extern bool mapActive; //Show if we are on a menu or map
extern Window window; //The global window
extern Map *currentMap; //Shows the current map we are
extern Interactions *currentScene; //Shows the current menu-scene we are
extern Coordinates *currentMenuItem; //Show the specific menu-item we are
extern Coordinates playerMapPosition; //Show the specific menu-item we are


//A list of Menu Scenes
extern Interactions startScene;
extern Interactions newGameScene;
extern Interactions debugScene;
extern Interactions settingsScene;
extern Interactions inventoryScene;
extern Interactions shopScene;
extern Interactions popUpMenu;


//A list of the Map Scenes
extern Map defaultMapScene;
extern Map nextMapScene;
extern Map endMapScene;
extern Map garryHouseMapScene;




//----------------------------------------------------------------------------------------//
//                   General function, that always needs to be used FIRST                 //
//----------------------------------------------------------------------------------------//


//Initialized all the scenes (map and menu's)
void initScenes();




//----------------------------------------------------------------------------------------//
//                       Render functions, specifically for the menus                     //
//----------------------------------------------------------------------------------------//


//The functions renders the start screen of the game
void renderStartScene(Window &window);


//The function renders the newGameScene where a new character is created
void renderNewGameScene(Window &window);


//Just for debug grr
void renderDebugScene(Window &window);


//The function renders the inventory of the player
void renderInventoryScene(Window &window);


//The function renders the shop the player can buy from
void renderShopScene(Window &window);




//----------------------------------------------------------------------------------------//
//                       Render functions, specifically for the maps                      //
//----------------------------------------------------------------------------------------//


//The function renders a default map, that can be customized
void renderDefaultMap(Window &window, Map &map);




//----------------------------------------------------------------------------------------//
//                       Extra function for add-ons to menus or maps                      //
//----------------------------------------------------------------------------------------//


//The function draws the logo to the window
void drawLogoToWindow(Window &window);


//The functions renders the infos of the knight screen (StartScene)
void insertKnightDetails(Window &window);


//The functions renders the infos of the wizard screen (StartScene)
void insertWizardDetails(Window &window);


//The functions renders the infos of the healer screen (StartScene)
void insertHealerDetails(Window &window);


//The functions renders the infos of the rouge screen (StartScene)
void insertRougeDetails(Window &window);


//The function insert the info that the game is saved
void insertSavedIntoWindow(Window &window);


//The function inserts the generic line of the debug npc
void insertGenericTalkNPC(Window &window);


//The function insert the default hotbar for map into the window
void insertHotbarToWindow(Window &window);


//The function inserts the settings menu into the window
void insertSettingsMenu(Window &window);




#endif