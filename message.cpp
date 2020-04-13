#include "message.h"

using namespace std;


void Message::init(SDL_Renderer* renderer)
{
    loadSprites(surface, texture, renderer, path);
}

void Message::display(SDL_Renderer* renderer)
{
    srcrect = {0,51,178,48};
    dstrect = {480, 80, 178*2, 48*2};
    SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);

    if(readyBlink == true && blinkDelay>0)
    {
        srcrect = {0,100,114,60};
        dstrect = {595, 485, 114, 60};
        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        srcrect = {0,0,184,50};
        dstrect = {565, 185, 184, 50};
        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        blinkDelay--;
    }

    if(readyBlink == false && blinkDelay>0){
        blinkDelay--;
    }

    if(blinkDelay==0 && readyBlink==true)
    {
        readyBlink = false;
        blinkDelay = 20;
    }
    else if(blinkDelay==0 && readyBlink==false)
    {
        readyBlink = true;
        blinkDelay = 20;
    }
}

void Message::destroy()
{
    destroyObject(surface, texture);
}
