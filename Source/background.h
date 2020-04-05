#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "sdl_engine.h"

class Background{
public:
    void init(SDL_Renderer* renderer);
    void display(SDL_Renderer* renderer);
    void destroy();
private:
    char* path = "sprites\\background.png";
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Rect rect1;
    SDL_Rect rect2;
};

#endif // BACKGROUND_H
