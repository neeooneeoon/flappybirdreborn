#include "background.h"

using namespace std;

void Background::select(){
    srand(time(NULL));
    int selection = rand() %2 +1;
    if(selection ==1) path = "sprites\\dayBackground.png";
    else if(selection == 2) path = "sprites\\nightBackground.png";
}

void Background::init(SDL_Renderer* renderer){
    select();
    loadSprites(surface, texture, renderer, path);
    rect1.x = 0;
    rect1.y = -120;
    rect1.w = 1280;
    rect1.h = 720;
    rect2.x = 1280;
    rect2.y = -120;
    rect2.w = 1280;
    rect2.h = 720;
}

void Background::display(SDL_Renderer* renderer, int multiplier){
    SDL_RenderCopy(renderer, texture, NULL, &rect1);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
    rect1.x -= 6 * multiplier;
    rect2.x -= 6 * multiplier;
    if(rect1.x<-1280 + 6) rect1.x = 1280 - 6 * multiplier;
    if(rect2.x<-1280 + 6) rect2.x = 1280 - 6 * multiplier;
}

void Background::destroy(){
    destroyObject(surface, texture);
}
