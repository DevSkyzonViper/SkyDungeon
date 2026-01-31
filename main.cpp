//==================================================================================
// INCLUDES OF GENERAL LIBRARIES
//==================================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>



//==================================================================================
// INCLUDES OF MY OWN LIBRARIES
//==================================================================================
#include "src/SaveManager.h"        // SaveGameLibrary
#include "src/TerminalUI.h"         // TextRenderLibrary
#include "src/TerminalInput.h"      // InputProcessingLibrary
#include "src/GameScenesLib.h"      // PrepareSceneLibrary
#include "src/ItemListLib.h"        // ItemLibrary



//==================================================================================
// GENERAL FUNCTION DEFINITIONS
//==================================================================================

// The function initializes the game scenes, item list and load
// the save game, enabling raw mode and rendering the start scene
void initializeGame()
{
    //Setting interaction Options for startscreen
    initScenes(); //Initialise the scenes
    initItemList(); //Initialise Item list
    loadSaveGame(); //Loads the current save game

    currentMap = &defaultMapScene;

    //Terminal fast mode
    enableRawMode();
    
    //Start rendering
    renderStartScene(window);
}



//==================================================================================
// MAIN FUNCTION
//==================================================================================

int main()
{
    // InitializeGame
    initializeGame();
    
    while(true)
    {
        // Check input buffer
        if(processGameInput())
        {
            return 0;
        }
    }
    
    return 0;
}

