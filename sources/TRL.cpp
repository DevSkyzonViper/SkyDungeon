#include "TRL.hpp"
#include <iostream>

//The function makes a border in the window
void makeBorder(char* window)
{
    const int width = 110;
    const int height = 28;

    for(int j = 0; j < height; j++)
    {
        if(j == 0 || j == height - 1)
        {
            for(int i = 0; i < width; i++)
                window[j * width + i] = '#';
        }
        else
        {
            window[j * width] = '#';
            window[j * width + width - 1] = '#';
        }
    }
}

//The function draws a box onto the given position, with the given size
void drawBox(char* window, int x, int y, int boxWidth, int boxHeight)
{
    const int width = 110;   // Fensterbreite
    const int height = 28;   // Fensterhöhe

    // Sicherheitscheck
    if(x < 0 || y < 0 || x >= width || y >= height)
    {
        return;
    }
    for(int j = 0; j < boxHeight; j++)
    {
        int posY = y + j;
        if(posY >= height)
        {
            break; // nicht über Fenster hinaus
        }
        for(int i = 0; i < boxWidth; i++)
        {
            int posX = x + i;
            if(posX >= width)
            {
                break;
            }
            if(j == 0 || j == boxHeight - 1 || i == 0 || i == boxWidth - 1)
            {
                window[posY * width + posX] = '#';
            }
        }
    }
}

//The function clears the inside of a box (without the edges)
void clearBox(char* window, int x, int y, int boxWidth, int boxHeight)
{
    const int width = 110;   // Fensterbreite
    const int height = 28;   // Fensterhöhe

    // Sicherheitscheck: sinnvolle Box-Größe
    if (boxWidth <= 2 || boxHeight <= 2) return;

    for (int j = 1; j < boxHeight - 1; ++j)
    {
        int posY = y + j;
        if (posY < 0 || posY >= height) continue;
        for (int i = 1; i < boxWidth - 1; ++i)
        {
            int posX = x + i;
            if (posX < 0 || posX >= width) continue;

            window[posY * width + posX] = ' ';
        }
    }
}



//The function clears the Window Array, to reuse
void clearWindow(char* window)
{
    for(int i = 0; i < 3080; i++)
    {
        window[i] = ' ';
    }
}

//The function writes the given text into a position onto the window
void writeIntoWindow(char* window, int x, int y, const std::string& text)
{
    const int width = 110;
    const int height = 28;

    if(y < 0 || y >= height)
    {
        return;
    }
    for(size_t i = 0; i < text.size(); i++)
    {
        int posX = x + i;
        if(posX >= 0 && posX < width)
        {
            window[y * width + posX] = text[i];
        }
    }
}

//The function draws the window onto the terminal screen
void drawWindow(char* window)
{
    std::system("clear");

    for(int j = 0; j < 28; j++)
    {
        for(int i = 0; i < 110; i++)
        {
            std::cout << window[i + (j * 110)];
        }
        std::cout << std::endl;
    }
}



//The function clears the Map Array, to reuse
void clearMap(char* map)
{
    for(int i = 0; i < 2160; i++)
    {
        map[i] = ' ';
    }
}

//The function draws the current map into the window
void drawMapIntoWindow(char* window, char* map)
{
    for(int j = 1; j < 21; j++)
    {
        for(int i = 1; i < 109; i++)
        {
            window[i + (j * 110)] = map[i - 1 + ((j - 1) * 108)];
        }
    }
}
