#include "flappy_bird.h"

using namespace std;

void FlappyBird::init()
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    setDefaultBGColor(renderer);
    bird.init(renderer);
    background.init(renderer);
    base.init(renderer);
    scoreboard.init(renderer);
    scoreboard.update(0);
    sfx.init();
    pipeInit();
    message.init(renderer);
    flash.init(renderer);
}

void FlappyBird::quit()
{
    bird.destroy();
    background.destroy();
    base.destroy();
    pipeDestroy();
    scoreboard.destroy();
    sfx.close();
    flash.destroy();
    message.destroy();
    quitSDL(window, renderer);
}

void FlappyBird::menu()
{
    bool menuLoop = true;
    while(menuLoop == true)
    {
        while(SDL_PollEvent(&event))
        {

            switch(event.type)
            {
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                cout << mouseX << " " << mouseY << endl;
                break;
            case SDL_QUIT:
                lose = true;
                menuLoop = false;
                gameQuit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    bird.update();
                    bird.keyUpdate();
                    menuLoop = false;
                    break;
                default:
                    break;
                }
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_SPACE:
                case SDL_BUTTON_LEFT:
                    bird.update();
                    bird.keyUpdate();
                    menuLoop = false;
                    break;
                default:
                    break;
                }
            }
        }
        background.display(renderer, config.multiplier);
        base.display(renderer, config.multiplier);
        bird.display(renderer);
        bird.aniUpdate();
        message.display(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(1280/60);
    }
    game_loop();
}

void FlappyBird::game_loop()
{
    while(!lose)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                cout << mouseX << " " << mouseY << endl;
                break;
            case SDL_QUIT:
                lose = true;
                gameQuit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    bird.keyUpdate();
                    sfx.playWing();
                    break;
                default:
                    break;
                }
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_SPACE:
                    bird.keyUpdate();
                    sfx.playWing();
                    break;
                default:
                    break;
                }
            }
        }
        nextLevel();
        collision();
        update(1280/60, lose);
        display();
    }
    if(gameQuit == false)
    {
        game_over();
    }
}

void FlappyBird::game_over()
{
    config.multiplier = 0;
    sfx.playHit();
    sfx.playDie();
    flash.display(renderer);
    while(bird.dstrect.y<1000)
    {
        update(1280/60, lose);
        SDL_RenderClear(renderer);
        background.display(renderer, config.multiplier);
        base.display(renderer, config.multiplier);
        pipeGen();
        bird.display(renderer);
        if(flash.alpha>0)
            flash.alpha-=10;
        flash.displayAlphaNone(renderer);
        SDL_RenderPresent(renderer);
    }
}

void FlappyBird::update(double delta_time, bool &close)
{
    bird.update();
    bird.aniUpdate();
    bird.status(lose);
    SDL_Delay(delta_time);
}

void FlappyBird::display()
{
    SDL_RenderClear(renderer);
    background.display(renderer, config.multiplier);
    base.display(renderer, config.multiplier);
    pipeGen();
    bird.display(renderer);
    scoreboard.display(renderer);
    SDL_RenderPresent(renderer);
}

void FlappyBird::collision()
{
    if(collisionCheck(bird.dstrect, base.rect1)
            || collisionCheck(bird.dstrect, base.rect2))
    {
        lose = true;
    }
}

void FlappyBird::pipeInit()
{
    randNum = rand() % 2;
    for(int i=0; i<6; i++)
    {
        if(randNum == 0)
            pipe[i].loadGreen(renderer);
        else
            pipe[i].loadRed(renderer);
        pipe[i].init(renderer, i*250);
        scoreStatus[i]=false;
    }
}

void FlappyBird::pipeGen()
{
    if(delay>0)
    {
        delay--;
    }
    if(delay==0)
    {
        for(int i=0; i<6; i++)
        {
            if(pipe[i].dstrectDown.x<-60)
            {
                pipe[i].destroy();
                pipe[i].init(renderer, 150);
                if(randNum == 0)
                    pipe[i].loadGreen(renderer);
                else
                    pipe[i].loadRed(renderer);
                scoreStatus[i] = false;
            }
            if(collisionCheck(bird.dstrect, pipe[i].dstrectUp)
                    || collisionCheck(bird.dstrect, pipe[i].dstrectDown))
            {
                lose = true;
            }
            if(bird.dstrect.x > pipe[i].dstrectUp.x && scoreStatus[i]==false)
            {
                sfx.playPoint();
                score++;
                scoreStatus[i] = true;
                scoreboard.update(score);
            }
            pipe[i].display(renderer, config.multiplier);
        }
    }

}

void FlappyBird::pipeDestroy()
{
    for(int i=0; i<6; i++)
    {
        pipe[i].destroy();
    }
}

void FlappyBird::nextLevel()
{
    if(score==20)
    {
        config.multiplier = 2;
    }
}
