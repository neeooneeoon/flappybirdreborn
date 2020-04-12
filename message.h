#ifndef MESSAGE_H
#define MESSAGE_H

#include "sdl_engine.h"

using namespace std;

class Message{
public:
    void init(SDL_Renderer* renderer);
    void display(SDL_Renderer* renderer);
    void destroy();
private:
    char* path = "sprites\\menu_message.png";
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect srcrect;
    SDL_Rect dstrect;

    bool readyBlink = true;
    int blinkDelay = 20;
};

#endif // MESSAGE_H
