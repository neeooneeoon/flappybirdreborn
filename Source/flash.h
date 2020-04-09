#ifndef FLASH_H
#define FLASH_H

#include "sdl_engine.h";

using namespace std;

class Flash{
public:
    void init(SDL_Renderer* renderer);
    void display(SDL_Renderer* renderer);
    void destroy();
private:
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = NULL;
    char* path = "sprites\\white.png";
    SDL_Rect rect;
};

#endif
