#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "../headers/common.h"

using namespace std;

struct Explosion {
    vector<SDL_Texture*> textures;  // 5 ảnh cho hiệu ứng nổ
    SDL_Rect destRect;
    int currentFrame;
    int frameDelay;
    int frameCounter;
    bool finished;

    Explosion();
    Explosion(SDL_Texture* tex1, SDL_Texture* tex2, SDL_Texture* tex3, SDL_Texture* tex4, SDL_Texture* tex5, int x, int y, int size, int delay);
    void update();
    void render(SDL_Renderer* renderer);
    bool isFinished() const;
};

#endif
