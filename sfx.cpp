#include "sfx.h"

void SFX::init(){
    wing = Mix_LoadWAV("sounds\\wing.wav");
    swoosh = Mix_LoadWAV("sounds\\swoosh.wav");
    point = Mix_LoadWAV("sounds\\point.wav");
    hit = Mix_LoadWAV("sounds\\hit.wav");
    die = Mix_LoadWAV("sounds\\die.wav");
    coin = Mix_LoadWAV("sounds\\coin.wav");
    levelUp = Mix_LoadWAV("sounds\\levelup.wav");
}

void SFX::playWing(){
    Mix_PlayChannel(-1,wing,0);
}

void SFX::playSwoosh(){
    Mix_PlayChannel(-1,swoosh,0);
}

void SFX::playPoint(){
    Mix_PlayChannel(-1,point,0);
}

void SFX::playHit(){
    Mix_PlayChannel(-1,hit,0);
}

void SFX::playDie(){
    Mix_PlayChannel(-1,die,0);
}

void SFX::playCoin(){
    Mix_PlayChannel(-1, coin,0);
}

void SFX::playLevelUp(){
    Mix_PlayChannel(-1, levelUp, 0);
}

void SFX::close(){
    Mix_CloseAudio();
}
