#include "flash.h"

using namespace std;

void Flash::init(SDL_Renderer *renderer){
    loadSprites(surface, texture, renderer, path);
}

void Flash::display(SDL_Renderer* renderer){
    rect = {0,0,1280,720};
    //SDL_GetTextureAlphaMod(texture, &alpha);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for(int i=0; i<20; i++){
        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
    }
}

void Flash::displayNoAlpha(SDL_Renderer* renderer){
    if(alpha>0) alpha-=10;
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Flash::destroy(){
    SDL_DestroyTexture(texture);
}
