#include "game.h"

void game(SDL_Renderer* renderer, vector<int> &highscore,int tempNameBG)
{
    SDL_Rect fullscreen_rect = {0,0,500,800};

    //tao cac bien event, music, chunk
    SDL_Event event;
    Mix_Chunk *crash_sound_effect = Mix_LoadWAV("music/Car Crash.mp3");
    Mix_Chunk *speedup_sound_effect = Mix_LoadWAV("music/Speedup.mp3");
    Mix_Chunk *coinCollect_sound_effect = Mix_LoadWAV("music/Coin collect.mp3");
    Mix_Chunk *rain_sound_effect = Mix_LoadWAV("music/Rain.mp3");
    Mix_Music *bg_music = Mix_LoadMUS("music/BGmusic.mp3");
    Mix_PlayMusic(bg_music,-1);
    Mix_VolumeMusic(90);

    // tao background
    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = -3200;
    background_rect.h = 4000;
    background_rect.w = 500;


    // tao nhan vat
    Player mainPlayer(125,650);
    string nameFilePlayer = "image/Player.png";

    // tao rao chan
    Barrier barrier1(10,0);
    Barrier barrier2(110,0);

    // tao coin
    SDL_Rect coin_rect = {0,-100,50,60};

    // tao font score
    TTF_Font* font = TTF_OpenFont("Roboto.ttf",50);

    //tao cac bien can thiet
    int healthPoint =0;
    int countScore =0,count_animation =0;
    bool running = true;
    bool checkMenustart =true, checkHowtoplay =true,checkmusicBG =true, checkspeedup =true, checkrain =true;
    //ten cac images dung lam animation
    string rain_animation[4] = {"image/rain1.png","image/rain2.png","image/rain3.png","image/rain4.png"};
    string mainmenu_animation[4] = {"image/menustart1.png","image/menustart2.png","image/menustart3.png","image/menustart4.png"};
    int temp_mainmenu_animation = 0, temp_rain_animation=0;

    //tao main menu start && chay menu start
    while(checkMenustart)
    {
        count_animation++;
        render_image("image/start.png",renderer,fullscreen_rect); // trong header Function.h
        if (count_animation % 20 ==0) temp_mainmenu_animation++;
        if (temp_mainmenu_animation ==4) temp_mainmenu_animation=0;
        render_image(mainmenu_animation[temp_mainmenu_animation],renderer,fullscreen_rect);

        pollEvent(checkMenustart,checkmusicBG);
        renderSoundButton(checkmusicBG,renderer);
        SDL_RenderPresent(renderer);
    }

    //tao man hinh howtoplay
    while (checkHowtoplay)
    {
        render_image("image/howtoplay.png",renderer,fullscreen_rect); // trong header Function.h

        pollEvent(checkHowtoplay,checkmusicBG);
        renderSoundButton(checkmusicBG,renderer);
        SDL_RenderPresent(renderer);


    }

    //tao menu dung 3s
    if (tempNameBG%2 ==0){
        render_image("image/start1.png",renderer,fullscreen_rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        render_image("image/start2.png",renderer,fullscreen_rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        render_image("image/start3.png",renderer,fullscreen_rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    else{
        render_image("image/start4.png",renderer,fullscreen_rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        render_image("image/start5.png",renderer,fullscreen_rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        render_image("image/start6.png",renderer,fullscreen_rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    //vong while chinh chay game
    while (running)
    {
        int random = rand()%3;
        //chay background
        if (tempNameBG%2==0) render_image("image/BG1.png",renderer,background_rect);
        else render_image("image/BG2.jpg",renderer,background_rect);

        //khi diem > 20000 thi nhac chay effect speedup
        if (countScore > 20000){
                if (checkspeedup) {Mix_PlayChannel(-1,speedup_sound_effect,0);checkspeedup= false ;}
            }

        //chinh toc do background
        if (countScore < 20000) background_rect.y +=5;
        else background_rect.y +=10;

        if (background_rect.y > 0) background_rect.y =-3200;

        //chay mainplayer
        mainPlayer.renderPlayer(renderer, nameFilePlayer );
        mainPlayer.inside();

        //poll event
        if(SDL_PollEvent(&event))
        {
            mainPlayer.pollEvent(event, renderer, nameFilePlayer,checkmusicBG);
        }
        renderSoundButton(checkmusicBG,renderer);

        //chay coin
        render_image("image/coin.png",renderer,coin_rect);
        if (running)
        {
            if (coin_rect.y ==-100)
            {
                if (random == 0) coin_rect.x =25;
                else if (random == 1) coin_rect.x =125;
                else if (random == 2) coin_rect.x =225;
            }
            coin_rect.y += 10;
            if (coin_rect.y > 800) coin_rect.y = -100;

            //collision coin vs player
            if (coin_rect.x == mainPlayer.x && (coin_rect.y +coin_rect.h) > 670 && (coin_rect.y +coin_rect.h) < (670 +85)) //85 la mainplayer.h
            {
                coin_rect.y = -100;
                Mix_PlayChannel(-1,coinCollect_sound_effect,0);
                countScore += 1000;
            }
        }

        //in ra score
        countScore+=10;
        string str = to_string(countScore); //cast int to string
        showScore(font, renderer,str, highscore.back()); //trong header Function.h

        //chay barriers
        barrier1.renderBarrier(renderer);
        barrier1.move1(countScore);

        barrier2.renderBarrier(renderer);
        barrier2.move2(countScore);

        // chay rain animation
        if (countScore > 10000 && countScore < 30000)
        {
            if (checkrain) {Mix_PlayChannel(-1,rain_sound_effect,0); checkrain = false;}
            count_animation++;
            if (count_animation % 30 ==0) temp_rain_animation++;
            if (temp_rain_animation ==4) temp_rain_animation=0;
            render_image(rain_animation[temp_rain_animation],renderer,fullscreen_rect);
        }
        if (countScore > 30000) Mix_FreeChunk(rain_sound_effect);

        //kiem tra va cham
        if (barrier1.checkCollision(mainPlayer) ) {healthPoint++; Mix_PlayChannel(-1,crash_sound_effect,0);}
        if (barrier2.checkCollision(mainPlayer) ) {healthPoint++; Mix_PlayChannel(-1,crash_sound_effect,0);}

        // chay health
        if (healthPoint ==4)
        {
            running = false;
        }
        else createHealth(font,healthPoint,renderer); //trong header health.h

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    Mix_VolumeChunk(speedup_sound_effect,0);
    SDL_Delay(200);
    highscore.push_back(countScore);
    // sap xep vector de in highestscore
    sort(highscore.begin(), highscore.end());

    //render gameover menu
    render_image("image/gameover.png",renderer,fullscreen_rect); // trong header Function.h
    //render highest score:
    SDL_Color color = {255,50,147,225};
    SDL_Rect highest_rect1 = {320,503,110,40};
    string highestScore = to_string(highscore.back());
    SDL_Surface* surfScore = TTF_RenderText_Solid(font,highestScore.c_str(), color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer,surfScore);
    SDL_RenderCopy(renderer,tex,NULL,&highest_rect1);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);
    SDL_RenderPresent(renderer);

    //ket thuc
    Mix_HaltMusic();
    Mix_FreeChunk(crash_sound_effect);
    Mix_FreeChunk(speedup_sound_effect);
    Mix_FreeChunk(rain_sound_effect);
    Mix_FreeChunk(coinCollect_sound_effect);
    Mix_FreeMusic(bg_music);


    TTF_CloseFont(font);

}

