#include "health.h"


void createHealth(TTF_Font* font, int healthPoint, SDL_Renderer* renderer)
{
    //render "Health :"
    SDL_Color color = {0,0,0,225};
    SDL_Rect healthbar_rect = {310,540,130,40};
    SDL_Surface *surfScore = TTF_RenderText_Solid(font, "Health :", color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer,surfScore);
    SDL_RenderCopy(renderer,tex,NULL,&healthbar_rect);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);


    // render thanh mau
    string nameHealth[4] = {"image/health1.png" , "image/health2.png" ,"image/health3.png" ,"image/health4.png" };

    SDL_Rect health_rect = {303,600,190,38};
    render_image(nameHealth[healthPoint],renderer,health_rect);
}

