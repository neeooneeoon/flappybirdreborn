#include "flappy_bird.h"

using namespace std;

int main(int argc, char* argv[])
{
    FlappyBird FlappyBird;

    FlappyBird.init();
    FlappyBird.getReady();
    FlappyBird.quit();

    return 0;
}
