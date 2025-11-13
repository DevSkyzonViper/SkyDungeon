#include "PSL.h"

#include <string>




//----------------------------------------------------------------------------------------//
//                          Global Variables to know, where we are                        //
//----------------------------------------------------------------------------------------//


bool mapActive; //Show if we are on a menu or map
Window window; //The global window
Map *currentMap; //Shows the current map we are
Interactions *currentScene; //Shows the current menu-scene we are
Coordinates *currentMenuItem; //Show the specific menu-item we are
Coordinates playerMapPosition; //Show the specific menu-item we are


//A list of Menu Scenes
Interactions startScene;
Interactions newGameScene;
Interactions debugScene;
Interactions settingsScene;
Interactions inventoryScene;
Interactions shopScene;
Interactions popUpMenu;


//A list of the Map Scenes
Map defaultMapScene(108, 20);
Map nextMapScene(108, 20);
Map endMapScene(108, 20);
Map garryHouseMapScene(108, 20);




//----------------------------------------------------------------------------------------//
//                   General function, that always needs to be used FIRST                 //
//----------------------------------------------------------------------------------------//


//Initialized all the scenes (map and menu's)
void initScenes()
{
    Tile tile; //Temporary


    // ---   Initializing the interactions of the menu   --- //


    //The start scene, of the game
    startScene.iNumberInct = 3;
    startScene.interactOption = new Coordinates[3]{{"newGame", 41, 17},{"continueGame", 41, 19},{"exit", 41, 22}};
    startScene.interactOptionVertical = true;

    //The player creation scene
    newGameScene.iNumberInct = 4;
    newGameScene.interactOption = new Coordinates[4]{{"chooseName", 19, 16},{"chooseClass", 19, 18},{"createNewGame", 19, 21},{"startScene", 19, 23}};
    newGameScene.interactOptionVertical = true;

    //The debug scene (temporary)
    debugScene.iNumberInct = 4;
    debugScene.interactOption = new Coordinates[4]{{"openShop", 40, 16},{"openMap", 40, 18},{"openSkillTree", 40, 20},{"startScene", 40, 23}};
    debugScene.interactOptionVertical = true;

    //The settings popup, that shows in the map
    settingsScene.iNumberInct = 2;
    settingsScene.interactOption = new Coordinates[2]{{"openMap", 42, 13},{"startScene", 42, 15}};
    settingsScene.interactOptionVertical = true;

    //The inventory scene for the player
    inventoryScene.iNumberInct = 9;
    inventoryScene.interactOption = new Coordinates[9]{{"inv1", 19, 6},{"inv2", 19, 8},{"inv3", 19, 10},{"inv4", 19, 12},{"inv5", 19, 14},{"inv6", 19, 16},{"inv7", 19, 18},{"inv8", 19, 20},{"inv9", 19, 22}};
    inventoryScene.interactOptionVertical = true;

    //The shop scene to buy things from, that gets opened from the map
    shopScene.iNumberInct = 5;
    shopScene.interactOption = new Coordinates[5]{{"item1", 19, 6},{"item2", 19, 8},{"item3", 19, 10},{"item4", 19, 12},{"item5", 19, 14}};
    shopScene.interactOptionVertical = true;

    //General pop up menu, that gets used by the NPC's, and the save-manager
    popUpMenu.iNumberInct = 1;
    popUpMenu.interactOption = new Coordinates[1]{"openMap", 0, 0};
    popUpMenu.interactOptionVertical = true;



    
    // ---   Initializing the interactions of the map: DebugMap   --- //


    //2x2 Box - Red Barrier
    tile = {'#', "red", "default", "NULL", "NULL", false};
    defaultMapScene.changeTileBox(16, 8, 2, 2, tile);
    
    //1x Save-Point
    tile = {'T', "blue", "default", "NULL", "savePoint", false};
    defaultMapScene.changeTile(58, 8, tile);
    
    //1x Shop
    tile = {'S', "yellow", "default", "NULL", "openShop", false};
    defaultMapScene.changeTile(14, 14, tile);

    //1x NPC: Garry (Sigma)
    tile = {'N', "orange", "default", "NULL", "NULL", false};
    defaultMapScene.changeTile(15, 17, tile);

    //Interaction field around the NPC: Garry (Sigma)
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    defaultMapScene.changeTile(14, 17, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    defaultMapScene.changeTile(16, 17, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    defaultMapScene.changeTile(15, 16, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    defaultMapScene.changeTile(15, 18, tile);

    //Interaction Field to change the map: BOTTOM (x)
    tile = {' ', "default", "white", "spawnNext", "NULL", true};
    defaultMapScene.changeTileBox(52, 19, 7, 1, tile);



    
    // ---   Initializing the interactions of the map: NextMap   --- //


    //2x2 Box - Red Barrier
    tile = {'#', "red", "default", "NULL", "NULL", false};
    nextMapScene.changeTileBox(85, 15, 2, 2, tile);
    
    //1x Save-Point
    tile = {'T', "blue", "default", "NULL", "savePoint", false};
    nextMapScene.changeTile(23, 6, tile);
    
    //1x Shop
    tile = {'S', "yellow", "default", "NULL", "openShop", false};
    nextMapScene.changeTile(34, 18, tile);

    //1x NPC: Garry (Sigma)
    tile = {'N', "orange", "default", "NULL", "NULL", false};
    nextMapScene.changeTile(63, 11, tile);

    //Interaction field around the NPC: Garry (Sigma)
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    nextMapScene.changeTile(62, 11, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    nextMapScene.changeTile(64, 11, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    nextMapScene.changeTile(63, 10, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    nextMapScene.changeTile(63, 12, tile);

    //Interaction Field to change the map: TOP (x)
    tile = {' ', "default", "white", "spawnBack", "NULL", true};
    nextMapScene.changeTileBox(52, 0, 7, 1, tile);

    //1x House: Garry (Sigma)
    tile = {'#', "default", "default", "NULL", "NULL", false};
    nextMapScene.changeTileBox(8, 12, 8, 1, tile);
    tile = {'@', "default", "default", "NULL", "NULL", false};
    nextMapScene.changeTileBox(9, 13, 7, 1, tile);
    tile = {'#', "default", "default", "NULL", "NULL", false};
    nextMapScene.changeTileBox(8, 14, 8, 1, tile);
    tile = {'#', "default", "default", "NULL", "NULL", false};
    nextMapScene.changeTileBox(8, 17, 8, 1, tile);
    tile = {'#', "default", "default", "NULL", "NULL", false};
    nextMapScene.changeTileBox(8, 12, 1, 6, tile);
    tile = {'#', "default", "default", "NULL", "NULL", false};
    nextMapScene.changeTileBox(10, 16, 5, 1, tile);
    tile = {'#', "default", "default", "NULL", "NULL", false};
    nextMapScene.changeTileBox(16, 12, 1, 6, tile);
    tile = {' ', "default", "white", "spawnGarryHouse", "NULL", true};
    nextMapScene.changeTileBox(11, 17, 3, 1, tile);

    //Interaction Field to change the map: RIGHT (x)
    tile = {' ', "default", "white", "spawnEnd", "NULL", true};
    nextMapScene.changeTileBox(107, 9, 1, 3, tile);



    // ---   Initializing the interactions of the map: Garrys House   --- //

    //28x19 Box - Barrier (LEFT & RIGHT)
    tile = {'#', "default", "default", "NULL", "NULL", false};
    garryHouseMapScene.changeTileBox(1, 0, 27, 20, tile);
    tile = {'#', "default", "default", "NULL", "NULL", false};
    garryHouseMapScene.changeTileBox(79, 0, 27, 20, tile);

    //2x2 Box - Red Barrier
    tile = {'#', "red", "default", "NULL", "NULL", false};
    garryHouseMapScene.changeTileBox(43, 11, 2, 2, tile);
    
    //1x Save-Point
    tile = {'T', "blue", "default", "NULL", "savePoint", false};
    garryHouseMapScene.changeTile(63, 3, tile);
    
    //1x Shop
    tile = {'S', "yellow", "default", "NULL", "openShop", false};
    garryHouseMapScene.changeTile(42, 8, tile);

    //1x NPC: Garry (Sigma)
    tile = {'N', "orange", "default", "NULL", "NULL", false};
    garryHouseMapScene.changeTile(35, 5, tile);

    //Interaction field around the NPC: Garry (Sigma)
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    garryHouseMapScene.changeTile(34, 5, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    garryHouseMapScene.changeTile(36, 5, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    garryHouseMapScene.changeTile(35, 4, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    garryHouseMapScene.changeTile(35, 6, tile);

    //Interaction Field to change the map: DOWN (x)
    tile = {' ', "default", "white", "spawnNext", "NULL", true};
    garryHouseMapScene.changeTileBox(54, 19, 3, 1, tile);




    
    // ---   Initializing the interactions of the map: EndMap   --- //

    //28x19 Box - Barrier (LEFT & RIGHT)
    tile = {'#', "default", "default", "NULL", "NULL", false};
    endMapScene.changeTileBox(1, 0, 27, 20, tile);
    tile = {'#', "default", "default", "NULL", "NULL", false};
    endMapScene.changeTileBox(79, 0, 27, 20, tile);

    //2x2 Box - Red Barrier
    tile = {'#', "red", "default", "NULL", "NULL", false};
    endMapScene.changeTileBox(43, 11, 2, 2, tile);
    
    //1x Save-Point
    tile = {'T', "blue", "default", "NULL", "savePoint", false};
    endMapScene.changeTile(63, 3, tile);
    
    //1x Shop
    tile = {'S', "yellow", "default", "NULL", "openShop", false};
    endMapScene.changeTile(42, 8, tile);

    //1x NPC: Garry (Sigma)
    tile = {'N', "orange", "default", "NULL", "NULL", false};
    endMapScene.changeTile(35, 5, tile);

    //Interaction field around the NPC: Garry (Sigma)
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    endMapScene.changeTile(34, 5, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    endMapScene.changeTile(36, 5, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    endMapScene.changeTile(35, 4, tile);
    tile = {' ', "default", "default", "genericNPC", "NULL", true};
    endMapScene.changeTile(35, 6, tile);

    //Interaction Field to change the map: LEFT (x)
    tile = {' ', "default", "white", "spawnNext", "NULL", true};
    endMapScene.changeTileBox(28, 9, 1, 3, tile);



    // ---   Initializing startup thingys   --- //
    mapActive = false;
    currentScene = &startScene;
    currentMenuItem = &startScene.interactOption[0];

    //Sets the default position on the debug map
    defaultMapScene.setPlayerPos(30, 10);
}




//----------------------------------------------------------------------------------------//
//                       Render functions, specifically for the menus                     //
//----------------------------------------------------------------------------------------//


//The functions renders the start screen of the game
void renderStartScene(Window &window)
{

    //Clears all
    window.clearWindow();
    std::system("clear");

    //Makes a border
    window.makeBorder();

    //Makes the logo 
    drawLogoToWindow(window);

    //Makes a dedicated settings box
    window.makeBox(35, 15, 40, 10);
    window.writeIntoWindow(40, 17, "[*] Create a new game");
    window.writeIntoWindow(40, 19, "[ ] Continue");
    window.writeIntoWindow(40, 22, "[ ] Exit the game");

    //Renders the scene
    window.render();
}

//The function renders the newGameScene where a new character is created
void renderNewGameScene(Window &window)
{
    //Clears all
    window.clearWindow();
    std::system("clear");

    //Makes the border
    window.makeBorder();

    //Makes the logo
    drawLogoToWindow(window);

    //Makes the input box
    window.makeBox(15, 14, 80, 12);
    window.writeIntoWindow(18, 16, "[*] Playername: (____________)");
    window.writeIntoWindow(18, 18, "[ ] PlayerClass: (1)");
    window.writeIntoWindow(18, 21, "[ ] Continue");
    window.writeIntoWindow(18, 23, "[ ] Cancel and to menu");

    //Makes a info box for the classes
    window.makeBox(53, 16, 37, 8);
    insertKnightDetails(window);

    //Renders the scene
    window.render();
}

//Just for debug grr
void renderDebugScene(Window &window)
{
    //Clears all
    window.clearWindow();
    std::system("clear");

    //Makes a border
    window.makeBorder();

    //Makes the logo
    drawLogoToWindow(window);

    //Makes the dedicated debug settings
    window.makeBox(36, 14, 32, 12);
    window.writeIntoWindow(39, 16, "[*] Open the shop");
    window.writeIntoWindow(39, 18, "[ ] Open the map");
    window.writeIntoWindow(39, 20, "[ ] Open the skill list");
    window.writeIntoWindow(39, 23, "[ ] Cancel and to menu");

    //Renders the scene
    window.render();
}

//The function renders the inventory of the player
void renderInventoryScene(Window &window)
{
    //Clears all
    std::system("clear");
    window.clearWindow();

    //Makes a border
    window.makeBorder();

    //Adds the title
    window.makeBox(0, 0, 110, 3);
    window.writeIntoWindow(47, 1, "Player Inventory");


    //Makes the box for list of the inventory
    window.makeBox(14, 4, 36, 21);
    char cIncrement = '1';

    //Calculates the inventory
    for(int i = 0; i < 9; i++)
    {
        std::string label(1, cIncrement);

        if(save.player.inv.place[i] == 0)
        {
            window.writeIntoWindow(18, (6 + (i * 2)), std::string("[ ]  " + label + ":  Empty place"));
            cIncrement++;
            continue;
        }
        for(int j = 0; j < 5; j++)
        {
            if(save.player.inv.place[i] == itemList[j].id)
            {
                window.writeIntoWindow(18, (6 + (i * 2)), std::string("[ ]  " + label + ":  " + itemList[j].item.name));
                cIncrement++;
                break;
            }
        }
    }

    //Makes a dedicated settings box
    window.makeBox(60, 9, 35, 11);
    window.writeIntoWindow(67, 11, "Continue to game (C)");
    window.writeIntoWindow(70, 14, "View Infos (V)");
    window.writeIntoWindow(67, 17, "Back to main menu (X)");
        
    //Renders the scene
    window.render();
}

//The function renders the shop the player can buy from
void renderShopScene(Window &window)
{
    //Clears all
    std::system("clear");
    window.clearWindow();

    //Makes a border
    window.makeBorder();

    //Adds the title
    window.makeBox(0, 0, 110, 3);
    window.writeIntoWindow(44, 1, "Shop Menu");

    //Makes box for the items that get selled
    window.makeBox(14, 4, 36, 21);
    char cIncrement = '1';

    //Adds the items that get selled
    for(int i = 0; i < shopScene.iNumberInct; i++)
    {
        std::string label(1, cIncrement);
        window.writeIntoWindow(18, (6 + (i * 2)), std::string("[ ]  " + label + ":  " + itemList[i].item.name));
        cIncrement++;
    }

    //Adds the box with the players coins
    window.makeBox(60, 6, 35, 5);
    std::string write = std::to_string(save.player.coins);
    window.writeIntoWindow(67, 8, "Current coins: " + write);

    //Makes a dedicated settings box
    window.makeBox(60, 12, 35, 11);
    window.writeIntoWindow(67, 14, "Continue to game (C)");
    window.writeIntoWindow(70, 17, "View Infos (V)");
    window.writeIntoWindow(67, 20, "Back to main menu (X)");
        
    //Renders the scene
    window.render();
}




//----------------------------------------------------------------------------------------//
//                       Render functions, specifically for the maps                      //
//----------------------------------------------------------------------------------------//


//The function renders a default map, that can be customized
void renderDefaultMap(Window &window, Map &map)
{
    //Clears all
    std::system("clear");
    //map.clearMap();

    //Makes a border
    window.makeBorder();
    window.makeBox(0, 0, 110, 22);

    //Insert the hotbar and map
    insertHotbarToWindow(window);

    //Draws map onto the window
    window.drawMap(1, 1, map);

    //Renders the scene
    window.render();
}




//----------------------------------------------------------------------------------------//
//                       Extra function for add-ons to menus or maps                      //
//----------------------------------------------------------------------------------------//


//The function draws the logo to the window
void drawLogoToWindow(Window &window)
{
    window.writeIntoWindow(5, 3, R"( $$$$$$\  $$\                 $$$$$$$\                                                              )");
    window.writeIntoWindow(5, 4, R"($$  __$$\ $$ |                $$  __$$\                                                             )");
    window.writeIntoWindow(5, 5, R"($$ /  \__|$$ |  $$\ $$\   $$\ $$ |  $$ |$$\   $$\ $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$\  )");
    window.writeIntoWindow(5, 6, R"(\$$$$$$\  $$ | $$  |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ )");
    window.writeIntoWindow(5, 7, R"( \____$$\ $$$$$$  / $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |$$$$$$$$ |$$ /  $$ |$$ |  $$ |)");
    window.writeIntoWindow(5, 8, R"($$\   $$ |$$  _$$<  $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$   ____|$$ |  $$ |$$ |  $$ |)");
    window.writeIntoWindow(5, 9, R"(\$$$$$$  |$$ | \$$\ \$$$$$$$ |$$$$$$$  |\$$$$$$  |$$ |  $$ |\$$$$$$$ |\$$$$$$$\ \$$$$$$  |$$ |  $$ |)");
    window.writeIntoWindow(5,10, R"( \______/ \__|  \__| \____$$ |\_______/  \______/ \__|  \__| \____$$ | \_______| \______/ \__|  \__|)");
    window.writeIntoWindow(5,11, R"(                    $$\   $$ |                              $$\   $$ |                              )");
    window.writeIntoWindow(5,11, R"(                    \$$$$$$  |                              \$$$$$$  |                              )");
    window.writeIntoWindow(5,11, R"(                     \______/                                \______/                               )");
}

//The functions renders the infos of the knight screen (StartScene)
void insertKnightDetails(Window &window)
{
    window.clearBox(53, 16, 37, 8);
    window.writeIntoWindow(56, 17, "Knight:");
}

//The functions renders the infos of the wizard screen (StartScene)
void insertWizardDetails(Window &window)
{
    window.clearBox(53, 16, 37, 8);
    window.writeIntoWindow(56, 17, "Wizard:");
}

//The functions renders the infos of the healer screen (StartScene)
void insertHealerDetails(Window &window)
{
    window.clearBox(53, 16, 37, 8);
    window.writeIntoWindow(56, 17, "Healer:");
}

//The functions renders the infos of the rouge screen (StartScene)
void insertRougeDetails(Window &window)
{
    window.clearBox(53, 16, 37, 8);
    window.writeIntoWindow(56, 17, "Rouge:");
}

//The function insert the info that the game is saved
void insertSavedIntoWindow(Window &window)
{
    //Makes room for the settings menu
    window.clearBox(33, 9, 44, 9);
    window.makeBox(33, 9, 44, 9, "yellow");

    //Adds the title
    window.makeBox(33, 9, 44, 3, "yellow");
    window.writeIntoWindow(49, 10, "Save-Manager");

    //Writes the settings available
    window.writeIntoWindow(37, 13, "The current game was save succesfull");
    window.writeIntoWindow(41, 15, "Press enter key to continue");
}

//The function inserts the generic line of the debug npc
void insertGenericTalkNPC(Window &window)
{
    //Makes room for the speaking line
    window.clearBox(7, 15, 96, 5);
    window.makeBox(7, 15, 96, 5, "yellow");

    //Makes room for the persons name
    window.clearBox(9, 13, 25, 3);
    window.makeBox(9, 13, 25, 3, "red");

    //Write NPCs name
    window.writeIntoWindow(15, 14, "Garry (Sigma)");

    //Writes the line
    window.writeIntoWindow(12, 16, "What a wonderfull and nice debug line from me, on this pretty philosophical day");
    window.writeIntoWindow(12, 17, "Its also not AI or some shit like Microsoft does, eww.");
    window.writeIntoWindow(12, 18, "Also, I use Arch BTW. Nevermind I use Windows 7 AeroGlass AHHHH sheesh");

    //Renders the info
    window.render();
}

//The function insert the default hotbar for map into the window
void insertHotbarToWindow(Window &window)
{
    //Makes room for the hotbar
    window.clearBox(0, 21, 110, 7);
    window.makeBox(0, 21, 110, 7);

    //Creates the health and mana bar boxes
    window.makeBox(11, 22, 34, 3);
    window.makeBox(11, 24, 34, 3);
    window.writeIntoWindow(5, 23, "HP");
    window.writeIntoWindow(4, 25, "Mana");

    int write = 0;

    //Calculates the health bar
    for(double i = save.player.atr.maxHP / 30.0; i <= save.player.atr.HP; i = i + (save.player.atr.maxHP / 30.0))
    {
        window.writeIntoWindow(13 + write, 23, "=");
        write++;
    }

    write = 0;

    //Calculates the mana bar
    for(double i = double(save.player.atr.maxMana) / 30.0; i <= save.player.atr.mana; i = i + (double(save.player.atr.maxMana) / 30.0))
    {
        window.writeIntoWindow(13 + write, 25, "=");
        write++;
    }
    
    //Show the equiped item
    window.makeBox(51, 22, 25, 5);
    if(save.player.inv.place[0] == 0)
    {
        window.writeIntoWindow(58, 24, "Empty hand");
    }
    else
    {
        for(int j = 0; j < 5; j++)
        {
            if(save.player.inv.place[0] == itemList[j].id)
            {
                window.writeIntoWindow(57, 24, std::string(itemList[j].item.name));
                break;
            }
        }
    }

    //Makes the settings 
    window.writeIntoWindow(84, 23, "Open Inventory (I)");
    window.writeIntoWindow(84, 25, "Open Settings (X)");
}

//The function inserts the settings menu into the window
void insertSettingsMenu(Window &window)
{
    //Makes room for the settings menu
    window.clearBox(37, 9, 36, 9);
    window.makeBox(37, 9, 36, 9, "yellow");

    //Adds the title
    window.makeBox(37, 9, 36, 3, "yellow");
    window.writeIntoWindow(49, 10, "Settings Menu");

    //Writes the settings available
    window.writeIntoWindow(41, 13, "[ ] Continue game");
    window.writeIntoWindow(41, 15, "[ ] Cancel and to menu");
}



