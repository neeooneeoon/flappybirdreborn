#ifndef SAVES_H
#define SAVES_H

#include <fstream>

using namespace std;

class Saves
{
public:
    void read();
    void write();
private:
    fstream casual;
    fstream pvp;
    fstream dinosaur;
    int highscoreCasual;
    int highscorePvP;
    int highscoreDinosaur;
};

#endif // SAVES_H
