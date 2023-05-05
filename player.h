#ifndef PLAYER_H
#define PLAYER_H

#include "Function.h"

using namespace std;
struct Player{
    int x;
    int y;
    int step =100;
    Player () {};
    Player (int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    void renderPlayer(SDL_Renderer* renderer,string file_path);

    void inside();

    void pollEvent(SDL_Event event,SDL_Renderer* renderer, string &nameFilePlayer,bool &checkmusicBG);
};

#endif // MAINPLAYER_H


