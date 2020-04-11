#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "sdl_engine.h";
#include <sstream>
#include <string>

using namespace std;

class Scoreboard{
public:
    void init(SDL_Renderer* renderer);
    void display(SDL_Renderer* renderer);
    void update(int score);
    void destroy();
    void getNum(char num);
private:
    char* path = "sprites\\scoresheet.png";
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect srcrect, dstrect;
    int anchor = 640; //step = 36; x
    stringstream ss;
    string scoreStr;
    bool updateScr = false;
};

#endif // SCOREBOARD_H
