#ifndef COIN_H
#define COIN_H

#include <stdlib.h>
#include <time.h>

#include "sdl_engine.h"

using namespace std;

class Coin{
public:
    void loadPNG(SDL_Renderer* renderer);
    void init(SDL_Renderer* renderer, int pos);
    void display(SDL_Renderer* renderer, int multiplier);
    void destroy();
private:
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;
    char* path = "sprites\\coin.png";
};

#endif // COIN_H
