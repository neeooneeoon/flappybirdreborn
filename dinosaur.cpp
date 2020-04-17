#include "dinosaur.h"

using namespace std;

void Dinosaur::init()
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    bird.loadPNG(renderer);
    bird.initCasual();
    background.init(renderer);
    base.init(renderer);
    message.init(renderer);
    flash.init(renderer);
    sfx.init();
    scoreboard.init(renderer);
    resInit();
}

void Dinosaur::quit()
{
    bird.destroy();
    background.destroy();
    base.destroy();
    resDestroy();
    flash.destroy();
    message.destroy();
    sfx.close();
    quitSDL(window, renderer);
}

void Dinosaur::getReady()
{
    while(menuLoop == true)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
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
        framerateControl(config.frameNum);
    }
    gameLoop();
}

void Dinosaur::gameLoop()
{
    while(!lose)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
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
        bird.aniUpdate();
        bird.status(lose);
        //nextLevel();
        bird.collideBase(base.rect1, base.rect2, lose);
        framerateControl(config.frameNum);
        display();
    }
    if(gameQuit == false)
    {
        gameOver();
    }
}

void Dinosaur::gameOver()
{
    config.multiplier = 0;
    sfx.playHit();
    flash.display(renderer);
    sfx.playDie();
    while(bird.dstrect.y<1000)
    {
        SDL_RenderClear(renderer);

        background.display(renderer, config.multiplier);
        base.display(renderer, config.multiplier);
        resGen();
        bird.update();
        bird.status(lose);
        bird.display(renderer);
        flash.displayNoAlpha(renderer);

        framerateControl(config.frameNum);
        SDL_RenderPresent(renderer);
    }
}

void Dinosaur::display()
{
    SDL_RenderClear(renderer);

    background.display(renderer, config.multiplier);
    base.display(renderer, config.multiplier);
    resGen();
    bird.display(renderer);
    scoreboard.display(renderer, bird.dstrect.y);

    SDL_RenderPresent(renderer);
}

void Dinosaur::resInit()
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

        coin[i].loadPNG(renderer);
        coin[i].init(renderer, i*250);
        coinStatus[i]=true;
        coinRandom[i] = rand() % 2;
    }
}

void Dinosaur::resGen()
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
                pipe[i].init(renderer, 150);
                scoreStatus[i] = false;
            }
            if(coin[i].dstrect.x<-60)
            {
                coin[i].init(renderer, 10);
                coinStatus[i] = true;
                coinRandom[i] = rand() % 2;
            }
            if(collisionCheck(bird.dstrect, pipe[i].dstrectUp)
                    || collisionCheck(bird.dstrect, pipe[i].dstrectDown))
            {
                lose = true;
            }
            if(collisionCheck(bird.dstrect, coin[i].dstrect) && coinStatus[i]==true && coinRandom[i]==1)
            {
                sfx.playCoin();
                score+=2;
                scoreboard.update(score);
                coinStatus[i]=false;
            }
            if(bird.dstrect.x > pipe[i].dstrectUp.x && scoreStatus[i]==false && lose == false)
            {
                sfx.playPoint();
                score+=config.multiplier;
                scoreStatus[i] = true;
                scoreboard.update(score);
            }
            pipe[i].display(renderer);
            coin[i].updatePos(config.multiplier);
            if(coinStatus[i]==true && coinRandom[i]==1)
            {
                coin[i].display(renderer);
            }
        }
    }
}

void Dinosaur::resDestroy()
{
    for(int i=0; i<6; i++)
    {
        pipe[i].destroy();
        coin[i].destroy();
    }
    scoreboard.destroy();
}



