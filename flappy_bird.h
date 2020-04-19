#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H

#include <string>
#include <stdlib.h>
#include <time.h>
#include <cstdint>

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
#include "text.h"
#include "indicator.h"
#include "saves.h"

using namespace std;

class FlappyBird
{
public:
    void init();
    void quit();
    void reset();
    void menu();
    void getReady();
    void gameLoop();
    void gameOver();
    void display();
    void resInit();
    void resGen();
    void resDestroy();
    void nextLevel();
private:
    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 720;
    string WINDOW_TITLE = "Flappy Bird Reborn - Build 180420";

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    bool lose = false;
    bool gameQuit = false;
    bool realQuit = false;
    bool menuLoop = true;
    bool getReadyLoop = true;
    bool level2 = false;
    bool casual = false;

    int mouseX;
    int mouseY;

    int randNum;
    int delay = 60;

    Config config;
    Saves saves;

    Bird bird;
    Background background;
    Base base;
    SFX sfx;
    Flash flash;
    Message message;
    Text text;
    Indicator indicator;

    Pipe pipe[7];

    Coin coin[7];
    bool coinStatus[7];
    int coinRandom[7];

    Scoreboard scoreboard;
    int score = 0;
    bool scoreStatus[7];
};

#endif // FLAPPY_BIRD_H
