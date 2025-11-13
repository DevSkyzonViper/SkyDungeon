#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "src/SGL.h" //SaveGameLibrary
#include "src/TRL.h" //TextRenderLibrary
#include "src/IPL.h" //InputProcessingLibrary
#include "src/PSL.h" //PrepareSceneLibrary
#include "src/IL.h"  //ItemLibrary

void initGame();

// Main function
int main()
{
    initGame();
    
    while(true)
    {
        if(processGameInput())
        {
            return 0;
        }
    }


    return 0;
}

void initGame()
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
