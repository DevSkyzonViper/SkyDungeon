#ifndef IPL_HPP
#define IPL_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>

#include "SGL.hpp"
#include "IL.hpp"

extern struct termios orig_termios;

struct Coordinates {
    std::string name;
    int x;
    int y;
    std::string func;

    bool operator==(const Coordinates& other) const {
        return x == other.x && y == other.y;
    }
};

struct Interactions {
    Coordinates* interactOption;
    int interactOptionLength;
    bool interactOptionVertical;
};

//Terminal reset
void resetTerminal();

//Dynamic input processing
void enableRawMode();


//The function processes the general inputs of the user
void processGeneralInput(char* window, char* map, bool* mapActive, Coordinates*& playerMapPosition, const std::string &input, Coordinates*& cursorPosition, Interactions*& inct);

//The function processes the enter input of the user
bool processEnterInput(char* window, char* map, bool* mapActive, Coordinates*& playerMapPosition, Interactions*& inct, Coordinates*& cursorPosition);

//The function processes the back input of the user
void processBackInput(char* window, Interactions*& inct, Coordinates*& cursorPosition);


//The functions processes the arrow keys input for the menu
void processUpMenu(char* window, Interactions*& inct, Coordinates*& cursorPosition);
void processDownMenu(char* window, Interactions*& inct, Coordinates*& cursorPosition);
void processLeftMenu(char* window, Interactions*& inct, Coordinates*& cursorPosition);
void processRightMenu(char* window, Interactions*& inct, Coordinates*& cursorPosition);


//The function processes the arrow keys input for the map
void arrowMapInput(char* window, char* map, Coordinates*& playerMapPosition, const std::string &input);

//The function processes the map interaction
void processMapInteraction(char* window, bool* mapActive, Coordinates*& cursorPosition, Interactions*& inct, int x, int y);


#endif