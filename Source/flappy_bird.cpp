#include "flappy_bird.h"

using namespace std;

void FlappyBird::game_loop()
{
    bool keyCheck = false;
    while(!close)
    {
        collision();
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
    pipe.init(renderer);
}

void FlappyBird::quit()
{
    bird.destroy();
    background.destroy();
    base.destroy();
    pipe.destroy();
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
    pipe.display(renderer, config.multiplier);
    bird.display(renderer);
    SDL_RenderPresent(renderer);
}

void FlappyBird::collision(){
    if(collisionCheck(bird.dstrect, base.rect1)
       || collisionCheck(bird.dstrect, base.rect2)
       || collisionCheck(bird.dstrect, pipe.dstrectUp)
       || collisionCheck(bird.dstrect, pipe.dstrectDown))
    {
        close = true;
    }
}
