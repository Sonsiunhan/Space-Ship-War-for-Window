#include "../headers/item.h"

Item::Item(SDL_Renderer* renderer, SDL_Texture* texture)
    : texture(texture), active(false) {
    srand(time(0));
    resetPos();
}

void Item::resetPos() {
    destRect.x = rand() % (SCREEN_WIDTH - 90);
    destRect.y = -30;

    destRect.w = 36;
    destRect.h = 22;

    ySpeed = 2.0f + (rand() % 3);
    rotationAngle = 0.0f;
    rotationSpeed = 2.0f + (rand() % 5);

    active = true;
    lastSpawnTime = SDL_GetTicks();
    spawnInterval = 20000 + (rand() % 5000);
}

void Item::update() {
    if (active) {
        destRect.y += ySpeed;
        rotationAngle += rotationSpeed;
        
        if (isOffScreen()) {
            active = false;
            lastSpawnTime = SDL_GetTicks();
        }
    } else {
        if (SDL_GetTicks() - lastSpawnTime > spawnInterval) {
            resetPos();
        }
    }
}

void Item::render(SDL_Renderer* renderer) {
    if (active) {
        SDL_RenderCopyEx(renderer, texture, nullptr, &destRect, rotationAngle, nullptr, SDL_FLIP_NONE);
    }
}

bool Item::isOffScreen() const {
    return destRect.y > SCREEN_HEIGHT;
}

void Item::reset(){
    active = false;
}