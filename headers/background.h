#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../headers/common.h"

using namespace std;

struct Background {
    vector<SDL_Texture*> textures; // Danh sách texture của background
    vector<float> pos = {0, 0, 0}; // Vị trí của từng layer
    int h = 0, w = 0;
    vector<float> scrollSpeed = {0.02f, 0.02f, 0.06f}; // Tốc độ cuộn nền


    Background() {}
    void initBackground(SDL_Renderer* renderer, const vector<SDL_Texture*>& bgTextures);
    void update();
    void render(SDL_Renderer* renderer);
};

#endif
