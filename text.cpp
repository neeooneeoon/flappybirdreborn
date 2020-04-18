#include "text.h"

using namespace std;

void Text::init(SDL_Renderer* renderer)
{
    font = TTF_OpenFont("font\\minecraft.ttf", 20);

    surface = TTF_RenderText_Solid(font, "Casual", color);
    casual = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(casual,NULL,NULL, &casualRect.w, &casualRect.h);
    casualRect.x = 1182;
    casualRect.y = 75;

    surface = TTF_RenderText_Solid(font, "PvP", color);
    pvp = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(pvp, NULL, NULL, &pvpRect.w, &pvpRect.h);
    pvpRect.x = 1205;
    pvpRect.y = 95;

    surface = TTF_RenderText_Solid(font, "Dinosaur", color);
    dinosaur = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(dinosaur, NULL, NULL, &dinosaurRect.w, &dinosaurRect.h);
    dinosaurRect.x = 1165;
    dinosaurRect.y = 115;

    surface = TTF_RenderText_Solid(font, "Quit", color);
    quit = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(quit, NULL, NULL, &quitRect.w, &quitRect.h);
    quitRect.x = 1210;
    quitRect.y = 135;
}

void Text::display(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, casual, NULL, &casualRect);
    SDL_RenderCopy(renderer, pvp, NULL, &pvpRect);
    SDL_RenderCopy(renderer, dinosaur, NULL, &dinosaurRect);
    SDL_RenderCopy(renderer, quit, NULL, &quitRect);
}

void Text::destroy()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(casual);
}
