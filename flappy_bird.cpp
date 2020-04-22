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
    multiplier = 1;
    score = 0;
    gameLose = false;
    gameReset = false;
    menuLoop = true;
    readyLoop = true;
    level2 = false;
    casual = false;
    versus = false;
    help = false;

    bird.destroy();
    background.destroy();
    base.destroy();
    resDestroy();
    flash.destroy();
    message.destroy();
    text.destroy();
    scoreboard.destroy();

    bird.loadPNG(renderer);
    background.init(renderer);
    base.init(renderer);
    message.init(renderer);
    flash.init(renderer);
    scoreboard.init(renderer);
    text.init(renderer);

    menu();
}

void FlappyBird::menu()
{
    sfx.playSwoosh();
    sfx.playBGM();
    while(menuLoop==true
            && casual == false && versus == false)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                if(mouseParRect(text.casualRect,mouseY) && indicator.selected != 1)
                {
                    sfx.playSelect();
                    indicator.setPosCasual();
                }
                else if(mouseParRect(text.versusRect,mouseY) && indicator.selected != 2)
                {
                    sfx.playSelect();
                    indicator.setPosVersus();
                }
                else if(mouseParRect(text.helpRect,mouseY) && indicator.selected != 3)
                {
                    sfx.playSelect();
                    indicator.setPosHelp();
                }
                else if(mouseParRect(text.quitRect,mouseY) && indicator.selected != 4)
                {
                    sfx.playSelect();
                    indicator.setPosQuit();
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
                    if(mouseInRect(text.versusRect, mouseX, mouseY))
                    {
                        sfx.playSelected();
                        menuLoop = false;
                        versus = true;
                    }
                    if(mouseInRect(text.helpRect, mouseX, mouseY))
                    {
                        sfx.playSelected();
                        if(help==false)
                            help = true;
                        else help = false;
                    }
                    if(mouseInRect(text.quitRect, mouseX, mouseY))
                    {
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
                        versus = true;
                        menuLoop = false;
                        sfx.playSelected();
                        break;
                    case 3:
                        if(help==false)
                            help = true;
                        else help = false;
                        sfx.playSelected();
                        break;
                    case 4:
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


        background.display(renderer, multiplier);
        base.display(renderer, multiplier);
        message.displayMenu(renderer);
        text.display(renderer);
        indicator.display(renderer);
        if(help == true)
            text.helperDisplay(renderer);

        framerateControl(frameNum);
        SDL_RenderPresent(renderer);
    }
    sfx.stopBGM();
    resInit();
    if(casual==true)
        getReady();
    else if(versus == true)
        versusReady();
}

void FlappyBird::getReady()
{
    sfx.playSwoosh();
    bird.initCasual();
    while(readyLoop == true)
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
                gameLose = true;
                readyLoop = false;
                gameReset = true;
                gameQuit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if(casual == true)
                        bird.keyUpdate();
                    else if(versus == true)
                        bird.versusKeyUpdate();
                    bird.update();
                    readyLoop = false;
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
                    bird.update();
                    bird.keyUpdate();
                    readyLoop = false;
                    break;
                default:
                    break;
                }
            }
        }
        background.display(renderer, multiplier);
        base.display(renderer, multiplier);
        bird.display(renderer);
        bird.aniUpdate();
        message.display(renderer, false);
        SDL_RenderPresent(renderer);
        framerateControl(frameNum);
    }
    gameLoop();
}

void FlappyBird::gameLoop()
{
    while(!gameLose)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameLose = true;
                gameReset = true;
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
        bird.statusUpdate(gameLose);
        nextLevel();
        bird.collideBase(base.rect1, base.rect2, gameLose);
        framerateControl(frameNum);
        display();
    }
    if(gameQuit == false)
        gameOver();
}

void FlappyBird::versusReady()
{
    sfx.playSwoosh();
    bird.initVersus();
    while(readyLoop == true)
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
                gameLose = true;
                readyLoop = false;
                gameReset = true;
                gameQuit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    bird.update();
                    bird.keyUpdate();
                    readyLoop = false;
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
                    bird.update();
                    bird.keyUpdate();
                    readyLoop = false;
                    break;
                default:
                    break;
                }
            }
        }
        background.display(renderer, multiplier);
        base.display(renderer, multiplier);
        bird.display(renderer);
        bird.aniUpdate();
        message.display(renderer, true);
        SDL_RenderPresent(renderer);
        framerateControl(frameNum);
    }
    gameVersus();
}

void FlappyBird::gameVersus()
{
    while(!gameLose)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameLose = true;
                gameReset = true;
                gameQuit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    bird.versusKeyUpdate();
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
                    bird.versusKeyUpdate();
                    sfx.playWing();
                    break;
                default:
                    break;
                }
            }
        }
        bird.update();
        bird.versusstatusUpdate(gameLose);
        nextLevel();
        framerateControl(frameNum);
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
    multiplier = 0;
    sfx.playHit();
    flash.display(renderer);
    sfx.playDie();
    while(bird.dstrect.y<1000)
    {
        SDL_RenderClear(renderer);

        background.display(renderer, multiplier);
        base.display(renderer, multiplier);
        resGen();
        bird.update();
        bird.statusUpdate(gameLose);
        bird.display(renderer);
        flash.displayNoAlpha(renderer);

        framerateControl(frameNum);
        SDL_RenderPresent(renderer);
    }
    sfx.playSwoosh();

    //High-score(saves) R/W
    saves.read();
    if(casual == true)
    {
        if(saves.compareCasual(score))
        {
            scoreboard.newHighScore = true;
        }
        scoreboard.getHighScore(saves.highscoreCasual);
    }
    else if(versus == true)
    {
        if(saves.compareVersus(score))
        {
            scoreboard.newHighScore = true;
        }
        scoreboard.getHighScore(saves.highscoreVersus);
    }
    saves.write();

    //Display Gameover Scoreboard
    while(gameReset==false)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameReset = true;
                gameQuit = true;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                case SDL_SCANCODE_RETURN:
                    gameReset = true;
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
                        gameReset = true;
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

        background.display(renderer, multiplier);
        base.display(renderer, multiplier);
        for(int i=0; i<6; i++)
        {
            if(coinStatus[i]==true && coinRandom[i]==1)
            {
                coin[i].display(renderer);
            }
            if(casual == true)
            {
                pipe[i].display(renderer);
            }
            else if(versus == true)
            {
                pipe[i].versusDisplay(renderer);
            }

        }
        message.displayGameOver(renderer);
        scoreboard.displayGameOver(renderer);

        framerateControl(frameNum);
        SDL_RenderPresent(renderer);
    }
    if(gameQuit == false)
    {
        reset();
    }
}

void FlappyBird::display()
{
    SDL_RenderClear(renderer);

    background.display(renderer, multiplier);
    base.display(renderer, multiplier);
    resGen();
    if(casual == true)
        bird.display(renderer);
    else if(versus == true)
        bird.versusDisplay(renderer);
    scoreboard.display(renderer, bird.dstrect.y);

    SDL_RenderPresent(renderer);
}

void FlappyBird::resInit()
{
    //Get a random choice
    randNum = rand() % 2;

    for(int i=0; i<6; i++)
    {
        //Load a random pipe sprite based on randNum
        if(randNum == 0)
            pipe[i].loadGreen(renderer);
        else
            pipe[i].loadRed(renderer);

        //Initialize pipe(s) based on game mode
        if(casual == true)
            pipe[i].init(i*250);
        else if(versus == true)
            pipe[i].versusInit(i*250);

        scoreStatus[i]=false;

        //Initialize coin(s)
        coin[i].loadPNG(renderer);
        coin[i].init(i*250);
        coinStatus[i] = true;
        coinRandom[i] = rand() % 2;

        //Initialize pacman(s)
        if(versus == true)
        {
            pacman[i].loadPacman(renderer);
            pacman[i].init(i*250, pipe[i].length);
            pacmanStatus[i] = true;
            pacmanRandom[i] = rand() % 2;
            pacmanScore[i] = false;
        }
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
            //Pipe Generators & Score Updater
            if(pipe[i].dstrectDown.x<-60)
            {
                if(casual == true)
                    pipe[i].init(150);
                else if(versus == true)
                    pipe[i].versusInit(150);
                scoreStatus[i] = false;
            }
            if(collisionCheck(bird.dstrect, pipe[i].dstrectDown))
            {
                gameLose = true;
            }
            if(collisionCheck(bird.dstrect, pipe[i].dstrectUp) && casual == true)
            {
                gameLose = true;
            }
            if(bird.dstrect.x > pipe[i].dstrectDown.x && scoreStatus[i]==false && gameLose == false)
            {
                sfx.playPoint();
                score+=multiplier;
                scoreStatus[i] = true;
                scoreboard.update(score);
            }
            //Display Pipe(s)
            if(casual == true)
            {
                pipe[i].display(renderer);
                pipe[i].update(multiplier);
            }
            else if(versus == true)
            {
                pipe[i].versusDisplay(renderer);
                pipe[i].versusUpdate(multiplier);
            }

            //Coin Generators && Score Updater
            if(coin[i].dstrect.x<-60)
            {
                coin[i].init(10);
                coinStatus[i] = true;
                coinRandom[i] = rand() % 2;
            }
            if(collisionCheck(bird.dstrect, coin[i].dstrect) && coinStatus[i]==true && coinRandom[i]==1)
            {
                sfx.playCoin();
                score+=2;
                scoreboard.update(score);
                coinStatus[i]=false;
            }
            //Display Coin(s)
            coin[i].updatePos(multiplier);
            if(coinStatus[i]==true && coinRandom[i]==1)
                coin[i].display(renderer);

            //Pacman
            if(versus == true)
            {
                //Generators && Score updater
                if(pacman[i].dstrect.x<-60) //|| collisionCheck(pacman[i].dstrect, coin[i].dstrect)==false)
                {
                    pacman[i].init(10, pipe[i].length);
                    pacmanStatus[i] = true;
                    pacmanRandom[i] = rand() % 2;
                    pacmanScore[i] = false;
                }
                if(collisionCheck(bird.dstrect, pacman[i].dstrect) && pacmanStatus[i]==true && pacmanRandom[i]==1)
                {
                    gameLose = true;
                    cout << "ok" << endl;
                }
                if(bird.dstrect.x > pacman[i].dstrect.x && pacmanStatus[i]==true && pacmanRandom[i]==1 && pacmanScore[i]==false)
                {
                    sfx.playPoint();
                    pacmanScore[i] = true;
                    score+=multiplier;
                    scoreboard.update(score);
                }
                //Display Pacman(s)
                pacman[i].update(multiplier);
                if(pacmanStatus[i]==true && pacmanRandom[i]==1)
                    pacman[i].display(renderer);
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
        if(versus == true)
            pacman[i].destroy();
    }
}

void FlappyBird::nextLevel()
{
    if(score>=20 && level2==false)
    {
        multiplier = 2;
        level2 = true;
        sfx.playLevelUp();
    }
}


