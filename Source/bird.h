#ifndef BIRD_H
#define BIRD_H

#include "sdl_engine.h"


using namespace std;

class Bird
{
public:
    void init(SDL_Renderer* renderer);
    void draw(SDL_Renderer* renderer);
    void update();
    void keyUpdate();
    void status(bool &close, SDL_Rect &baseRect1, SDL_Rect &baseRect2);
    void destroy();
private:
    char* pathUp = "sprites\\yellowbird-upflap.png";
    char* pathMid = "sprites\\yellowbird-midflap.png";
    char* pathDown = "sprites\\yellowbird-downflap.png";
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = NULL;
    SDL_Rect rect;
    int speed = 500;
    int velocity = 0;
    double angle = 0;
    int hold = 0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
};

#endif // BIRD_H
