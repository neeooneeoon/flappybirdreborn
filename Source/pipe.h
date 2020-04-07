#ifndef PIPE_H
#define PIPE_H

#include "sdl_engine.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

class Pipe{
public:
    SDL_Rect dstrectUp;
    SDL_Rect dstrectDown;
    void getRandomLength();
    void init(SDL_Renderer* renderer, int pos);
    void display(SDL_Renderer* renderer, int multiplier);
    void destroy();
private:
    char* greenPath = "sprites\\greenPipe.png";
    char* redPath = "sprites\\redPipe.png";
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect srcrectUp;
    SDL_Rect srcrectDown;
    int length = 50; //max 320
    int upAngle = 180;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
};

#endif // PIPE_H
