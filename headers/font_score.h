#ifndef FONT_SCORE_H
#define FONT_SCORE_H

#include "../headers/common.h"

struct FontScore {
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* textTexture;
    SDL_Rect textRect;
    SDL_Renderer* renderer;
    int score;

    FontScore(SDL_Renderer* renderer, TTF_Font* font, int fontSize, SDL_Color color);
    ~FontScore();

    void setScore(int newScore);
    void render();
};

#endif
