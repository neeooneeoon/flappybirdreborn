#include "sfx.h"

void SFX::init(){
    wing = Mix_LoadWAV("wav\\wing.wav");
    swoosh = Mix_LoadWAV("wav\\swoosh.wav");
    point = Mix_LoadWAV("wav\\point.wav");
    hit = Mix_LoadWAV("wav\\hit.wav");
    die = Mix_LoadWAV("wav\\die.wav");
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

void SFX::close(){
    Mix_CloseAudio();
}
