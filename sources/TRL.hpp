#ifndef TRL_HPP
#define TRL_HPP

#include <string>

struct Color {
    std::string name;
    std::string value;
};

// Foreground (text) colors
inline Color fgColorMap[] = {
    {"default", "\033[0m"},
    {"black", "\033[30m"},
    {"red", "\033[31m"},
    {"green", "\033[32m"},
    {"yellow", "\033[33m"},
    {"blue", "\033[34m"},
    {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},
    {"white", "\033[37m"},
    {"bright_black", "\033[90m"},
    {"bright_red", "\033[91m"},
    {"bright_green", "\033[92m"},
    {"bright_yellow", "\033[93m"},
    {"bright_blue", "\033[94m"},
    {"bright_magenta", "\033[95m"},
    {"bright_cyan", "\033[96m"},
    {"bright_white", "\033[97m"}
};

// Background colors
inline Color bgColorMap[] = {
    {"default", "\033[0m"},
    {"black", "\033[40m"},
    {"red", "\033[41m"},
    {"green", "\033[42m"},
    {"yellow", "\033[43m"},
    {"blue", "\033[44m"},
    {"magenta", "\033[45m"},
    {"cyan", "\033[46m"},
    {"white", "\033[47m"},
    {"bright_black", "\033[100m"},
    {"bright_red", "\033[101m"},
    {"bright_green", "\033[102m"},
    {"bright_yellow", "\033[103m"},
    {"bright_blue", "\033[104m"},
    {"bright_magenta", "\033[105m"},
    {"bright_cyan", "\033[106m"},
    {"bright_white", "\033[107m"}
};


//Lookup function for the Colors
inline std::string getTextColor(const std::string& name)
{
    for (int i = 0; i < 17; i++)
    {
        if (fgColorMap[i].name == name)
        {
            return fgColorMap[i].value;
        }
    }
    return "\033[0m"; //Default
}
inline std::string getBackColor(const std::string& name)
{
    for (int i = 0; i < 17; i++)
    {
        if (bgColorMap[i].name == name)
        {
            return bgColorMap[i].value;
        }
    }
    return "\033[0m"; //Default
}



//The function makes a border in the window
void makeBorder(char* window);

//The function draws a box onto the given position, with the given size
void drawBox(char* window, int x, int y, int boxWidth, int boxHeight);

//The function clears the inside of a box (without the edges)
void clearBox(char* window, int x, int y, int boxWidth, int boxHeight);



//The function clears the Window Array, to reuse
void clearWindow(char* window);

//The function writes the given text into a position onto the window
void writeIntoWindow(char* window, int x, int y, const std::string& text);

//The function draws the window onto the terminal screen
void drawWindow(char* window);



//The function clears the Map Array, to reuse
void clearMap(char* map);

//The function draws the current map into the window
void drawMapIntoWindow(char* window, char* map);


#endif