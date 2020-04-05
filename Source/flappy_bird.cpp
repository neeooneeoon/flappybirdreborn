#include "flappy_bird.h"

using namespace std;

void FlappyBird::game_loop()
{
    bool close = false;
    bool keyCheck = false;
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
}

void FlappyBird::quit()
{
    bird.destroy();
    background.destroy();
    quitSDL(window, renderer);
}

void FlappyBird::update(double delta_time, bool &close)
{
    bird.update();
    bird.status(close, base.rect1, base.rect2);
    SDL_Delay(delta_time);
}

void FlappyBird::display()
{
    SDL_RenderClear(renderer);
    background.display(renderer);
    base.display(renderer);
    bird.draw(renderer);
    SDL_RenderPresent(renderer);
}
