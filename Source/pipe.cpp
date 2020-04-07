#include "pipe.h"

using namespace std;

void Pipe::getRandomLength(){
    length = rand() %280+30;
}

void Pipe::init(SDL_Renderer* renderer, int pos){
    loadSprites(surface, texture, renderer, greenPath);
    getRandomLength();
    srcrectDown = {0,0,52,length};
    dstrectDown = {1280+pos, 590-length, 52, length};
    srcrectUp = {0,0, 52, 600-length-140};
    dstrectUp = {1280+pos, 0, 52, 600-length-140};
}

void Pipe::display(SDL_Renderer* renderer, int multiplier){
    SDL_RenderCopy(renderer, texture, &srcrectDown, &dstrectDown);
    SDL_RenderCopyEx(renderer, texture, &srcrectUp, &dstrectUp,
                     upAngle, center, flip);
    dstrectDown.x -= 6 * multiplier;
    dstrectUp.x -= 6 * multiplier;
}

void Pipe::destroy(){
    destroyObject(surface, texture);
}
