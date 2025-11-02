#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "sources/SGL.hpp" //SaveGameLibrary
#include "sources/TRL.hpp" //TextRenderLibrary
#include "sources/IPL.hpp" //InputProcessingLibrary
#include "sources/PSL.hpp" //PrepareSceneLibrary
#include "sources/IL.hpp"  //ItemLibrary

// Main function
int main()
{
    //Setting interaction Options for startscreen
    initScenes(); //Initialise the scenes
    Interactions* activeScene = &startScene;

    initItemList(); //Setting the Items

    //Setting current CursorPosition
    Coordinates* cursorPosition = &activeScene->interactOption[0];

    //Default Window & Map
    char* window = new char[3080];
    char* map = new char[2160];
    bool mapActive = false;

    //Setting players default position
    Coordinates* playerMapPosition = new Coordinates;
    playerMapPosition->x = 30;
    playerMapPosition->y = 10;

    enableRawMode();

    renderStartScene(window);

    while (true) 
    {
        char c = getchar();

        if (c == '\n')
        {
            if(processEnterInput(window, map, &mapActive, playerMapPosition, activeScene, cursorPosition))
            {
                delete[] window;
                return 1;
            }

        }
        else if (c == 127 || c == 8)
        {
            processBackInput(window, activeScene, cursorPosition);
        }
        else if (c == '\x1b')
        {
            char seq[2];
            seq[0] = getchar();
            seq[1] = getchar();
            if (seq[0] == '[')
            {
                switch (seq[1])
                {
                    case 'A':
                        if(mapActive == false)
                        {
                            processUpMenu(window, activeScene, cursorPosition);
                        }
                        else
                        {
                            arrowMapInput(window, map, playerMapPosition, "up");
                        }
                        break;
                    case 'B':
                        if(mapActive == false)
                        {
                            processDownMenu(window, activeScene, cursorPosition);
                        }
                        else
                        {
                            arrowMapInput(window, map, playerMapPosition, "down");
                        }
                        break;
                    case 'C':
                        if(mapActive == false)
                        {
                            processRightMenu(window, activeScene, cursorPosition);
                        }
                        else
                        {
                            arrowMapInput(window, map, playerMapPosition, "right");
                        }
                        break;
                    case 'D':
                        if(mapActive == false)
                        {
                            processLeftMenu(window, activeScene, cursorPosition);
                        }
                        else
                        {
                            arrowMapInput(window, map, playerMapPosition, "left");
                        }
                        break;
                }
            }
        }
        else if (std::isalnum(c))
        {
            // Alle Buchstaben a-Z und Zahlen 0-9
            std::string input(1, c);
            processGeneralInput(window, map, &mapActive, playerMapPosition, input, cursorPosition, activeScene);
        }
    }

    delete[] window;
    return 0;
}