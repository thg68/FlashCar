#include "player.h"


using namespace std;

void Player::renderPlayer(SDL_Renderer* renderer,string file_path)
{
    SDL_Rect player_rect;
    player_rect.x = x;
    player_rect.y = y;
    player_rect.w = 45;
    player_rect.h = 85;
    render_image(file_path.c_str(), renderer,player_rect);
}

void Player::inside()
{
    if (x < 25) x=25;
    if (x > 225) x=225;
}
void Player::pollEvent(SDL_Event event,SDL_Renderer* renderer, string &nameFilePlayer,bool &checkmusicBG)
{
    switch (event.type)
    {
        case SDLK_ESCAPE: break;
        //khi ấn phím
        default :
        {
        if (event.type == SDL_KEYDOWN )
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_DOWN:
                    {
                        if (checkmusicBG == true ) {checkmusicBG = false; Mix_VolumeMusic(0); break;}
                        else if (checkmusicBG == false ) {checkmusicBG = true; Mix_VolumeMusic(90); break;}
                    }
                case SDLK_LEFT:
                    {
                        if (x == 25);
                        else{
                            x -= step;
                            nameFilePlayer = "image/Player_ani_1.png";
                        }
                        break;
                    }
                case SDLK_RIGHT:
                    {
                        if (x == 225);
                        else{
                            x += step;
                            nameFilePlayer = "image/Player_ani_2.png";
                        }
                        break;
                    }
                default: break;
            }
        }
        //khi nhả phím
        else if (event.type == SDL_KEYUP )
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_LEFT: nameFilePlayer = "image/Player.png"; break;
                case SDLK_RIGHT: nameFilePlayer = "image/Player.png";; break;
                default: break;
            }
        }
        } break;
    }
}



