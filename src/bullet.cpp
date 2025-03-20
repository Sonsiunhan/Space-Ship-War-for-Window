#include "../headers/bullet.h"

Mix_Chunk* Bullet::fireSound = nullptr;

Bullet::Bullet(SDL_Texture* tex, int x, int y, int w, int h, float spd, bool isPlayer)
    : bulletTexture(tex), speed(spd), realY(y), isPlayerBullet(isPlayer) {
    pos = {x, y, w, h};

    if (fireSound && isPlayerBullet) {
        Mix_PlayChannel(-1, fireSound, 0);
    }
}

void Bullet::update() {
    realY -= speed;
    pos.y = static_cast<int>(realY);
}

void Bullet::setFireSound(Mix_Chunk* sound) {
    fireSound = sound;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, bulletTexture, nullptr, &pos);
}

bool Bullet::isOffScreen(int screenHeight) {
    bool offScreen = pos.y + pos.h < 0 || pos.y > screenHeight;
        return offScreen;
}
