#include "flappy_bird.h"

using namespace std;

void FlappyBird::game_loop()
{
    //bool keyCheck = false;
    while(!lose)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                lose = true;
                break;
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
    game_over();
}

void FlappyBird::game_over(){
    config.multiplier = 0;
    sfx.playHit();
    sfx.playDie();
    while(bird.dstrect.y<1000){
        update(1280/60, lose);
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
    scoreboard.init(renderer);
    scoreboard.update(0);
    sfx.init();
    pipeInit();
}

void FlappyBird::quit()
{
    bird.destroy();
    background.destroy();
    base.destroy();
    pipeDestroy();
    scoreboard.destroy();
    sfx.close();
    quitSDL(window, renderer);
}

void FlappyBird::update(double delta_time, bool &close)
{
    bird.update();
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

void FlappyBird::collision(){
    if(collisionCheck(bird.dstrect, base.rect1)
       || collisionCheck(bird.dstrect, base.rect2))
    {
        lose = true;
    }
}

void FlappyBird::pipeInit(){
    for(int i=0; i<6; i++){
        pipe[i].init(renderer, i*250);
        scoreStatus[i]=false;
    }
}

void FlappyBird::pipeGen(){
    for(int i=0; i<6; i++){
        if(pipe[i].dstrectDown.x<-60){
            pipe[i].destroy();
            pipe[i].init(renderer, 150);
            scoreStatus[i] = false;
        }
        if(collisionCheck(bird.dstrect, pipe[i].dstrectUp)
           || collisionCheck(bird.dstrect, pipe[i].dstrectDown)){
                lose = true;
           }
        if(bird.dstrect.x > pipe[i].dstrectUp.x && scoreStatus[i]==false){
            sfx.playPoint();
            score++;
            scoreStatus[i] = true;
            scoreboard.update(score);
        }
        pipe[i].display(renderer, config.multiplier);
    }
}

void FlappyBird::pipeDestroy(){
    for(int i=0; i<6; i++){
        pipe[i].destroy();
    }
}

void FlappyBird::nextLevel(){
    if(score==20){
        config.multiplier = 2;
    }
}
