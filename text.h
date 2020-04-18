#ifndef TEXT_H
#define TEXT_H

#include "sdl_engine.h"

using namespace std;

class Text
{
public:
    void init(SDL_Renderer* renderer);
    void display(SDL_Renderer* renderer);
    void destroy();
private:
    TTF_Font *font = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *casual = NULL;
    SDL_Color color = {255,255,255};
    SDL_Rect casualRect;
};

#endif // TEXT_H
