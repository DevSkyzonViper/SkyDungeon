#include <iostream>
#include <cctype>

#include "TRL.hpp"
#include "IPL.hpp"
#include "PSL.hpp"
#include "SGL.hpp"
#include "IL.hpp"

struct termios orig_termios;

//Terminal reset
void resetTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

//Dynamic input processing
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(resetTerminal);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}



//The function processes the general inputs of the user
void processGeneralInput(char* window, char* map, bool* mapActive, Coordinates*& playerMapPosition, const std::string &input, Coordinates*& cursorPosition, Interactions*& inct)
{
    //Filtering by menu
    if(*mapActive == false)
    {
        //Filtering for the player creation scene
        if(inct == &newGameScene)
        {
            if(cursorPosition->name == "chooseName")
            {
                //Writing into the field for player creating
                for(int i = 1; i < 13; i++)
                {
                    if(window[1794 + i] == '_')
                    {
                        std::system("clear");
                        window[1794 + i] = input[0];
                        drawWindow(window);
                        break;
                    }
                }
            }
        }
        //Filtering fot the shop scene
        else if(inct == &shopScene)
        {
            //Continues to the map
            if(input == "c")
            {
                *mapActive = true;
                inct = &defaultMapScene;
                renderDefaultMap(window, map, playerMapPosition);
            }
            //Cancels and goes to the start screen
            else if(input == "x")
            {
                renderStartScene(window);
                inct = &startScene;
                cursorPosition = &inct->interactOption[0];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
            }
        }
        //Filtering for the inventory
        else if(inct == &inventoryScene)
        {
            //Continues to the map
            if(input == "c")
            {
                *mapActive = true;
                inct = &defaultMapScene;
                renderDefaultMap(window, map, playerMapPosition);
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
                inct = &startScene;
                cursorPosition = &inct->interactOption[0];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
            }
        }
    }
    //Filtering by map
    else
    {
        //Filtering by the different map scenes
        if(inct == &defaultMapScene)
        {
            //Opens the inventory
            if(input == "i")
            {
                *mapActive = false;
                inct = &inventoryScene;
                cursorPosition = &inct->interactOption[0];
                renderInventoryScene(window);
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                drawWindow(window);
            }
            //Opens the settings box
            else if(input == "x")
            {
                *mapActive = false;
                inct = &settingsScene;
                cursorPosition = &inct->interactOption[0];
                insertSettingsMenu(window);
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                drawWindow(window);
            }
        }
    }
}

//The function processes the enter input of the user
bool processEnterInput(char* window, char* map, bool* mapActive, Coordinates*& playerMapPosition, Interactions*& inct, Coordinates*& cursorPosition)
{
    //Filtering for the menu
    if(*mapActive == false)
    {
        //Filtering options to start scene
        if(inct == &startScene)
        {
            if(cursorPosition->name == "newGame")
            {
                renderNewGameScene(window);
                inct = &newGameScene;
                cursorPosition = &inct->interactOption[0];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
            }
            else if(cursorPosition->name == "continueGame")
            {
                loadSaveGame();
                std::system("clear");

                renderDebugScene(window);
                inct = &debugScene;
                cursorPosition = &inct->interactOption[0];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
            }
            else if(cursorPosition->name == "exit")
            {
                return true;
            }
        }
        //Filtering options for the game creation scene
        else if(inct == &newGameScene)
        {
            if(cursorPosition->name == "createNewGame")
            {
                std::system("clear");
                playerCreation(window);
                saveCurrentGame();
                loadSaveGame();

                renderDebugScene(window);
                inct = &debugScene;
                cursorPosition = &inct->interactOption[0];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                drawWindow(window);
            }
            else if(cursorPosition->name == "startScene")
            {
                renderStartScene(window);
                inct = &startScene;
                cursorPosition = &inct->interactOption[0];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
            }
        }
        //Filtering for debug menu
        else if(inct == &debugScene)
        {
            if(cursorPosition->name == "openShop")
            {
                renderShopScene(window);
                inct = &shopScene;
                cursorPosition = &inct->interactOption[0];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
            }
            else if(cursorPosition->name == "openMap")
            {
                *mapActive = true;
                inct = &defaultMapScene;
                renderDefaultMap(window, map, playerMapPosition);
            }
            else if(cursorPosition->name == "startScene")
            {
                renderStartScene(window);
                inct = &startScene;
                cursorPosition = &inct->interactOption[0];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
            }
            else
            {
                std::cout << cursorPosition->name << std::endl;
            }
        }
        //Filtering for settings menu
        else if(inct == &settingsScene)
        {
            if(cursorPosition->name == "openMap")
            {
                *mapActive = true;
                inct = &defaultMapScene;
                renderDefaultMap(window, map, playerMapPosition);
            }
            else if(cursorPosition->name == "startScene")
            {
                renderStartScene(window);
                inct = &startScene;
                cursorPosition = &inct->interactOption[0];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
            }
        }
        //Filtering for inventory menu
        else if(inct == &inventoryScene)
        {
            std::cout << cursorPosition->name << std::endl;
        }
        //Filtering for shop menu
        else if(inct == &shopScene)
        {
            std::cout << cursorPosition->name << std::endl;
        }
        //Unimplemented scene gets printed out
        else
        {
            std::cout << cursorPosition->name << std::endl;
        }
    }
    //Filtering for the map
    else
    {
        //Filters for the default map scene
        if(inct == &defaultMapScene)
        {
            //Checks above the player
            if(map[playerMapPosition->x + ((playerMapPosition->y - 1) * 108)] != ' ')
            {
                processMapInteraction(window, mapActive, cursorPosition, inct, playerMapPosition->x, playerMapPosition->y - 1);
            }
            //Checks under the player
            else if(map[playerMapPosition->x + ((playerMapPosition->y + 1) * 108)] != ' ')
            {
                processMapInteraction(window, mapActive, cursorPosition, inct, playerMapPosition->x, playerMapPosition->y + 1);
            }
            //Checks left of the player
            else if(map[(playerMapPosition->x - 1) + (playerMapPosition->y * 108)] != ' ')
            {
                processMapInteraction(window, mapActive, cursorPosition, inct, playerMapPosition->x - 1, playerMapPosition->y);
            }
            //Checks right of the player
            else if(map[(playerMapPosition->x + 1) + (playerMapPosition->y * 108)] != ' ')
            {
                processMapInteraction(window, mapActive, cursorPosition, inct, playerMapPosition->x + 1, playerMapPosition->y);
            }
        }
        else
        {
            std::cout << cursorPosition->name << std::endl;
        }
    }
    return false;
}

//The function processes the back input of the user
void processBackInput(char* window, Interactions*& inct, Coordinates*& cursorPosition)
{
    //Only option, so no filtering
    if(cursorPosition->name == "chooseName")
    {
        for(int i = 12; i >= 0; i--)
        {
            if(window[1794 + i] != '_')
            {
                window[1794 + i] = '_';
                drawWindow(window);
                break;
            }
        }
    }
}



//The function processes the up key for the menu
void processUpMenu(char* window, Interactions*& inct, Coordinates*& cursorPosition)
{
    //Filtering for vertical interaction options
    if(inct->interactOptionVertical == true)
    {
        //Goes up in menu if it isnt the first thing
        for(int i = 0; i < inct->interactOptionLength; i++)
        {
            if(cursorPosition == &inct->interactOption[i] && i > 0)
            {
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, " ");
                cursorPosition = &inct->interactOption[i - 1];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
                break;
            }
        }
    }
}

//The function processes the down key for the menu
void processDownMenu(char* window, Interactions*& inct, Coordinates*& cursorPosition)
{
    //Filtering for vertical interaction options
    if(inct->interactOptionVertical == true)
    {
        //Goes down in menu if it isnt the last thing
        for(int i = 0; i < inct->interactOptionLength; i++)
        {
            if(cursorPosition == &inct->interactOption[i] && i < inct->interactOptionLength - 1)
            {
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, " ");
                cursorPosition = &inct->interactOption[i + 1];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
                break;
            }
        }
    }
}

//The function processes the left key for the menu
void processLeftMenu(char* window, Interactions*& inct, Coordinates*& cursorPosition)
{
    //Filtering for horizontal interaction options
    if(inct->interactOptionVertical == false)
    {
        //Goes left in menu if it isnt the first thing
        for(int i = 0; i < inct->interactOptionLength; i++)
        {
            if(cursorPosition == &inct->interactOption[i] && i > 0)
            {
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, " ");
                cursorPosition = &inct->interactOption[i - 1];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
                break;
            }
        }
    }
    //Exceptions of the rule
    else
    {
        //Special options for choosing class
        if(cursorPosition->name == "chooseClass")
        {
            char cBuffer = window[2016];

            if(cBuffer > '1')
            {
                cBuffer--;
            }
            else
            {
                cBuffer = '4';
            }
            window[2016] = cBuffer;

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

            std::system("clear");
            drawWindow(window);
        }
    }
}

//The function processes the right key for the menu
void processRightMenu(char* window, Interactions*& inct, Coordinates*& cursorPosition)
{
    //Filtering for horizontal interaction options
    if(inct->interactOptionVertical == false)
    {
        //Goes right in menu if it isnt the last thing
        for(int i = 0; i < inct->interactOptionLength; i++)
        {
            if(cursorPosition == &inct->interactOption[i] && i < inct->interactOptionLength - 1)
            {
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, " ");
                cursorPosition = &inct->interactOption[i + 1];
                writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                std::system("clear");
                drawWindow(window);
                break;
            }
        }
    }
    //Exceptions of the rule
    else
    {
        //Special options for choosing class
        if(cursorPosition->name == "chooseClass")
        {
            char cBuffer = window[2016];

            if(cBuffer < '4')
            {
                cBuffer++;
            }
            else
            {
                cBuffer = '1';
            }
            window[2016] = cBuffer;

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

            std::system("clear");
            drawWindow(window);
        }
    }
}



//The function processes the arrow keys input for the map
void arrowMapInput(char* window, char* map, Coordinates*& playerMapPosition, const std::string &input)
{
    //Only options is the map, so no filtering
    std::system("clear");
    changePlayerPositionInMap(map, playerMapPosition, input, defaultMapScene);
    drawMapIntoWindow(window, map);
    drawWindow(window);
}

//The function processes the map interaction
void processMapInteraction(char* window, bool* mapActive, Coordinates*& cursorPosition, Interactions*& inct, int x, int y)
{

    if(inct == &defaultMapScene)
    {
        for(int i = 0; i < inct->interactOptionLength; i++)
        {
            if(inct->interactOption[i].x == x)
            {
                if(inct->interactOption[i].y == y)
                {
                    if(inct->interactOption[i].func == "openShop")
                    {
                        *mapActive = false;
                        renderShopScene(window);
                        inct = &shopScene;
                        cursorPosition = &inct->interactOption[0];
                        writeIntoWindow(window, cursorPosition->x, cursorPosition->y, "*");
                        std::system("clear");
                        drawWindow(window);
                    }
                    else if(inct->interactOption[i].func == "savePoint")
                    {
                        saveCurrentGame();
                        insertSavedIntoWindow(window);
                    }
                    else if(inct->interactOption[i].func == "genericNPC")
                    {
                        insertGenericTalkNPC(window);
                    }
                    break;
                }
            }
        }
    }
}