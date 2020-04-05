#include "bird.h"

using namespace std;

void Bird::init(SDL_Renderer* renderer)
{

    loadSprites(surface, texture, renderer, pathMid);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = (1280 - rect.w) /2;
    rect.y = (720 - rect.h) /2;
    rect.w = 34*2;
    rect.h = 24*2;
}

void Bird::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, center, flip);
}

void Bird::status(bool &close, SDL_Rect &baseRect1, SDL_Rect &baseRect2)
{
    if(hold>0)
    {
        hold--;
    }
    if(angle<90 && hold ==0)
    {
        angle+=7;
    }

    if(collisionCheck(rect, baseRect1)){
        close = true;
    }

    if(collisionCheck(rect, baseRect2)){
        close = true;
    }

    // bottom boundary check
    if (rect.y + rect.h > 720)
    {
        rect.y = 720 - rect.h;
        close = true;
    }

    // upper boundary check
    if (rect.y < 0)
    {
        rect.y = 0;
        close = true;
    }


}

void Bird::update()
{
    rect.y += (speed+velocity) / 200;
    velocity += 9.8*5;
}

void Bird::keyUpdate()
{
    rect.y -= speed / 7;
    velocity = 9.8;
    angle = -20;
    hold = 15;
}

void Bird::destroy()
{
    destroyObject(surface, texture);
}
