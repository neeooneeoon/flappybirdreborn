#ifndef SFX_H
#define SFX_H

#include "sdl_engine.h"

using namespace std;

class SFX{
public:
    void init();
    void playWing();
    void playSwoosh();
    void playPoint();
    void playHit();
    void playDie();
    void playCoin();
    void close();
private:
    Mix_Chunk* wing = NULL;
    Mix_Chunk* swoosh = NULL;
    Mix_Chunk* point = NULL;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* die = NULL;
    Mix_Chunk* coin = NULL;
};

#endif // SFX_H
