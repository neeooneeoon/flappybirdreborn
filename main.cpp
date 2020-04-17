#include "flappy_bird.h"
#include "dinosaur.h"

using namespace std;

int main(int argc, char* argv[])
{
    FlappyBird FlappyBird;
    FlappyBird.init();
    FlappyBird.getReady();
    FlappyBird.quit();

    /*Dinosaur dinosaur;
    dinosaur.init();
    dinosaur.gameLoop();
    dinosaur.quit();*/

    return 0;
}
