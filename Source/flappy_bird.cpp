#include "flappy_bird.h"

using namespace std;

void FlappyBird::game_loop()
{
    //bool keyCheck = false;
    while(!close)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                close = true;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_SPACE:
                    bird.keyUpdate();
                    break;
                default:
                    break;
                }
            }
        }
        collision();
        update(1280/60, close);
        display();
    }
}

void FlappyBird::init()
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    setDefaultBGColor(renderer);
    bird.init(renderer);
    background.init(renderer);
    base.init(renderer);
    pipeInit();
}

void FlappyBird::quit()
{
    bird.destroy();
    background.destroy();
    base.destroy();
    quitSDL(window, renderer);
}

void FlappyBird::update(double delta_time, bool &close)
{
    bird.update();
    bird.status(close);
    SDL_Delay(delta_time);
}

void FlappyBird::display()
{
    SDL_RenderClear(renderer);
    background.display(renderer, config.multiplier);
    base.display(renderer, config.multiplier);
    pipeGen();
    bird.display(renderer);
    SDL_RenderPresent(renderer);
}

void FlappyBird::collision(){
    if(collisionCheck(bird.dstrect, base.rect1)
       || collisionCheck(bird.dstrect, base.rect2))
    {
        close = true;
    }
}

void FlappyBird::pipeInit(){
    for(int i=0; i<6; i++){
        pipe[i].init(renderer, i*250);
    }

}

void FlappyBird::pipeGen(){
    for(int i=0; i<6; i++){
        if(pipe[i].dstrectDown.x<-60){
            pipe[i].destroy();
            pipe[i].init(renderer, 150);
        }
        pipe[i].display(renderer, config.multiplier);
    }
}

void FlappyBird::pipeDestroy(){
    for(int i=0; i<6; i++){
        pipe[i].destroy();
    }
}
