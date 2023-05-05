#ifndef BARRIER_H
#define BARRIER_H

#include "player.h"
#include "function.h"

using namespace std;

struct Barrier
{
    int x;
    int y;
    int posNameBarrier = 0;
    int posBarrier = 1;
    int speed1 =8, speed2 = 10;
    Barrier (){};
    Barrier (int _x,int _y)
    {
        x = _x;
        y = _y;
    }
    void renderBarrier(SDL_Renderer* renderer);

    void move1(int countScore);

    void move2(int countScore);

    bool checkCollision(Player playerCheck);
};
#endif // BARRIER_H

