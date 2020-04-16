#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H

#include <string>
#include <stdlib.h>
#include <time.h>

#include "sdl_engine.h"
#include "bird.h"
#include "background.h"
#include "base.h"
#include "pipe.h"
#include "scoreboard.h"
#include "sfx.h"
#include "flash.h"
#include "message.h"
#include "coin.h"

using namespace std;

class FlappyBird
{
public:
    void init();
    void quit();
    void getReady();
    void game_loop();
    void game_over();
    void display();
    void resInit();
    void resGen();
    void resDestroy();
    void baseCollision();
    void nextLevel();
private:
    bool lose = false;
    bool gameQuit = false;

    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 720;
    string WINDOW_TITLE = "Flappy Bird SDL - Build 160420";

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    Config config;

    Bird bird;
    Background background;
    Base base;
    SFX sfx;
    Flash flash;
    Message message;

    Pipe pipe[6];

    Coin coin[6];
    bool coinStatus[6];
    int coinRandom[6];

    Scoreboard scoreboard;
    int score = 0;
    int highscore = 0;
    bool scoreStatus[6];

    int delay = 60;
    int randNum;

    int mouseX;
    int mouseY;
};

#endif // FLAPPY_BIRD_H
