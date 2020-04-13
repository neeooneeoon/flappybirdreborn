#include "coin.h"

using namespace std;

void Coin::loadPNG(SDL_Renderer* renderer){
    loadSprites(surface, texture, renderer, path);
}

void Coin::init(SDL_Renderer* renderer, int pos){
    rect = {1420+pos, 400, 25, 25};
}

void Coin::display(SDL_Renderer* renderer, int multiplier){
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    rect.x -= 4 * multiplier;
}

void Coin::destroy(){
    destroyObject(surface, texture);
}
