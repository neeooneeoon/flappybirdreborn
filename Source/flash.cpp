#include "flash.h"

using namespace std;

void Flash::init(SDL_Renderer *renderer){
    loadSprites(surface, texture, renderer, path);
}

void Flash::display(SDL_Renderer* renderer){
    rect = {0,0,1280,720};
    unsigned char alpha;
    SDL_GetTextureAlphaMod(texture, &alpha);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for(int i=0; i<60; i++){
        SDL_SetTextureAlphaMod(texture, alpha);
        if(alpha>0) alpha -= 50;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1280/60);
    }
}

void Flash::destroy(){
    destroyObject(surface, texture);
}
