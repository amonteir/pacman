// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Quit();
    return 0;
}
