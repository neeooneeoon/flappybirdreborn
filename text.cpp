#include "text.h"

using namespace std;

void Text::init(SDL_Renderer* renderer)
{
    font = TTF_OpenFont("font\\minecraft.ttf", 20);

    surface = TTF_RenderText_Solid(font, "Casual", color);
    casual = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(casual,NULL,NULL, &casualRect.w, &casualRect.h);
    casualRect.x = 1182;
    casualRect.y = 75;
    SDL_FreeSurface(surface);
}

void Text::display(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, casual, NULL, &casualRect);
}

void Text::destroy()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(casual);
}
