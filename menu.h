#ifndef MENU_H
#define MENU_H

#include "sdl_engine.h"

using namespace std;

class Menu{
public:
    void init(SDL_Renderer* renderer);
    void display(SDL_Renderer* renderer);
    void destroy();
private:

};

#endif // MENU_H
