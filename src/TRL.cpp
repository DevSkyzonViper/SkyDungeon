#include "TRL.h"
#include "PSL.h"

#include <iostream>
#include <string>


//----------------------------------------------------------------------------------------//
//                           Window-Class and all its functions                           //
//----------------------------------------------------------------------------------------//


/* ------- Standard-Window ------- */
Window::Window()
{
    iWidth = 110;
    iHeight = 28;
    tilemap = new Tile[iWidth * iHeight];

    for (int i = 0; i < iWidth * iHeight; ++i)
    {
        tilemap[i].cChar = ' ';
    }
}

/* ------- Sizeable-Window ------- */
Window::Window(int iWidth, int iHeight)
{
    this->iWidth = iWidth;
    this->iHeight = iHeight;
    tilemap = new Tile[iWidth * iHeight];

    for (int i = 0; i < iWidth * iHeight; ++i)
    {
        tilemap[i].cChar = ' ';
    }
}

/* ------- Destrukt-Window ------- */
Window::~Window()
{
    delete[] tilemap;
}


//Write a text string into the window
void Window::writeIntoWindow(int x, int y, std::string sText)
{
    for(int i = 0; i < sText.size(); i++)
    {
        this->at(x + i, y).cChar = sText[i];
        this->at(x + i, y).sTextColor = "default";
    }
}

//Draws a border onto the window
void Window::makeBorder()
{
    for(int i = 0; i < iWidth; i++)
    {
        this->at(i, 0).cChar = '#';
        this->at(i, iHeight - 1).cChar = '#';
    }

    for(int j = 1; j < iHeight - 1; j++)
    {
        this->at(0, j).cChar = '#';
        this->at(iWidth - 1, j).cChar = '#';
    }
}

//Clears a field for a box
void Window::clearBox(int x, int y, int boxWidth, int boxHeight)
{
    for (int j = 1; j < boxHeight - 1; ++j)
    {
        int posY = y + j;
        if (posY < 0 || posY >= iHeight) continue;
        for (int i = 1; i < boxWidth - 1; ++i)
        {
            int posX = x + i;
            if (posX < 0 || posX >= iWidth) continue;

            this->at(posX, posY).cChar = ' ';
            this->at(posX, posY).sTextColor = "default";
            this->at(posX, posY).sBackColor = "default";
        }
    }
}

//Draws a box onto the window
void Window::makeBox(int x, int y, int boxWidth, int boxHeight)
{
    if(x < 0 || y < 0 || x >= iWidth || y >= iHeight)
    {
        return;
    }
    for(int j = 0; j < boxHeight; j++)
    {
        int posY = y + j;
        if(posY >= iHeight)
        {
            break; // nicht über Fenster hinaus
        }
        for(int i = 0; i < boxWidth; i++)
        {
            int posX = x + i;
            if(posX >= iWidth)
            {
                break;
            }
            if(j == 0 || j == boxHeight - 1 || i == 0 || i == boxWidth - 1)
            {
                this->at(posX, posY).cChar = '#';
                this->at(posX, posY).sTextColor = "default";
            }
        }
    }
}

//Draws a box onto the window
void Window::makeBox(int x, int y, int boxWidth, int boxHeight, std::string sColor)
{
    if(x < 0 || y < 0 || x >= iWidth || y >= iHeight)
    {
        return;
    }
    for(int j = 0; j < boxHeight; j++)
    {
        int posY = y + j;
        if(posY >= iHeight)
        {
            break; // nicht über Fenster hinaus
        }
        for(int i = 0; i < boxWidth; i++)
        {
            int posX = x + i;
            if(posX >= iWidth)
            {
                break;
            }
            if(j == 0 || j == boxHeight - 1 || i == 0 || i == boxWidth - 1)
            {
                this->at(posX, posY).cChar = '#';
                this->at(posX, posY).sTextColor = sColor;
            }
        }
    }
}

//Draws a box onto the window
void Window::makeBox(int x, int y, int boxWidth, int boxHeight, std::string sColor, std::string sBackColor)
{
    if(x < 0 || y < 0 || x >= iWidth || y >= iHeight)
    {
        return;
    }
    for(int j = 0; j < boxHeight; j++)
    {
        int posY = y + j;
        if(posY >= iHeight)
        {
            break; // nicht über Fenster hinaus
        }
        for(int i = 0; i < boxWidth; i++)
        {
            int posX = x + i;
            if(posX >= iWidth)
            {
                break;
            }
            if(j == 0 || j == boxHeight - 1 || i == 0 || i == boxWidth - 1)
            {
                this->at(posX, posY).cChar = '#';
                this->at(posX, posY).sTextColor = sColor;
                this->at(posX, posY).sBackColor = sBackColor;
            }
        }
    }
}

//Clears the whole window
void Window::clearWindow()
{
    for (int i = 0; i < iWidth * iHeight; ++i)
    {
        tilemap[i].cChar = ' ';
        tilemap[i].sTextColor = "default";
        tilemap[i].sBackColor = "default";
    }
}

//Draws the map onto the window
void Window::drawMap(int x, int y, Map &map)
{
    for (int j = 0; j < map.getHeight(); ++j)
    {
        int posY = y + j;
        if (posY < 0 || posY >= iHeight) continue;
        for (int i = 0; i < map.getWidth(); ++i)
        {
            int posX = x + i;
            if (posX < 0 || posX >= iWidth) continue;

            this->at(posX, posY).cChar = map.at(i, j).cChar;
            this->at(posX, posY).sTextColor = map.at(i, j).sTextColor;
            this->at(posX, posY).sBackColor = map.at(i, j).sBackColor;
        }
    }
}

//Renders the window onto the screen
void Window::render()
{
    std::system("clear");

    for (int j = 0; j < iHeight; j++)
    {
        for (int i = 0; i < iWidth; i++)
        {
            //Map Area will get checked for color
            if (i >= 1 && i <= 109 && j >= 1 && j <= 22)
            {
                if(this->at(i, j).sTextColor == "black")
                {
                    std::cout << "\033[30m";
                }
                else if(this->at(i, j).sTextColor == "red")
                {
                    std::cout << "\033[31m";
                }
                else if(this->at(i, j).sTextColor == "green")
                {
                    std::cout << "\033[32m";
                }
                else if(this->at(i, j).sTextColor == "yellow")
                {
                    std::cout << "\033[33m";
                }
                else if(this->at(i, j).sTextColor == "blue")
                {
                    std::cout << "\033[34m";
                }
                else if(this->at(i, j).sTextColor == "magenta")
                {
                    std::cout << "\033[35m";
                }
                else if(this->at(i, j).sTextColor == "cyan")
                {
                    std::cout << "\033[36m";
                }
                else if(this->at(i, j).sTextColor == "white" || this->at(i, j).sTextColor == "default")
                {
                    std::cout << "\033[37m";
                }

                if(this->at(i, j).sBackColor == "black" || this->at(i, j).sBackColor == "default")
                {
                    std::cout << "\033[40m";
                }
                else if(this->at(i, j).sBackColor == "red")
                {
                    std::cout << "\033[41m";
                }
                else if(this->at(i, j).sBackColor == "green")
                {
                    std::cout << "\033[42m";
                }
                else if(this->at(i, j).sBackColor == "yellow")
                {
                    std::cout << "\033[43m";
                }
                else if(this->at(i, j).sBackColor == "blue")
                {
                    std::cout << "\033[44m";
                }
                else if(this->at(i, j).sBackColor == "magenta")
                {
                    std::cout << "\033[45m";
                }
                else if(this->at(i, j).sBackColor == "cyan")
                {
                    std::cout << "\033[46m";
                }
                else if(this->at(i, j).sBackColor == "white")
                {
                    std::cout << "\033[47m";
                }
            }
            std::cout << this->at(i, j).cChar;
            std::cout << "\033[0m";
        }
        std::cout << std::endl;
    }

    // Reset am Ende
    std::cout << "\033[0m";
}




//----------------------------------------------------------------------------------------//
//                           Map-Class and all its functions                           //
//----------------------------------------------------------------------------------------//


/* ------- Standard-Map ------- */
Map::Map()
{
    iWidth = 108;
    iHeight = 20;
    tilemap = new Tile[iWidth * iHeight];

    playerPos.name = "NULL";
    playerPos.x = 0;
    playerPos.y = 0;


    for (int i = 0; i < iWidth * iHeight; ++i)
    {
        tilemap[i].cChar = ' ';
        tilemap[i].sTextColor = "default";
        tilemap[i].sBackColor = "default";
        tilemap[i].sOnMove = "NULL";
        tilemap[i].sOnInteract = "NULL";
        tilemap[i].walkable = true;
    }
}

/* ------- Sizeable-Map ------- */
Map::Map(int iWidth, int iHeight)
{
    this->iWidth = iWidth;
    this->iHeight = iHeight;
    tilemap = new Tile[iWidth * iHeight];

    playerPos.name = "NULL";
    playerPos.x = 40;
    playerPos.y = 0;

    for (int i = 0; i < iWidth * iHeight; ++i)
    {
        tilemap[i].cChar = ' ';
        tilemap[i].sTextColor = "default";
        tilemap[i].sBackColor = "default";
        tilemap[i].sOnMove = "NULL";
        tilemap[i].sOnInteract = "NULL";
        tilemap[i].walkable = true;
    }
}

/* ------- Destrukt-Map ------- */
Map::~Map()
{
    delete[] tilemap;
}


//Returns the players infos
Coordinates Map::getPlayerPos()
{
    return playerPos;
}

//Deletes the player from the map
void Map::deletePlayerPos()
{
    //Sets the player on the map
    this->at(this->getPlayerPos().x, this->getPlayerPos().y).cChar = ' ';
    this->at(this->getPlayerPos().x, this->getPlayerPos().y).sTextColor = "default";
}

//Sets the players position
void Map::setPlayerPos(int x, int y)
{
    //Sets the player on the map
    this->at(x, y).cChar = 'P';
    this->at(x, y).sTextColor = "green";

    //Sets the position
    playerPos.x = x;
    playerPos.y = y;
}

//Sets the players position
bool Map::changePlayerPos(std::string input)
{
    if(input == "up")
    {
        if(playerPos.y > 0 && this->at(playerPos.x, playerPos.y - 1).walkable)
        {
            this->at(playerPos.x, playerPos.y).cChar = ' ';
            this->at(playerPos.x, playerPos.y).sTextColor = "default";

            this->at(playerPos.x, playerPos.y - 1).cChar = 'P';
            this->at(playerPos.x, playerPos.y - 1).sTextColor = "green";

            playerPos.y--;
            return true;
        }
    }
    else if(input == "down")
    {
        if(playerPos.y < iHeight - 1 && this->at(playerPos.x, playerPos.y + 1).walkable)
        {
            this->at(playerPos.x, playerPos.y).cChar = ' ';
            this->at(playerPos.x, playerPos.y).sTextColor = "default";

            this->at(playerPos.x, playerPos.y + 1).cChar = 'P';
            this->at(playerPos.x, playerPos.y + 1).sTextColor = "green";

            playerPos.y++;
            return true;
        }
    }
    else if(input == "right")
    {
        if(playerPos.x < iWidth - 1 && this->at(playerPos.x + 1, playerPos.y).walkable)
        {
            this->at(playerPos.x, playerPos.y).cChar = ' ';
            this->at(playerPos.x, playerPos.y).sTextColor = "default";

            this->at(playerPos.x + 1, playerPos.y).cChar = 'P';
            this->at(playerPos.x + 1, playerPos.y).sTextColor = "green";

            playerPos.x++;
            return true;
        }
    }
    else if(input == "left")
    {
        if(playerPos.x > 0 && this->at(playerPos.x - 1, playerPos.y).walkable)
        {
            this->at(playerPos.x, playerPos.y).cChar = ' ';
            this->at(playerPos.x, playerPos.y).sTextColor = "default";

            this->at(playerPos.x - 1, playerPos.y).cChar = 'P';
            this->at(playerPos.x - 1, playerPos.y).sTextColor = "green";

            playerPos.x--;
            return true;
        }
    }
    return false;
}

//Changes a tile for making custom maps
void Map::changeTile(int x, int y, Tile &tile)
{
    this->at(x, y).cChar = tile.cChar;
    this->at(x, y).sTextColor = tile.sTextColor;
    this->at(x, y).sBackColor = tile.sBackColor;
    this->at(x, y).sOnMove = tile.sOnMove;
    this->at(x, y).sOnInteract = tile.sOnInteract;
    this->at(x, y).walkable = tile.walkable;
}

// Example robust implementation; adapt types/names to your headers
void Map::changeTileBox(int x, int y, int boxWidth, int boxHeight, Tile &tile)
{
    for(int i = 0; i < boxWidth; i++)
    {
        for(int j = 0; j < boxHeight; j++)
        {
            this->at(x + i, y + j).cChar = tile.cChar;
            this->at(x + i, y + j).sTextColor = tile.sTextColor;
            this->at(x + i, y + j).sBackColor = tile.sBackColor;
            this->at(x + i, y + j).sOnMove = tile.sOnMove;
            this->at(x + i, y + j).sOnInteract = tile.sOnInteract;
            this->at(x + i, y + j).walkable = tile.walkable;
        }
    }
}

//Adds & changes an Interaction
void Map::changeInteraction(int x, int y, std::string sOnMove, std::string sOnInteract)
{
    this->at(x, y).sOnMove = sOnMove;
    this->at(x, y).sOnInteract = sOnInteract;
}

//Returns the Map height
int Map::getHeight()
{
    return iHeight;
}

//Returns the Map width
int Map::getWidth()
{
    return iWidth;
}


