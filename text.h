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

    SDL_Rect casualRect;
    SDL_Rect pvpRect;
    SDL_Rect dinosaurRect;
    SDL_Rect quitRect;
private:
    TTF_Font *font = NULL;
    SDL_Color color = {255,255,255};
    SDL_Surface *surface = NULL;
    SDL_Texture *casual = NULL;
    SDL_Texture *pvp = NULL;
    SDL_Texture *dinosaur = NULL;
    SDL_Texture *quit = NULL;
};

#endif // TEXT_H
