#include "PSL.hpp"
#include "TRL.hpp"
#include "IPL.hpp"
#include "IL.hpp"

// Szene-Variablen
Interactions startScene;
Interactions newGameScene;
Interactions debugScene;
Interactions defaultMapScene;
Interactions settingsScene;
Interactions inventoryScene;
Interactions shopScene;

// Initialisierung der Szenen
void initScenes()
{
    //Interaction Options of the start Screen of the Game
    startScene.interactOption = new Coordinates[3]{{"newGame",41,17},{"continueGame",41,19},{"exit",41,22}};
    startScene.interactOptionLength = 3;
    startScene.interactOptionVertical = true;

    //Interaction Options of the player creation screen
    newGameScene.interactOption = new Coordinates[4]{{"chooseName",19,16},{"chooseClass",19,18},{"createNewGame", 19,21},{"startScene",19,23}};
    newGameScene.interactOptionLength = 4;
    newGameScene.interactOptionVertical = true;

    //Interaction Options of the debug screen
    debugScene.interactOption = new Coordinates[4]{{"openShop",40,16},{"openMap",40,18},{"openSkillTree", 40,20},{"startScene",40,23}};
    debugScene.interactOptionLength = 4;
    debugScene.interactOptionVertical = true;

    //Interaction Options of the default map
    defaultMapScene.interactOption = new Coordinates[8]{
        {"shop", 10, 5, "openShop"}, {"npc", 12, 5, "genericNPC"},
        {"quest", 20, 9, "makeQuest"}, {"barrier", 16, 9, "@"},
        {"barrier", 16, 8, "@"}, {"barrier", 17, 8, "#"},
        {"barrier", 17, 9, "@"}, {"statue", 25, 9, "savePoint"}
    };
    defaultMapScene.interactOptionLength = 8;

    //Interaction Options of the settings menu
    settingsScene.interactOption = new Coordinates[2]{{"openMap", 42, 13}, {"startScene", 42, 15}};
    settingsScene.interactOptionLength = 2;
    settingsScene.interactOptionVertical = true;

    //Interaction Options of the inventory scene
    inventoryScene.interactOption = new Coordinates[9]{{"inv1", 19, 6}, {"inv2", 19, 8}, {"inv3", 19, 10}, {"inv4", 19, 12}, {"inv5", 19, 14}, {"inv6", 19, 16}, {"inv7", 19, 18}, {"inv8", 19, 20}, {"inv9", 19, 22}};
    inventoryScene.interactOptionLength = 9;
    inventoryScene.interactOptionVertical = true;

    //Interaction Options of the shop scene
    shopScene.interactOption = new Coordinates[5]{{"item1", 19, 6}, {"item2", 19, 8}, {"item3", 19, 10}, {"item4", 19, 12}, {"item4", 19, 14}};
    shopScene.interactOptionLength = 5;
    shopScene.interactOptionVertical = true;
}



//The functions renders the start screen of the game
void renderStartScene(char* window)
{

    //Clears all
    clearWindow(window);
    std::system("clear");

    //Makes a border
    makeBorder(window);

    //Makes the logo 
    writeIntoWindow(window, 5, 3, R"( $$$$$$\  $$\                 $$$$$$$\                                                              )");
    writeIntoWindow(window, 5, 4, R"($$  __$$\ $$ |                $$  __$$\                                                             )");
    writeIntoWindow(window, 5, 5, R"($$ /  \__|$$ |  $$\ $$\   $$\ $$ |  $$ |$$\   $$\ $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$\  )");
    writeIntoWindow(window, 5, 6, R"(\$$$$$$\  $$ | $$  |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ )");
    writeIntoWindow(window, 5, 7, R"( \____$$\ $$$$$$  / $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |$$$$$$$$ |$$ /  $$ |$$ |  $$ |)");
    writeIntoWindow(window, 5, 8, R"($$\   $$ |$$  _$$<  $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$   ____|$$ |  $$ |$$ |  $$ |)");
    writeIntoWindow(window, 5, 9, R"(\$$$$$$  |$$ | \$$\ \$$$$$$$ |$$$$$$$  |\$$$$$$  |$$ |  $$ |\$$$$$$$ |\$$$$$$$\ \$$$$$$  |$$ |  $$ |)");
    writeIntoWindow(window, 5,10, R"( \______/ \__|  \__| \____$$ |\_______/  \______/ \__|  \__| \____$$ | \_______| \______/ \__|  \__|)");
    writeIntoWindow(window, 5,11, R"(                    $$\   $$ |                              $$\   $$ |                              )");
    writeIntoWindow(window, 5,11, R"(                    \$$$$$$  |                              \$$$$$$  |                              )");
    writeIntoWindow(window, 5,11, R"(                     \______/                                \______/                               )");
    
    //Makes a dedicated settings box
    drawBox(window, 35, 15, 40, 10);
    writeIntoWindow(window, 40, 17, "[*] Create a new game");
    writeIntoWindow(window, 40, 19, "[ ] Continue");
    writeIntoWindow(window, 40, 22, "[ ] Exit the game");

    //Renders the scene
    drawWindow(window);
}

//The function renders the newGameScene where a new character is created
void renderNewGameScene(char* window)
{
    //Clears all
    clearWindow(window);
    std::system("clear");

    //Makes the border
    makeBorder(window);

    //Makes the logo
    writeIntoWindow(window, 5, 3, R"( $$$$$$\  $$\                 $$$$$$$\                                                              )");
    writeIntoWindow(window, 5, 4, R"($$  __$$\ $$ |                $$  __$$\                                                             )");
    writeIntoWindow(window, 5, 5, R"($$ /  \__|$$ |  $$\ $$\   $$\ $$ |  $$ |$$\   $$\ $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$\  )");
    writeIntoWindow(window, 5, 6, R"(\$$$$$$\  $$ | $$  |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ )");
    writeIntoWindow(window, 5, 7, R"( \____$$\ $$$$$$  / $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |$$$$$$$$ |$$ /  $$ |$$ |  $$ |)");
    writeIntoWindow(window, 5, 8, R"($$\   $$ |$$  _$$<  $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$   ____|$$ |  $$ |$$ |  $$ |)");
    writeIntoWindow(window, 5, 9, R"(\$$$$$$  |$$ | \$$\ \$$$$$$$ |$$$$$$$  |\$$$$$$  |$$ |  $$ |\$$$$$$$ |\$$$$$$$\ \$$$$$$  |$$ |  $$ |)");
    writeIntoWindow(window, 5,10, R"( \______/ \__|  \__| \____$$ |\_______/  \______/ \__|  \__| \____$$ | \_______| \______/ \__|  \__|)");
    writeIntoWindow(window, 5,11, R"(                    $$\   $$ |                              $$\   $$ |                              )");
    writeIntoWindow(window, 5,11, R"(                    \$$$$$$  |                              \$$$$$$  |                              )");
    writeIntoWindow(window, 5,11, R"(                     \______/                                \______/                               )");
    
    //Makes the input box
    drawBox(window, 15, 14, 80, 12);
    writeIntoWindow(window, 18, 16, "[*] Playername: (____________)");
    writeIntoWindow(window, 18, 18, "[ ] PlayerClass: (1)");
    writeIntoWindow(window, 18, 21, "[ ] Continue");
    writeIntoWindow(window, 18, 23, "[ ] Cancel and to menu");

    //Makes a info box for the classes
    drawBox(window, 53, 16, 37, 8);
    insertKnightDetails(window);

    //Renders the scene
    drawWindow(window);
}

//Just for debug grr
void renderDebugScene(char* window)
{
    //Clears all
    clearWindow(window);
    std::system("clear");

    //Makes a border
    makeBorder(window);

    //Makes the logo
    writeIntoWindow(window, 5, 3, R"( $$$$$$\  $$\                 $$$$$$$\                                                              )");
    writeIntoWindow(window, 5, 4, R"($$  __$$\ $$ |                $$  __$$\                                                             )");
    writeIntoWindow(window, 5, 5, R"($$ /  \__|$$ |  $$\ $$\   $$\ $$ |  $$ |$$\   $$\ $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$\  )");
    writeIntoWindow(window, 5, 6, R"(\$$$$$$\  $$ | $$  |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ )");
    writeIntoWindow(window, 5, 7, R"( \____$$\ $$$$$$  / $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |$$$$$$$$ |$$ /  $$ |$$ |  $$ |)");
    writeIntoWindow(window, 5, 8, R"($$\   $$ |$$  _$$<  $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$   ____|$$ |  $$ |$$ |  $$ |)");
    writeIntoWindow(window, 5, 9, R"(\$$$$$$  |$$ | \$$\ \$$$$$$$ |$$$$$$$  |\$$$$$$  |$$ |  $$ |\$$$$$$$ |\$$$$$$$\ \$$$$$$  |$$ |  $$ |)");
    writeIntoWindow(window, 5,10, R"( \______/ \__|  \__| \____$$ |\_______/  \______/ \__|  \__| \____$$ | \_______| \______/ \__|  \__|)");
    writeIntoWindow(window, 5,11, R"(                    $$\   $$ |                              $$\   $$ |                              )");
    writeIntoWindow(window, 5,11, R"(                    \$$$$$$  |                              \$$$$$$  |                              )");
    writeIntoWindow(window, 5,11, R"(                     \______/                                \______/                               )");
    
    //Makes the dedicated debug settings
    drawBox(window, 36, 14, 32, 12);
    writeIntoWindow(window, 39, 16, "[*] Open the shop (Makes no sense lmao)");
    writeIntoWindow(window, 39, 18, "[ ] Open the map");
    writeIntoWindow(window, 39, 20, "[ ] Open the skill list");
    writeIntoWindow(window, 39, 23, "[ ] Cancel and to menu");

    //Renders the scene
    drawWindow(window);
}

//Just for debug grr
void renderDefaultMap(char* window, char* map, Coordinates*& playerMapPosition)
{
    //Clears all
    std::system("clear");
    clearMap(map);

    //Makes a border
    makeBorder(window);

    //Adds the player and other game objects
    insertPlayerIntoMap(map, playerMapPosition);
    insertInteractionsIntoMap(map, defaultMapScene);

    //Insert the hotbar and map
    insertHotbarToWindow(window);
    drawMapIntoWindow(window, map);

    //Renders the scene
    drawWindow(window);
}

//The function renders the inventory of the player
void renderInventoryScene(char* window)
{
    //Clears all
    std::system("clear");
    clearWindow(window);

    //Makes a border
    makeBorder(window);

    //Adds the title
    drawBox(window, 0, 0, 110, 3);
    writeIntoWindow(window, 47, 1, "Player Inventory");


    //Makes the box for list of the inventory
    drawBox(window, 14, 4, 36, 21);
    char cIncrement = '1';

    //Calculates the inventory
    for(int i = 0; i < 9; i++)
    {
        std::string label(1, cIncrement);

        if(save.player.inv.place[i] == 0)
        {
            writeIntoWindow(window, 18, (6 + (i * 2)), std::string("[ ]  " + label + ":  Empty place"));
            cIncrement++;
            continue;
        }
        for(int j = 0; j < 5; j++)
        {
            if(save.player.inv.place[i] == itemList[j].id)
            {
                writeIntoWindow(window, 18, (6 + (i * 2)), std::string("[ ]  " + label + ":  " + itemList[j].item.name));
                cIncrement++;
                break;
            }
        }
    }

    //Makes a dedicated settings box
    drawBox(window, 60, 9, 35, 11);
    writeIntoWindow(window, 67, 11, "Continue to game (C)");
    writeIntoWindow(window, 70, 14, "View Infos (V)");
    writeIntoWindow(window, 67, 17, "Back to main menu (X)");
        
    //Renders the scene
    drawWindow(window);
}

//The function renders the shop the player can buy from
void renderShopScene(char* window)
{
    //Clears all
    std::system("clear");
    clearWindow(window);

    //Makes a border
    makeBorder(window);

    //Adds the title
    drawBox(window, 0, 0, 110, 3);
    writeIntoWindow(window, 44, 1, "Shop Menu");

    //Makes box for the items that get selled
    drawBox(window, 14, 4, 36, 21);
    char cIncrement = '1';

    //Adds the items that get selled
    for(int i = 0; i < shopScene.interactOptionLength; i++)
    {
        std::string label(1, cIncrement);
        writeIntoWindow(window, 18, (6 + (i * 2)), std::string("[ ]  " + label + ":  " + itemList[i].item.name));
        cIncrement++;
    }

    //Adds the box with the players coins
    drawBox(window, 60, 6, 35, 5);
    std::string write = std::to_string(save.player.coins);
    writeIntoWindow(window, 67, 8, "Current coins: " + write);

    //Makes a dedicated settings box
    drawBox(window, 60, 12, 35, 11);
    writeIntoWindow(window, 67, 14, "Continue to game (C)");
    writeIntoWindow(window, 70, 17, "View Infos (V)");
    writeIntoWindow(window, 67, 20, "Back to main menu (X)");
        
    //Renders the scene
    drawWindow(window);
}



//The functions renders the infos of the knight screen (StartScene)
void insertKnightDetails(char* window)
{
    clearBox(window, 53, 16, 37, 8);
    writeIntoWindow(window, 56, 17, "Knight:");
}

//The functions renders the infos of the wizard screen (StartScene)
void insertWizardDetails(char* window)
{
    clearBox(window, 53, 16, 37, 8);
    writeIntoWindow(window, 56, 17, "Wizard:");
}

//The functions renders the infos of the healer screen (StartScene)
void insertHealerDetails(char* window)
{
    clearBox(window, 53, 16, 37, 8);
    writeIntoWindow(window, 56, 17, "Healer:");
}

//The functions renders the infos of the rouge screen (StartScene)
void insertRougeDetails(char* window)
{
    clearBox(window, 53, 16, 37, 8);
    writeIntoWindow(window, 56, 17, "Rouge:");
}



//The function inserts the generic line of the debug npc
void insertGenericTalkNPC(char* window)
{
    //Makes room for the persons name
    clearBox(window, 8, 13, 25, 3);
    drawBox(window, 8, 13, 25, 3);

    //Write NPCs name
    writeIntoWindow(window, 14, 14, "Garry (Sigma)");

    //Makes room for the speaking line
    clearBox(window, 7, 15, 96, 5);
    drawBox(window, 7, 15, 96, 5);

    //Writes the line
    writeIntoWindow(window, 12, 16, "What a wonderfull and nice debug line from me, on this pretty philosophical day");
    writeIntoWindow(window, 12, 17, "Its also not AI or some shit like Microsoft does, eww.");
    writeIntoWindow(window, 12, 18, "Also, I use Arch BTW. Nevermind I use Windows 7 AeroGlass AHHHH sheesh");

    //Renders the info
    drawWindow(window);
}

//The function insert the default hotbar for map into the window
void insertHotbarToWindow(char* window)
{
    //Makes room for the hotbar
    clearBox(window, 0, 21, 110, 7);
    drawBox(window, 0, 21, 110, 7);

    //Creates the health and mana bar boxes
    drawBox(window, 11, 22, 34, 3);
    drawBox(window, 11, 24, 34, 3);
    writeIntoWindow(window, 5, 23, "HP");
    writeIntoWindow(window, 4, 25, "Mana");

    int write = 0;

    //Calculates the health bar
    for(double i = save.player.atr.maxHP / 30; i <= save.player.atr.HP; i = i + (save.player.atr.maxHP / 30))
    {
        writeIntoWindow(window, 13 + write, 23, "=");
        write++;
    }

    write = 0;

    //Calculates the mana bar
    for(double i = double(save.player.atr.maxMana) / 30; i <= save.player.atr.mana; i = i + (double(save.player.atr.maxMana) / 30))
    {
        writeIntoWindow(window, 13 + write, 25, "=");
        write++;
    }
    
    //Show the equiped item
    drawBox(window, 51, 22, 25, 5);
    if(save.player.inv.place[0] == 0)
    {
        writeIntoWindow(window, 58, 24, "Empty hand");
    }
    else
    {
        for(int j = 0; j < 5; j++)
        {
            if(save.player.inv.place[0] == itemList[j].id)
            {
                writeIntoWindow(window, 57, 24, std::string(itemList[j].item.name));
                break;
            }
        }
    }

    //Makes the settings 
    writeIntoWindow(window, 84, 23, "Open Inventory (I)");
    writeIntoWindow(window, 84, 25, "Open Settings (X)");
}

//The function inserts the settings menu into the window
void insertSettingsMenu(char* window)
{
    //Makes room for the settings menu
    clearBox(window, 37, 9, 36, 9);
    drawBox(window, 37, 9, 36, 9);

    //Adds the title
    drawBox(window, 37, 9, 36, 3);
    writeIntoWindow(window, 49, 10, "Settings Menu");

    //Writes the settings available
    writeIntoWindow(window, 41, 13, "[ ] Continue game");
    writeIntoWindow(window, 41, 15, "[ ] Cancel and to menu");
}

//The function insert the player from given coordinates into the screen
void insertPlayerIntoMap(char* map, Coordinates*& playerMapPosition)
{
    map[playerMapPosition->x + (playerMapPosition->y * 108)] = 'P';
}

//The function insert the info that the game is saved
void insertSavedIntoWindow(char* window)
{
    //Makes space for the info
    clearBox(window, 37, 10, 35, 7);
    drawBox(window, 37, 10, 35, 7);

    //Adds the title
    drawBox(window, 37, 10, 35, 3);
    writeIntoWindow(window, 48, 11, "Save Manager");

    //Writes the info
    writeIntoWindow(window, 42, 14, "The current game is saved");

    //Renders the info
    drawWindow(window);
}



//The function processes the move input of the player in the map
void changePlayerPositionInMap(char* map, Coordinates*& playerMapPosition, const std::string &input, Interactions defaultMapScene)
{
    bool bAllowed = true;

    if(input == "up")
    {
        if(playerMapPosition->y > 0)
        {
            for(int i = 0; i < defaultMapScene.interactOptionLength; i++)
            {
                if(defaultMapScene.interactOption[i].x == playerMapPosition->x && defaultMapScene.interactOption[i].y == playerMapPosition->y - 1)
                {
                    bAllowed = false;
                    break;
                }
            }
            if(bAllowed)
            {
                map[playerMapPosition->x + (playerMapPosition->y * 108)] = ' ';
                map[playerMapPosition->x + ((playerMapPosition->y - 1) * 108)] = 'P';

                playerMapPosition->y = playerMapPosition->y - 1;
            }
        }
    }
    else if(input == "down")
    {
        if(playerMapPosition->y < 19)
        {
            for(int i = 0; i < defaultMapScene.interactOptionLength; i++)
            {
                if(defaultMapScene.interactOption[i].x == playerMapPosition->x && defaultMapScene.interactOption[i].y == playerMapPosition->y + 1)
                {
                    bAllowed = false;
                    break;
                }
            }
            if(bAllowed)
            {
                map[playerMapPosition->x + (playerMapPosition->y * 108)] = ' ';
                map[playerMapPosition->x + ((playerMapPosition->y + 1) * 108)] = 'P';

                playerMapPosition->y = playerMapPosition->y + 1;
            }
        }
    }
    else if(input == "left")
    {
        if(playerMapPosition->x > 0)
        {
            for(int i = 0; i < defaultMapScene.interactOptionLength; i++)
            {
                if(defaultMapScene.interactOption[i].x == playerMapPosition->x - 1 && defaultMapScene.interactOption[i].y == playerMapPosition->y)
                {
                    bAllowed = false;
                    break;
                }
            }
            if(bAllowed)
            {
                map[playerMapPosition->x + (playerMapPosition->y * 108)] = ' ';
                map[(playerMapPosition->x - 1) + (playerMapPosition->y * 108)] = 'P';

                playerMapPosition->x = playerMapPosition->x - 1;
            }
        }
    }
    else if(input == "right")
    {
        if(playerMapPosition->x < 107)
        {
            for(int i = 0; i < defaultMapScene.interactOptionLength; i++)
            {
                if(defaultMapScene.interactOption[i].x == playerMapPosition->x + 1 && defaultMapScene.interactOption[i].y == playerMapPosition->y)
                {
                    bAllowed = false;
                    break;
                }
            }
            if(bAllowed)
            {
                map[playerMapPosition->x + (playerMapPosition->y * 108)] = ' ';
                map[(playerMapPosition->x + 1) + (playerMapPosition->y * 108)] = 'P';

                playerMapPosition->x = playerMapPosition->x + 1;
            }
        }
    }
}

//The function adds custom interactions into the map
void insertInteractionsIntoMap(char* map, Interactions defaultMapScene)
{
    for(int i = 0; i < defaultMapScene.interactOptionLength; i++)
    {
        if (defaultMapScene.interactOption[i].name == "barrier")
        {
            map[defaultMapScene.interactOption[i].x + (defaultMapScene.interactOption[i].y * 108)] = defaultMapScene.interactOption[i].func[0];
        }
        else if (defaultMapScene.interactOption[i].name == "quest")
        {
            map[defaultMapScene.interactOption[i].x + (defaultMapScene.interactOption[i].y * 108)] = '?';
        }
        else if (defaultMapScene.interactOption[i].name == "shop")
        {
            map[defaultMapScene.interactOption[i].x + (defaultMapScene.interactOption[i].y * 108)] = 'S';
        }
        else if (defaultMapScene.interactOption[i].name == "npc")
        {
            map[defaultMapScene.interactOption[i].x + (defaultMapScene.interactOption[i].y * 108)] = 'N';
        }
        else if (defaultMapScene.interactOption[i].name == "statue")
        {
            map[defaultMapScene.interactOption[i].x + (defaultMapScene.interactOption[i].y * 108)] = 'T';
        }
        else
        {
            map[defaultMapScene.interactOption[i].x + (defaultMapScene.interactOption[i].y * 108)] = 'F';
        }
    }
}