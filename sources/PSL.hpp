#ifndef PSL_HPP
#define PSL_HPP

#include "IPL.hpp"
#include "TRL.hpp"
#include "IL.hpp"

// Szenen-Variablen
extern Interactions startScene;
extern Interactions newGameScene;
extern Interactions debugScene;
extern Interactions defaultMapScene;
extern Interactions settingsScene;
extern Interactions inventoryScene;
extern Interactions shopScene;

// Initialisierung
void initScenes();


// Render-Funktionen für jede Szene
void renderStartScene(char* window);
void renderNewGameScene(char* window);
void renderDebugScene(char* window);
void renderDefaultMap(char* window, char* map, Coordinates*& playerMapPosition);
void renderInventoryScene(char* window);
void renderShopScene(char* window);


//The functions renders the infos of the knight screen (StartScene)
void insertKnightDetails(char* window);

//The functions renders the infos of the wizard screen (StartScene)
void insertWizardDetails(char* window);

//The functions renders the infos of the healer screen (StartScene)
void insertHealerDetails(char* window);

//The functions renders the infos of the rouge screen (StartScene)
void insertRougeDetails(char* window);

//The function insert the info that the game is saved
void insertSavedIntoWindow(char* window);

//The function inserts the generic line of the debug npc
void insertGenericTalkNPC(char* window);

//The function insert the default hotbar for map into the window
void insertHotbarToWindow(char* window);

//The function inserts the settings menu into the window
void insertSettingsMenu(char* window);

//The function insert the player from given coordinates into the screen
void insertPlayerIntoMap(char* map, Coordinates*& playerMapPosition);



//The function processes the move input of the player in the map
void changePlayerPositionInMap(char* map, Coordinates*& playerMapPosition, const std::string &input, Interactions defaultMapScene);

//The function adds custom interactions into the map
void insertInteractionsIntoMap(char* map, Interactions defaultMapScene);

#endif