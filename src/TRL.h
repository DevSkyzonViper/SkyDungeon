#ifndef TRL_H
#define TRL_H

#include <string>




//----------------------------------------------------------------------------------------//
//                          All necesary struct implementations                           //
//----------------------------------------------------------------------------------------//


//A single tile on a map/window
struct Tile
{
    char cChar; //Character displayed
    std::string sTextColor; //Color of the char
    std::string sBackColor; //Background color
    std::string sOnMove; //Interaction on move
    std::string sOnInteract; //Interaction on interacting
    bool walkable; //Collision for walking
};

//Coordinates for a player/monster
struct Coordinates
{
    std::string name; //Current interaction name
    int x; //X-Coordinate
    int y; //Y-Coordinate

    bool operator==(const Coordinates& other) const
    {
        return x == other.x && y == other.y && name == other.name;
    }
};

//A list of Menu Interactions
struct Interactions
{
    int iNumberInct;
    Coordinates *interactOption;
    bool interactOptionVertical;

    bool operator==(const Interactions& other) const
    {
        return iNumberInct == other.iNumberInct && interactOption == other.interactOption && interactOptionVertical == other.interactOptionVertical;
    }
};




//----------------------------------------------------------------------------------------//
//                           Map-Class and all its functions                           //
//----------------------------------------------------------------------------------------//


class Map
{
    private:
        int iWidth; //Width of the Map
        int iHeight; //Height of the Map
        Tile *tilemap; //The contents of the Map
        Coordinates playerPos; //Position of the player
        
    public:
        Map();
        Map(int iWidth, int iHeight);
        ~Map();

        Tile& at(int x,int y) {
             return this->tilemap[(y * iWidth) + x];
        }

        Coordinates getPlayerPos(); //Returns the players infos
        void deletePlayerPos(); //Deletes the player from the map
        void setPlayerPos(int x, int y); //Sets the players position
        //Returns the interaction that should happen
        bool changePlayerPos(std::string input); //Changes the players position
        void changeTile(int x, int y, Tile &tile); //Changes a tile of the map
        void changeTileBox(int x, int y, int boxWidth, int boxHeight, Tile &tile); //Changes a box  of tiles of the map
        void changeInteraction(int x, int y, std::string sOnMove, std::string sOnInteract); //Adds & changes an Interaction
        int getHeight(); //Returns the Map height
        int getWidth(); //Returns the Map width
};




//----------------------------------------------------------------------------------------//
//                           Window-Class and all its functions                           //
//----------------------------------------------------------------------------------------//


class Window
{
    private:
        int iWidth; //Width of the Window
        int iHeight; //Height of the Window
        Tile *tilemap; //The contents of the Window
    
    public:
        Window();
        Window(int iWidth, int iHeight);
        ~Window();

        Tile& at(int x,int y) { return this->tilemap[(y * iWidth) + x]; }

        void writeIntoWindow(int x, int y, std::string sText); //Writes text onto the window
        void makeBorder(); //Draws a border onto the window
        void clearBox(int x, int y, int boxWidth, int boxHeight); //Clears a field for a box
        void makeBox(int x, int y, int boxWidth, int boxHeight); //Draws a box onto the window
        void makeBox(int x, int y, int boxWidth, int boxHeight, std::string sColor); //Draws a box onto the window
        void makeBox(int x, int y, int boxWidth, int boxHeight, std::string sColor, std::string sBackColor); //Draws a box onto the window
        void clearWindow(); //Clears the whole window
        void drawMap(int x, int y, Map &map); //Draws the map onto the window
        void render(); //Renders the window onto the screen
};



#endif