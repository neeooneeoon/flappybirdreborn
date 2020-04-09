#include "flash.h"

using namespace std;

void Flash::init(SDL_Renderer *renderer){
    surface = SDL_LoadBMP(path);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void Flash::display(SDL_Renderer* renderer){
    rect = {0,0,1280,720};
    //SDL_GetTextureAlphaMod(texture, &alpha);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for(int i=0; i<60; i++){
        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
    }
}

void Flash::displayAlphaNone(SDL_Renderer* renderer){
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Flash::destroy(){
    destroyObject(surface, texture);
}
