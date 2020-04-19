#include "flappy_bird.h"

using namespace std;

void FlappyBird::init()
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    bird.loadPNG(renderer);
    background.init(renderer);
    base.init(renderer);
    message.init(renderer);
    flash.init(renderer);
    sfx.init();
    scoreboard.init(renderer);
    resInit();
    text.init(renderer);
    indicator.init(renderer);
}

void FlappyBird::quit()
{
    bird.destroy();
    background.destroy();
    base.destroy();
    resDestroy();
    flash.destroy();
    message.destroy();
    sfx.close();
    text.destroy();
    indicator.destroy();
    scoreboard.destroy();
    quitSDL(window, renderer);
}

void FlappyBird::reset()
{
    config.multiplier = 1;
    lose = false;
    gameQuit = false;
    menuLoop = true;
    getReadyLoop = true;
    level2 = false;
    casual = false;
    score = 0;

    bird.destroy();
    background.destroy();
    base.destroy();
    resDestroy();
    flash.destroy();
    message.destroy();
    text.destroy();

    bird.loadPNG(renderer);
    background.init(renderer);
    base.init(renderer);
    message.init(renderer);
    flash.init(renderer);
    scoreboard.init(renderer);
    resInit();
    text.init(renderer);

    menu();
}

void FlappyBird::menu()
{
    sfx.playSwoosh();
    sfx.playBGM();
    while(menuLoop==true && casual == false)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                if(mouseParRect(text.casualRect,mouseY))
                {
                    sfx.playSelect();
                    indicator.setPosCasual();
                    indicator.selected = 1;
                }
                else if(mouseParRect(text.pvpRect,mouseY))
                {
                    sfx.playSelect();
                    indicator.setPosPvP();
                    indicator.selected = 2;
                }
                else if(mouseParRect(text.dinosaurRect,mouseY))
                {
                    sfx.playSelect();
                    indicator.setPosDinosaur();
                    indicator.selected = 3;
                }
                else if(mouseParRect(text.quitRect,mouseY))
                {
                    sfx.playSelect();
                    indicator.setPosQuit();
                    indicator.selected = 4;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if(mouseInRect(text.casualRect, mouseX, mouseY))
                    {
                        sfx.playSelected();
                        casual = true;
                        menuLoop = false;
                    }
                    if(mouseInRect(text.quitRect, mouseX, mouseY))
                    {
                        sfx.playSelected();
                        menuLoop = false;
                    }
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT:
                menuLoop = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    sfx.playSelect();
                    indicator.select(true);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    sfx.playSelect();
                    indicator.select(false);
                    break;
                case SDL_SCANCODE_RETURN:
                    switch(indicator.selected)
                    {
                    case 1:
                        casual = true;
                        menuLoop = false;
                        sfx.playSelected();
                        break;
                    case 2:
                        //placeholder
                        sfx.playSelected();
                        break;
                    case 3:
                        //placeholder
                        sfx.playSelected();
                        break;
                    case 4:
                        sfx.playSelected();
                        menuLoop = false;
                        break;
                    }
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }

        SDL_RenderClear(renderer);
        framerateControl(config.frameNum);
        background.display(renderer, config.multiplier);
        base.display(renderer, config.multiplier);
        message.displayMenu(renderer);
        text.display(renderer);
        indicator.display(renderer);
        SDL_RenderPresent(renderer);
    }
    sfx.stopBGM();
    if(casual==true)
        getReady();
}

void FlappyBird::getReady()
{
    sfx.playSwoosh();
    bird.initCasual();
    while(getReadyLoop == true)
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
                getReadyLoop = false;
                gameQuit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    bird.update();
                    bird.keyUpdate();
                    getReadyLoop = false;
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
                    getReadyLoop = false;
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

void FlappyBird::gameLoop()
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
        bird.update();
        bird.status(lose);
        nextLevel();
        bird.collideBase(base.rect1, base.rect2, lose);
        framerateControl(config.frameNum);
        display();
    }
    if(gameQuit == false)
    {
        gameOver();
    }
}

void FlappyBird::gameOver()
{
    //Gameover Scene
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
    sfx.playSwoosh();

    //Highscore(saves) R/W
    saves.read();
    if(casual == true)
    {
        if(saves.highscoreCasual<score)
        {
            saves.highscoreCasual = score;
            scoreboard.newHighScore = true;
        }
        scoreboard.getHighScore(saves.highscoreCasual);
    }
    saves.write();

    //Display Gameover Scoreboard
    while(gameQuit==false)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameQuit = true;
                realQuit = true;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                case SDL_SCANCODE_RETURN:
                    gameQuit = true;
                default:
                    break;
                }
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if(mouseX>=590 && mouseX<=690
                            && mouseY>=445 && mouseY<=475)
                    {
                        gameQuit = true;
                    }
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        SDL_RenderClear(renderer);

        background.display(renderer, config.multiplier);
        base.display(renderer, config.multiplier);
        for(int i=0; i<6; i++)
        {
            if(coinStatus[i]==true && coinRandom[i]==1)
            {
                coin[i].display(renderer);
            }
            pipe[i].display(renderer);
        }
        message.displayGameOver(renderer);
        scoreboard.displayGameOver(renderer);

        framerateControl(config.frameNum);
        SDL_RenderPresent(renderer);
    }
    if(realQuit == false)
    {
        reset();
    }
}

void FlappyBird::display()
{
    SDL_RenderClear(renderer);

    background.display(renderer, config.multiplier);
    base.display(renderer, config.multiplier);
    resGen();
    bird.display(renderer);
    scoreboard.display(renderer, bird.dstrect.y);

    SDL_RenderPresent(renderer);
}

void FlappyBird::resInit()
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

void FlappyBird::resGen()
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
            pipe[i].update(config.multiplier);
            coin[i].updatePos(config.multiplier);
            if(coinStatus[i]==true && coinRandom[i]==1)
            {
                coin[i].display(renderer);
            }
        }
    }
}

void FlappyBird::resDestroy()
{
    for(int i=0; i<6; i++)
    {
        pipe[i].destroy();
        coin[i].destroy();
    }
    scoreboard.destroy();
}

void FlappyBird::nextLevel()
{
    if(score>=20 && level2==false)
    {
        config.multiplier = 2;
        sfx.playLevelUp();
        level2 = true;
    }
}
