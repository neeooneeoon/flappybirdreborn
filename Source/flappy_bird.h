#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H

#include <SDL_image.h>
#include <SDL.h>
#include <string>

#include "sdl_engine.h"
#include "bird.h"
#include "background.h"
#include "base.h"
#include "pipe.h"

using namespace std;

class FlappyBird
{
public:
    void game_loop();
    void update(double delta_time, bool &close);
    void display();
    void init();
    void quit();
    void collision();
private:
    bool close = false;

    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 720;
    string WINDOW_TITLE = "Flappy Bird SDL - Build 050420";

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    Bird bird;
    Background background;
    Base base;

    Config config;
    Pipe pipe;
};

#endif // FLAPPY_BIRD_H
