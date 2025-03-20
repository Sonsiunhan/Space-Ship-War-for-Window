#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include "../headers/common.h"
#include <fstream>

using namespace std;

struct HighScore
{
    TTF_Font* font = nullptr;         // font chữ của điểm cao nhất
    SDL_Rect pos;           // Hộp của tex
    SDL_Texture* tex = nullptr;
    SDL_Renderer* renderer = nullptr;

    HighScore(SDL_Renderer* renderer);
    int loadHighScore(const string& path);
    void saveHighScore(const string& path, int score);
    void CreateTex(int& highScore);
    void render(SDL_Renderer* renderer);
};
#endif