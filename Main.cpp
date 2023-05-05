#include "game.h"

const int S_width = 500;
const int S_height = 800;
const string title = "Racing Car";

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;
bool initSDL();


int main(int argc, char* argv[])
{
    //tao window, renderer
    if (initSDL() == false) return 0;

    bool is_run=true, playAgain = true;
    vector <int> highscore;
    highscore.push_back(0);
    int tempNameBG =0;

    while(is_run == true)
    {
        game(renderer,highscore,tempNameBG);
        playAgain = true;

        while (playAgain == true)
        {
            if ( SDL_WaitEvent(&event) != 0 )
            {
                if (event.type == SDL_QUIT) {is_run = false; playAgain = false;}
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) playAgain = false;
            }
        }
        tempNameBG++;
    }


    //ket thuc
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

    Mix_Quit();
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
    return 0;
}

bool initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "Error Init";
        return false;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, S_width, S_height, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        cout << "Failed to Create window";
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        cout << "Failed to Create renderer";
        return false;
    }

    if (TTF_Init() <0)
    {
        cout << "Error TTF init";
        return false;
    }
    if (Mix_OpenAudio(48000,MIX_DEFAULT_FORMAT,2,4096) < 0)
    {
        cout << "Error Create audio";
        return false;
    }

    return true;
}



