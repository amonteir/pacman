// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Screen.h"
#include "Logging.h"
#include "Timer.h"
#include <string>

using namespace angelogames;

int main(int argc, char* args[])
{
    Logging* log = new Logging("main.log");
    Screen* screen = new Screen();
    log->write("Pacman game is starting.");

    //Main game loop flag
    bool quit = false;

    //The frames per second timer
    Timer fps_timer;

    //Event handler
    SDL_Event e;

    //Start counting frames per second
    int countedFrames = 0;
    fps_timer.start();

    while (!quit) {

        /////////////
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {

            //User requests quit
            if (e.type == SDL_QUIT) {
                //screen->playSound("QUIT");
                //SDL_Delay(2000);
                quit = true;
            }
            else {
                screen->EventHandler(e);
            }
        }

        //Calculate and correct fps
        float avg_fps = countedFrames / (fps_timer.getTicks() / 1000.f);
        if (avg_fps > 2000000)
        {
            avg_fps = 0;
        }
        std::string fps_msg = "FPS = " + std::to_string(avg_fps);
        //log->write(fps_msg);

        /////////////
        // Move objects
        screen->MoveObjects();

        /////////////
        // Render objects
        screen->RenderObjects();

        /////////////
        // Update screen
        screen->UpdateScreen();

        ++countedFrames;

    }

    screen->Close();

    delete log;
    delete screen;

    return 0;
}
