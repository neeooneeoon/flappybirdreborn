#ifndef DINOSAUR_H
#define DINOSAUR_H

#include <string>
#include <stdlib.h>
#include <time.h>

#include "sdl_engine.h"
#include "bird.h"
#include "background.h"
#include "base.h"
#include "pipe.h"
#include "scoreboard.h"
#include "message.h"
#include "coin.h"
#include "sfx.h"
#include "flash.h"

using namespace std;

class Dinosaur
{
public:
    void init();
    void quit();
    void getReady();
    void gameLoop();
    void gameOver();
    void display();
    void resInit();
    void resGen();
    void resDestroy();
private:
    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 720;
    string WINDOW_TITLE = "Flappy Bird SDL - Build 170420";

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    bool lose = false;
    bool gameQuit = false;
    bool menuLoop = true;

    int mouseX;
    int mouseY;

    int randNum;
    int delay = 60;

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
};

#endif // DINOSAUR_H
