#include "Function.h"

using namespace std;

void pollEvent(bool &check, bool &checkmusicBG)
{
    SDL_Event event;
    if ( SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)) check = false;
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
        {
            if (checkmusicBG == true ) {checkmusicBG = false; Mix_VolumeMusic(0);}
            else if (checkmusicBG == false ) {checkmusicBG = true; Mix_VolumeMusic(90);}
        }
    }
}

SDL_Texture* load_image(string file_path,SDL_Renderer* renderer)
{
    SDL_Surface* loadImage = NULL;
    SDL_Texture* tex = NULL;
    loadImage = IMG_Load(file_path.c_str());
    if(loadImage != NULL)
    {
        tex = SDL_CreateTextureFromSurface(renderer, loadImage);
        SDL_FreeSurface(loadImage);

    }
    return tex;
}

void render_image(string file_path,SDL_Renderer* renderer,SDL_Rect rect)
{
    SDL_Texture* tex = NULL;
    tex = load_image(file_path.c_str() ,renderer);
    SDL_RenderCopy(renderer , tex, NULL, &rect);
    SDL_DestroyTexture(tex);

}

void renderSoundButton(bool &checkmusicBG, SDL_Renderer* renderer)
{
    SDL_Rect sound_rect = {0,0,50,50};
    if (checkmusicBG == true) render_image("image/unmute.png",renderer,sound_rect);
    if (checkmusicBG == false) render_image("image/mute.png",renderer,sound_rect);
}

void showScore(TTF_Font* font, SDL_Renderer* render,string score, long long int highestScore)
{
    //render "Score :"
    SDL_Color color = {0,0,0,225};
    SDL_Rect scorebar_rect = {310,75,115,40};

    SDL_Surface* surfScore = TTF_RenderText_Solid(font, "Score :", color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(render,surfScore);
    SDL_RenderCopy(render,tex,NULL,&scorebar_rect);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);

    //render Highest score
    SDL_Rect highScoreBar_rect ={310,240,180,40};

    string highScore = to_string(highestScore);
    string temp ="Highest :";
    string showHighestScore = temp +highScore;
    surfScore = TTF_RenderText_Solid(font,showHighestScore.c_str() , color);
    tex = SDL_CreateTextureFromSurface(render,surfScore);
    SDL_RenderCopy(render,tex,NULL,&highScoreBar_rect);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);

    //render Score
    SDL_Rect score_rect = {430,75,60,40};

    surfScore = TTF_RenderText_Solid(font, score.c_str(), color);
    tex = SDL_CreateTextureFromSurface(render,surfScore);
    SDL_RenderCopy(render,tex,NULL,&score_rect);

    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);
}
