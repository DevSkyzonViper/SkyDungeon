#ifndef IPL_H
#define IPL_H

#include <iostream>
#include <cctype>
#include <string>
#include <termios.h>
#include <unistd.h>

#include "PSL.h"
#include "TRL.h"



//Struct for the terminal thingy (ChatGPT)
extern struct termios orig_termios;

//Terminal reset (ChatGPT)
void resetTerminal();

//Dynamic input processing (ChatGPT)
void enableRawMode();





//----------------------------------------------------------------------------------------//
//                            Input that is for the menu and map                          //
//----------------------------------------------------------------------------------------//


//The function processes the enter input of the user
//for selecting something or opening it
bool processEnterInput();


//The function processes the back input of the user
//for returning or deleting a character input
void processBackInput();





//----------------------------------------------------------------------------------------//
//                         Input that is specifically for the menu                        //
//----------------------------------------------------------------------------------------//


//Processes if there is an option over the current one
//and switches to it, if possible
void processUpInputForMenu();


//Processes if there is an option under the current one
//and switches to it, if possible
void processDownInputForMenu();


//Processes if there is an option left the current one
//and switches to it, if possible
void processLeftInputForMenu();


//Processes if there is an option right the current one
//and switches to it, if possible
void processRightInputForMenu();


//The function processes the arrow keys input for the menu
//to choose the corresponding menu item (ChatGPT)
void processArrowKeyInputForMenu();


//The function processes the general inputs of the user
//such as numbers, characters, and special characters
//specifically for the menu
void processNormalInputForMenu(std::string input);





//----------------------------------------------------------------------------------------//
//                          Input that is specifically for the map                        //
//----------------------------------------------------------------------------------------//


//The function checks, if the place to move the player
//is walkable, and moves the player. If the player moved
//it also checks for interactions that happen on walk
void processMoveInputForMap(std::string input);


//The function processes the arrow keys input for the map
//to move the player in the corresponding direction (ChatGPT)
void processArrowKeyInputForMap();


//The function processes the general inputs of the user
//such as numbers, characters, and special characters
//specifically for the map
void processNormalInputForMap(std::string input);





//----------------------------------------------------------------------------------------//
//                               General game input to process                            //
//----------------------------------------------------------------------------------------//


//The function processes the users general game input
//to select the next thing that should happen (ChatGPT)
bool processGameInput();





#endif