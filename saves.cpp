#include "saves.h"

using namespace std;

void Saves::read()
{
    savefile.open("saves\\casual.txt");
    if(savefile.is_open())
    {
        savefile >> highscoreCasual;
    }
    savefile.close();

    savefile.open("saves\\pvp.txt");
    if(savefile.is_open())
    {
        savefile >> highscorePvP;
    }
    savefile.close();

    savefile.open("saves\\dinosaur.txt");
    if(savefile.is_open())
    {
        savefile >> highscoreDinosaur;
    }
    savefile.close();
}

void Saves::write()
{
    savefile.open("saves\\casual.txt", ios::out | ios::trunc);
    savefile << highscoreCasual;
    savefile.close();

    savefile.open("saves\\pvp.txt", ios::out | ios::trunc);
    savefile << highscorePvP;
    savefile.close();

    savefile.open("saves\\dinosaur.txt", ios::out | ios::trunc);
    savefile << highscoreDinosaur;
    savefile.close();
}
