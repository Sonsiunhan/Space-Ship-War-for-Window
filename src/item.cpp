#include "../headers/item.h"

Item::Item(SDL_Renderer* renderer, SDL_Texture* texture)
    : texture(texture), active(false) {
    srand(time(0));
    resetPosition();
}

void Item::resetPosition() {
    destRect.x = rand() % (SCREEN_WIDTH - 60);
    destRect.y = -60;

    destRect.w = 60;
    destRect.h = 60;

    ySpeed = 2.0f + (rand() % 3);
    rotationAngle = 0.0f;
    rotationSpeed = 2.0f + (rand() % 5);

    active = true;
    lastSpawnTime = SDL_GetTicks();
    spawnInterval = 5000 + (rand() % 5000);
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
            resetPosition();
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
