#ifndef MENU_H
#define MENU_H

#include "../headers/common.h"

struct Menu {
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font;
    SDL_Texture* intro = nullptr;

    Menu(SDL_Renderer* renderer);
    ~Menu();

    void render();
    void alpha_mod(SDL_Renderer* renderer, SDL_Texture* texture);
};

#endif
