#include "bird.h"

using namespace std;

void Bird::init(SDL_Renderer* renderer)
{

    loadSprites(surface, texture, renderer, path);
    SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
    srcrect = {0,25,34,24};
    dstrect.w = 34*2;
    dstrect.h = 24*2;
    dstrect = {(1280 - dstrect.w) /2, (720 - dstrect.h) /2, 34*2, 24*2};
}

void Bird::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, angle, center, flip);
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

    if(collisionCheck(dstrect, baseRect1)){
        close = true;
    }

    if(collisionCheck(dstrect, baseRect2)){
        close = true;
    }

    // bottom boundary check
    if (dstrect.y + dstrect.h > 720)
    {
        dstrect.y = 720 - dstrect.h;
        close = true;
    }

    // upper boundary check
    if (dstrect.y < 0)
    {
        dstrect.y = 0;
        close = true;
    }


}

void Bird::update()
{
    dstrect.y += (speed+velocity) / 200;
    velocity += 9.8*5;
}

void Bird::keyUpdate()
{
    dstrect.y -= speed / 7;
    velocity = 9.8;
    angle = -20;
    hold = 15;
}

void Bird::destroy()
{
    destroyObject(surface, texture);
}
