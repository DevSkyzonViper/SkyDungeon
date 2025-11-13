#include <iostream>
#include <cctype>
#include <string>
#include <termios.h>
#include <unistd.h>

#include "IPL.h"
#include "TRL.h"
#include "SGL.h"


//Some Terminal shit (ChatGPT)
struct termios orig_termios;



//Terminal reset (ChatGPT)
void resetTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

//Dynamic input processing (ChatGPT)
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(resetTerminal);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}




//----------------------------------------------------------------------------------------//
//                            Input that is for the menu and map                          //
//----------------------------------------------------------------------------------------//


//The function processes the enter input of the user
//for selecting something or opening it
bool processEnterInput()
{
    //Interacting of the menu
    if(mapActive == false)
    {
        //Menu Scene: Start-Scene
        if(currentScene == &startScene)
        {
            //Menu Item: Create a new Game
            if(currentMenuItem->name == "newGame")
            {
                renderNewGameScene(window);
                currentScene = &newGameScene;
                currentMenuItem = &newGameScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }
            //Menu Item: Continue an already created game
            else if(currentMenuItem->name == "continueGame")
            {
                //Savegame found
                if(loadSaveGame() == false)
                {
                    renderDebugScene(window);
                    currentScene = &debugScene;
                    currentMenuItem = &debugScene.interactOption[0];
                    window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                    window.render();
                }

                //No savegame found
                else
                {
                    renderNewGameScene(window);
                    currentScene = &newGameScene;
                    currentMenuItem = &newGameScene.interactOption[0];
                    window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                    window.render();
                }
            }
            //Menu Item: Exit the program
            else if(currentMenuItem->name == "exit")
            {
                return true;
            }
        }

        //Menu Scene: NewGame-Scene
        else if(currentScene == &newGameScene)
        {
            //Menu Item: Creates the new game and save and goes to the debugScene
            if(currentMenuItem->name == "createNewGame")
            {
                playerCreation(window);
                saveCurrentGame();
                loadSaveGame();
                renderDebugScene(window);
                currentScene = &debugScene;
                currentMenuItem = &debugScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }
            //Menu Item: Return to start menu
            else if(currentMenuItem->name == "startScene")
            {
                renderStartScene(window);
                currentScene = &startScene;
                currentMenuItem = &startScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }
        }

        //Menu Scene: Debug-Scene
        else if(currentScene == &debugScene)
        {
            //Menu Item: Opens the shop
            if(currentMenuItem->name == "openShop")
            {
                loadSaveGame();
                renderShopScene(window);
                currentScene = &shopScene;
                currentMenuItem = &shopScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }
            //Menu Item: Opens the map
            else if(currentMenuItem->name == "openMap")
            {
                mapActive = true;
                renderDefaultMap(window, defaultMapScene);
                currentScene = nullptr;
                currentMenuItem = nullptr;
                currentMap = &defaultMapScene;
                window.render();
            }
            //Menu Item: Return to start menu
            else if(currentMenuItem->name == "startScene")
            {
                renderStartScene(window);
                currentScene = &startScene;
                currentMenuItem = &startScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }
        }

        //Menu Scene: Settings-Scene
        else if(currentScene == &settingsScene)
        {
            //Menu Item: Opens the map
            if(currentMenuItem->name == "openMap")
            {
                mapActive = true;
                renderDefaultMap(window, *currentMap);
                currentScene = nullptr;
                currentMenuItem = nullptr;
                window.render();
            }
            //Menu Item: Return to start menu
            else if(currentMenuItem->name == "startScene")
            {
                renderStartScene(window);
                currentScene = &startScene;
                currentMenuItem = &startScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }
        }
        
        //Menu Scene: Inventory-Scene (x)
        else if(currentScene == &inventoryScene)
        {
            //The Inventory doesnt have anything to do rn
        }

        //Menu Scene: Shop-Scene (x)
        else if(currentScene == &shopScene)
        {
            //The Shop doesnt have anything to do rn
        }

        //Menu Scene: Save-Manager
        else if(currentScene == &popUpMenu)
        {
            if(currentMenuItem->name == "openMap")
            {
                mapActive = true;
                renderDefaultMap(window, *currentMap);
                currentScene = nullptr;
                currentMenuItem = nullptr;
                window.render();
            }
        }

    }

    //Interactions of the map
    else if(mapActive == true)
    {
        //Checks above the player 
        if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y - 1).sOnInteract != "NULL")
        {
            //Shop-interaction
            if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y - 1).sOnInteract == "openShop")
            {
                mapActive = false;
                renderShopScene(window);
                currentScene = &shopScene;
                currentMenuItem = &shopScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }

            //SavePoint-interaction
            else if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y - 1).sOnInteract == "savePoint")
            {
                mapActive = false;
                currentScene = &popUpMenu;
                currentMenuItem = &popUpMenu.interactOption[0];
                saveCurrentGame();
                insertSavedIntoWindow(window);
                window.render();
            }
        }

        //Checks under the player 
        else if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y + 1).sOnInteract != "NULL")
        {
            //Shop-interaction
            if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y + 1).sOnInteract == "openShop")
            {
                mapActive = false;
                renderShopScene(window);
                currentScene = &shopScene;
                currentMenuItem = &shopScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }

            //SavePoint-interaction
            else if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y + 1).sOnInteract == "savePoint")
            {
                mapActive = false;
                currentScene = &popUpMenu;
                currentMenuItem = &popUpMenu.interactOption[0];
                saveCurrentGame();
                insertSavedIntoWindow(window);
                window.render();
            }
        }

        //Checks left of the player 
        else if(currentMap->at(currentMap->getPlayerPos().x - 1, currentMap->getPlayerPos().y).sOnInteract != "NULL")
        {
            //Shop-interaction
            if(currentMap->at(currentMap->getPlayerPos().x - 1, currentMap->getPlayerPos().y).sOnInteract == "openShop")
            {
                mapActive = false;
                renderShopScene(window);
                currentScene = &shopScene;
                currentMenuItem = &shopScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }

            //SavePoint-interaction
            else if(currentMap->at(currentMap->getPlayerPos().x - 1, currentMap->getPlayerPos().y).sOnInteract == "savePoint")
            {
                mapActive = false;
                currentScene = &popUpMenu;
                currentMenuItem = &popUpMenu.interactOption[0];
                saveCurrentGame();
                insertSavedIntoWindow(window);
                window.render();
            }
        }

        //Checks right of the player 
        else if(currentMap->at(currentMap->getPlayerPos().x + 1, currentMap->getPlayerPos().y).sOnInteract != "NULL")
        {
            //Shop-interaction
            if(currentMap->at(currentMap->getPlayerPos().x + 1, currentMap->getPlayerPos().y).sOnInteract == "openShop")
            {
                mapActive = false;
                renderShopScene(window);
                currentScene = &shopScene;
                currentMenuItem = &shopScene.interactOption[0];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
            }

            //SavePoint-interaction
            else if(currentMap->at(currentMap->getPlayerPos().x + 1, currentMap->getPlayerPos().y).sOnInteract == "savePoint")
            {
                mapActive = false;
                currentScene = &popUpMenu;
                currentMenuItem = &popUpMenu.interactOption[0];
                saveCurrentGame();
                insertSavedIntoWindow(window);
                window.render();
            }
        }
    }

    return false;
}


//The function processes the back input of the user
//for returning or deleting a character input
void processBackInput()
{
    //Menu-Scene: Create New Game
    if(currentScene == &newGameScene)
    {
        //Menu-Item: Player Name Input
        if(currentMenuItem->name == "chooseName")
        {
            //Deleting the last character
            for(int i = 12; i > 0; i++)
            {
                if(window.at(34 + i, 16).cChar != '_')
                {
                    window.writeIntoWindow(34 + i, 16, "_");
                    window.render();
                    break;
                }
            }
        }
    }
}





//----------------------------------------------------------------------------------------//
//                         Input that is specifically for the menu                        //
//----------------------------------------------------------------------------------------//


//Processes if there is an option over the current one
//and switches to it, if possible
void processUpInputForMenu()
{
    if(currentScene->interactOptionVertical == true)
    {
        //Checks for the currentMenuItem, and switches it
        for(int i = 1; i < currentScene->iNumberInct; i++)
        {
            if(currentMenuItem->name == currentScene->interactOption[i].name)
            {
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, " ");
                currentMenuItem = &currentScene->interactOption[i - 1];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
                break;
            }
        }
    }
}

//Processes if there is an option under the current one
//and switches to it, if possible
void processDownInputForMenu()
{
    //Filtering for vertical interaction options
    if(currentScene->interactOptionVertical == true)
    {
        //Checks for the currentMenuItem, and switches it
        for(int i = 0; i < currentScene->iNumberInct - 1; i++)
        {
            if(currentMenuItem->name == currentScene->interactOption[i].name)
            {
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, " ");
                currentMenuItem = &currentScene->interactOption[i + 1];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
                break;
            }
        }
    }
}

//Processes if there is an option left the current one
//and switches to it, if possible
void processLeftInputForMenu()
{
    if(currentScene->interactOptionVertical == false)
    {
        //Checks for the currentMenuItem, and switches it
        for(int i = 1; i < currentScene->iNumberInct; i++)
        {
            if(currentMenuItem->name == currentScene->interactOption[i].name)
            {
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, " ");
                currentMenuItem = &currentScene->interactOption[i - 1];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
                break;
            }
        }
    }

    //Exceptions of the rule
    else
    {
        //Special options for choosing class
        if(currentMenuItem->name == "chooseClass")
        {
            char cBuffer = window.at(36, 18).cChar;

            if(cBuffer > '1')
            {
                cBuffer--;
            }
            else
            {
                cBuffer = '4';
            }
            window.at(36, 18).cChar = cBuffer;

            if(cBuffer == '1')
            {
                insertKnightDetails(window);
            }
            else if(cBuffer == '2')
            {
                insertWizardDetails(window);
            }
            else if(cBuffer == '3')
            {
                insertHealerDetails(window);
            }
            else if(cBuffer == '4')
            {
                insertRougeDetails(window);
            }

            window.render();
        }
    }
}

//Processes if there is an option right the current one
//and switches to it, if possible
void processRightInputForMenu()
{
    //Filtering for vertical interaction options
    if(currentScene->interactOptionVertical == false)
    {
        //Checks for the currentMenuItem, and switches it
        for(int i = 0; i < currentScene->iNumberInct - 1; i++)
        {
            if(currentMenuItem->name == currentScene->interactOption[i].name)
            {
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, " ");
                currentMenuItem = &currentScene->interactOption[i + 1];
                window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
                window.render();
                break;
            }
        }
    }
    
    //Exceptions
    else
    {
        //Special options for choosing class
        if(currentMenuItem->name == "chooseClass")
        {
            char cBuffer = window.at(36, 18).cChar;

            if(cBuffer < '4')
            {
                cBuffer++;
            }
            else
            {
                cBuffer = '1';
            }
            window.at(36, 18).cChar = cBuffer;

            if(cBuffer == '1')
            {
                insertKnightDetails(window);
            }
            else if(cBuffer == '2')
            {
                insertWizardDetails(window);
            }
            else if(cBuffer == '3')
            {
                insertHealerDetails(window);
            }
            else if(cBuffer == '4')
            {
                insertRougeDetails(window);
            }

            window.render();
        }
    }
}


//The function processes the arrow keys input for the menu
//to choose the corresponding menu item (ChatGPT)
void processArrowKeyInputForMenu()
{
    char seq[2];
    seq[0] = getchar();
    seq[1] = getchar();
    if (seq[0] == '[')
    {
        switch (seq[1])
        {
            case 'A':
                processUpInputForMenu();
                break;
            case 'B':
                processDownInputForMenu();
                break;
            case 'C':
                processRightInputForMenu();
                break;
            case 'D':
                processLeftInputForMenu();
                break;
        }
    }
}


//The function processes the general inputs of the user
//such as numbers, characters, and special characters
//specifically for the menu
void processNormalInputForMenu(std::string input)
{
    //Menu-Scene: Create New Game
    if(currentScene == &newGameScene)
    {
        //Menu-Item: Player Name Input
        if(currentMenuItem->name == "chooseName")
        {
            //Writing into the field for player creating
            for(int i = 1; i < 13; i++)
            {
                if(window.at(34 + i, 16).cChar == '_')
                {
                    window.writeIntoWindow(34 + i, 16, input);
                    window.render();
                    break;
                }
            }
        }
    }

    //Menu-Scene: Shop Menu
    else if(currentScene == &shopScene)
    {
        //Continues to the map
        if(input == "c")
        {
            mapActive = true;
            renderDefaultMap(window, *currentMap);
        }
        //Should let the player view stats or infosy
        else if(input == "v")
        {
            std::cout << "View";
        }
        //Cancels and goes to the start screen
        else if(input == "x")
        {
            renderStartScene(window);
            currentScene = &startScene;
            currentMenuItem = &startScene.interactOption[0];
            window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
            window.render();
        }
    }

    //Menu-Scene: Inventory Menu
    else if(currentScene == &inventoryScene)
    {
        //Continues to the map
        if(input == "c")
        {
            mapActive = true;
            renderDefaultMap(window, *currentMap);
        }
        //Should let the player view stats or infos
        else if(input == "v")
        {
            std::cout << "View";
        }
        //Cancels and goes to the start screen
        else if(input == "x")
        {
            renderStartScene(window);
            currentScene = &startScene;
            currentMenuItem = &startScene.interactOption[0];
            window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
            std::system("clear");
            window.render();
        }
    }

}





//----------------------------------------------------------------------------------------//
//                          Input that is specifically for the map                        //
//----------------------------------------------------------------------------------------//


//The function checks, if the place to move the player
//is walkable, and moves the player. If the player moved
//it also checks for interactions that happen on walk
void processMoveInputForMap(std::string input)
{
    //Checks if the move was made
    if(currentMap->changePlayerPos(input) == true)
    {
        //Checks for "OnMove"-Interactions
        if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y).sOnMove != "NULL")
        {
            //Interaction: GenericNPC
            if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y).sOnMove == "genericNPC")
            {
                mapActive = false;
                currentScene = &popUpMenu;
                currentMenuItem = &popUpMenu.interactOption[0];
                window.drawMap(1, 1, *currentMap);
                insertGenericTalkNPC(window);
                window.render();
            }
            //Interaction: MapChange to: NextMap
            else if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y).sOnMove == "spawnNext")
            {
                //Change from: FirstMap
                if(currentMap == &defaultMapScene)
                {
                    currentMap = &nextMapScene;
                    currentMap->deletePlayerPos();
                    currentMap->setPlayerPos(55, 1);
                }
                //Change from: GarrysHouseMap
                else if(currentMap == &garryHouseMapScene)
                {
                    currentMap = &nextMapScene;
                    currentMap->deletePlayerPos();
                    currentMap->setPlayerPos(12, 18);
                }
                //Change from: EndMap
                else if(currentMap == &endMapScene)
                {
                    currentMap = &nextMapScene;
                    currentMap->deletePlayerPos();
                    currentMap->setPlayerPos(106, 10);
                }
                window.drawMap(1, 1, *currentMap);
                window.render();
            }
            //Interaction: MapChange: GarrysHouseMap
            else if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y).sOnMove == "spawnGarryHouse")
            {
                //Change from: NextMap
                if(currentMap == &nextMapScene)
                {
                    currentMap = &garryHouseMapScene;
                    currentMap->deletePlayerPos();
                    currentMap->setPlayerPos(55, 18);
                    window.drawMap(1, 1, *currentMap);
                    window.render();
                }
            }
            
            //Interaction: MapChange: FirstMap
            else if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y).sOnMove == "spawnBack")
            {
                //Change from: NextMap
                if(currentMap == &nextMapScene)
                {
                    currentMap = &defaultMapScene;
                    currentMap->deletePlayerPos();
                    currentMap->setPlayerPos(55, 18);
                    window.drawMap(1, 1, *currentMap);
                    window.render();
                }
            }
            //Interaction: MapChange: EndMap
            else if(currentMap->at(currentMap->getPlayerPos().x, currentMap->getPlayerPos().y).sOnMove == "spawnEnd")
            {
                //Change from: NextMap
                if(currentMap == &nextMapScene)
                {
                    currentMap = &endMapScene;
                    currentMap->deletePlayerPos();
                    currentMap->setPlayerPos(29, 10);
                    window.drawMap(1, 1, *currentMap);
                    window.render();
                }
            }
        }

        //If there was no Interaction
        else
        {
            window.drawMap(1, 1, *currentMap);
            window.render();
        }
    }
}


//The function processes the arrow keys input for the map
//to move the player in the corresponding direction (ChatGPT)
void processArrowKeyInputForMap()
{
    char seq[2];
    seq[0] = getchar();
    seq[1] = getchar();
    if (seq[0] == '[')
    {
        switch (seq[1])
        {
            case 'A':
                processMoveInputForMap("up");
                break;
            case 'B':
                processMoveInputForMap("down");
                break;
            case 'C':
                processMoveInputForMap("right");
                break;
            case 'D':
                processMoveInputForMap("left");
                break;
        }
    }
}


//The function processes the general inputs of the user
//such as numbers, characters, and special characters
//specifically for the map
void processNormalInputForMap(std::string input)
{
    //Opens the inventory
    if(input == "i")
    {
        mapActive = false;
        currentScene = &inventoryScene;
        currentMenuItem = &inventoryScene.interactOption[0];
        renderInventoryScene(window);
        window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
        window.render();
    }
    //Opens the settings box
    else if(input == "x")
    {
        mapActive = false;
        currentScene = &settingsScene;
        currentMenuItem = &settingsScene.interactOption[0];
        insertSettingsMenu(window);
        window.writeIntoWindow(currentMenuItem->x, currentMenuItem->y, "*");
        window.render();
    }
}





//----------------------------------------------------------------------------------------//
//                               General game input to process                            //
//----------------------------------------------------------------------------------------//


//The function processes the users general game input
//to select the next thing that should happen (ChatGPT)
bool processGameInput()
{
    char c = getchar();

    if (c == '\n')
    {
        if(processEnterInput())
        {
            return true;
        }
    }
    else if (c == 127 || c == 8)
    {
        processBackInput();
    }
    else if (c == '\x1b')
    {
        if(mapActive == false)
        {
            processArrowKeyInputForMenu();
        }
        else if(mapActive == true)
        {
            processArrowKeyInputForMap();
        }
    }
    else if (std::isalnum(c))
    {
        //Alle Buchstaben a-Z und Zahlen 0-9
        std::string input(1, c);

        if(mapActive == false)
        {
            processNormalInputForMenu(input);
        }
        else if(mapActive == true)
        {
            processNormalInputForMap(input);
        }
    }
    return false;
}