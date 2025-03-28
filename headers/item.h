#ifndef ITEM_H
#define ITEM_H

#include "../headers/common.h"
#include <cstdlib>
#include <ctime>

struct Item {
    SDL_Texture* texture;
    SDL_Rect destRect;
    float ySpeed;
    float rotationAngle;
    float rotationSpeed;
    bool active;
    Uint32 lastSpawnTime;
    Uint32 spawnInterval;

    Item(SDL_Renderer* renderer, SDL_Texture* texture);
    void update();
    void render(SDL_Renderer* renderer);
    bool isOffScreen() const;
    void resetPos();
    void reset();
};

#endif
