#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <algorithm>

const int SCREEN_HEIGHT = 560;
const int SCREEN_WIDTH = 800;
const SDL_Color white = {255, 255, 255, 255};
const Uint32 speedIncreaseInterval = 1000; // Mỗi 5 giây tăng tốc một lần


using namespace std;

struct GameAssets {
    SDL_Texture* playerTexture = nullptr;
    SDL_Texture* turboTexture = nullptr;
    SDL_Texture* enemyTexture = nullptr;
    SDL_Texture* enemyTexture_2 = nullptr;
    SDL_Texture* bulletTexture = nullptr;
    SDL_Texture* enemyBulletTexture = nullptr;
    SDL_Texture* itemTexture = nullptr;

    vector<SDL_Texture*> explosions;
    vector<SDL_Texture*> backgroundTexture;

    TTF_Font* font_high = nullptr;
    TTF_Font* font = nullptr;
    string high_score_path = "";

    Mix_Music* bgm = nullptr;
    Mix_Chunk* shootSound = nullptr;
};

struct GameState {
    bool isRunning = true;
    int score = 0;
    int playerHP = 4;
};

bool init(SDL_Window*& window, SDL_Renderer*& renderer, GameAssets& assets);
bool loadGameAssets(SDL_Renderer* renderer, GameAssets& assets);
void handleEvents(GameState& state, SDL_Event &event);
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
void cleanUp(SDL_Window* window, SDL_Renderer* renderer, GameAssets& assets);

#endif