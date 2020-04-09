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
#include "scoreboard.h"
#include "sfx.h"

using namespace std;

class FlappyBird
{
public:
    void game_loop();
    void game_over();
    void update(double delta_time, bool &close);
    void display();
    void init();
    void quit();
    void collision();
    void pipeInit();
    void pipeGen();
    void pipeDestroy();
    void nextLevel();
private:
    bool lose = false;

    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 720;
    string WINDOW_TITLE = "Flappy Bird SDL - Build 090420";

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    Bird bird;
    Background background;
    Base base;
    SFX sfx;

    Config config;

    Pipe pipe[6];
    bool scoreStatus[6];

    Scoreboard scoreboard;
    int score = 0;
    int highscore = 0;
};

#endif // FLAPPY_BIRD_H
