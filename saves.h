#ifndef SAVES_H
#define SAVES_H

#include <fstream>

using namespace std;

class Saves
{
public:
    void read();
    void write();

    int highscoreCasual = 0;
    int highscorePvP = 0;
    int highscoreDinosaur = 0;
private:
    fstream savefile;
};

#endif // SAVES_H
