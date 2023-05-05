#include "barrier.h"


using namespace std;

void Barrier::renderBarrier(SDL_Renderer* renderer)
{
    string nameBarrier[5] = {"image/Barrier_1.png", "image/Barrier_2.png" ,"image/Barrier_3.png"
    , "image/Barrier_4.png", "image/Barrier_5.png"};

    SDL_Rect block_rect;
    block_rect.x = x;
    block_rect.y = y;
    block_rect.w = 80;
    block_rect.h = 30;
    render_image(nameBarrier[posNameBarrier],renderer,block_rect);
}

void Barrier::move1(int countScore)
{
    if (countScore < 20000) y += 10;
    else y += 20;
    if (posBarrier == 0) x = 110;
    else if (posBarrier == 1) x = 10;
    else if (posBarrier == 2) x = 110;
    else x = 210;

    if (y > 800)
    {
        y = 0;
        posBarrier++;
        posNameBarrier++;
        if (posBarrier == 3) posBarrier =0;
        if (posNameBarrier ==4) posNameBarrier =0;
    }

}

void Barrier::move2(int countScore)
{
    if (countScore < 20000) y += 8;
    else y += 16;
    if (posBarrier == 0) x = 210;
    else if (posBarrier == 1) x = 110;
    else if (posBarrier == 2) x = 10;
    else if (posBarrier == 3) x = 210;
    else x = 110;

    if (y > 800)
    {
        y = 0;
        posBarrier++;
        posNameBarrier++;
        if (posBarrier == 4) posBarrier =0;
        if (posNameBarrier ==4) posNameBarrier =0;
    }
}

bool Barrier::checkCollision(Player playerCheck)
{
    //cout << playerCheck.x<<endl;
    if ( x + 15 == playerCheck.x && y == 640 ) return true;
    else return false;
}

