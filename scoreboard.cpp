#include "scoreboard.h"

using namespace std;

void Scoreboard::init(SDL_Renderer* renderer)
{
    loadSprites(surface, texture, renderer, path);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    ss.str("");
    ss << 0;
    scoreStr = ss.str();
}

void Scoreboard::getNum(char num)
{
    switch(num)
    {
    case '0':
        srcrect = {0,0,24,36};
        break;
    case '1':
        srcrect = {100,37,16,36};
        break;
    case '2':
        srcrect = {25,0,24,36};
        break;
    case '3':
        srcrect = {50,0,24,36};
        break;
    case '4':
        srcrect = {75,0,24,36};
        break;
    case '5':
        srcrect = {100,0,24,36};
        break;
    case '6':
        srcrect = {0,37,24,36};
        break;
    case '7':
        srcrect = {25,37,24,36};
        break;
    case '8':
        srcrect = {50,37,24,36};
        break;
    case '9':
        srcrect = {75,37,24,36};
        break;
    }
}

void Scoreboard::display(SDL_Renderer* renderer, int birdY, int scoreboardY)
{
    if(abs(birdY-scoreboardY<=50)){
        alphaVal = 100;
    }else{
        alphaVal = 255;
    }
    SDL_SetTextureAlphaMod(texture, alphaVal);
    anchor = 640 - 12*(scoreStr.length()-1);
    for(int i=0; i<scoreStr.length(); i++)
    {
        getNum(scoreStr[i]);
        if(scoreStr[i]=='1')
        {
            dstrect = {anchor, 120, 16, 36};
            anchor += 16 + 5;
        }
        else
        {
            dstrect = {anchor, 120, 24, 36};
            anchor += 24 + 5;
        }
        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
    }
}

void Scoreboard::update(int score)
{
    ss.str("");
    ss << score;
    scoreStr = ss.str();
}

void Scoreboard::destroy()
{
    SDL_DestroyTexture(texture);
}
