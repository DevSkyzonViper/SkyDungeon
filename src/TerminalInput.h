#ifndef TERMINAL_INPUT_H
#define TERMINAL_INPUT_H


//==================================================================================
// INCLUDES OF GENERAL LIBRARIES
//==================================================================================
#include <iostream>
#include <cctype>
#include <string>
#include <termios.h>
#include <unistd.h>



//==================================================================================
// INCLUDES OF MY OWN LIBRARIES
//==================================================================================
#include "GameScenesLib.h"



//==================================================================================
// STRUCT DEFINITIONS
//==================================================================================
extern struct termios orig_termios;



//==================================================================================
// TERMIOS TERMINAL SETTINGS FUNCTIONS
//==================================================================================

// Terminal reset
void resetTerminal();

// Dynamic input processing
void enableRawMode();



//==================================================================================
// INPUT PROCESSING: GENERAL
//==================================================================================

// The function processes the users general game input
// to select the next thing that should happen
bool processGameInput();

// The function processes the enter input of the user
// for selecting something or opening it
bool processEnterInput();

// The function processes the users general game input
// to select the next thing that should happen
// The function processes the back input of the user
// for returning or deleting a character input
void processBackInput();



//==================================================================================
// INPUT PROCESSING: MENU
//==================================================================================

// Processes if there is an option over the current one
// and switches to it, if possible
void processUpInputForMenu();

// Processes if there is an option under the current one
// and switches to it, if possible
void processDownInputForMenu();

// Processes if there is an option left the current one
// and switches to it, if possible
void processLeftInputForMenu();

// Processes if there is an option right the current one
// and switches to it, if possible
void processRightInputForMenu();

// The function processes the arrow keys input for the menu
// to choose the corresponding menu item
void processArrowKeyInputForMenu();

// The function processes the general inputs of the user
// such as numbers, characters, and special characters
// specifically for the menu
void processNormalInputForMenu(std::string input);





//==================================================================================
// INPUT PROCESSING: MAP
//==================================================================================

// The function checks, if the place to move the player
// is walkable, and moves the player. If the player moved
// it also checks for interactions that happen on walk
void processMoveInputForMap(std::string input);

// The function processes the arrow keys input for the map
// to move the player in the corresponding direction
void processArrowKeyInputForMap();

// The function processes the general inputs of the user
// such as numbers, characters, and special characters
// specifically for the map
void processNormalInputForMap(std::string input);



#endif //TERMINAL_INPUT_H