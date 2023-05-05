#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <SDl_mixer.h>
using namespace std;

void pollEvent(bool &check, bool &checkmusicBG);

SDL_Texture* load_image(string file_path,SDL_Renderer* renderer);

void render_image(string file_path,SDL_Renderer* renderer,SDL_Rect rect);

void renderSoundButton(bool &checkmusicBG, SDL_Renderer* renderer);

void showScore(TTF_Font* font, SDL_Renderer* render,string score, long long int highestScore);

#endif // FUNCTION_H


