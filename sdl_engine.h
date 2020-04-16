#ifndef SDL_CONTROL_H
#define SDL_CONTROL_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_TTF.h>
#include <SDL_mixer.h>

using namespace std;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT, const string &WINDOW_TITLE);
void quitSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void loadSprites(SDL_Surface* &surface, SDL_Texture* &texture, SDL_Renderer* &renderer, char* path);
bool collisionCheck(SDL_Rect &rect1, SDL_Rect &rect2);
void framerateControl(int &frameNum); //frameNum init at 1 and range from 1 -> 3


#endif
