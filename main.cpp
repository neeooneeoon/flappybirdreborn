#include "flappy_bird.h"
#include "dinosaur.h"

using namespace std;

int main(int argc, char* argv[])
{
    FlappyBird FlappyBird;
    FlappyBird.init();
    FlappyBird.menu();
    FlappyBird.quit();
    return 0;
}
