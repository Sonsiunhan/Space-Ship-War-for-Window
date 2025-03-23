#include "../headers/bullet.h"

Mix_Chunk* Bullet::fireSound = nullptr;

Bullet::Bullet(SDL_Texture* tex, int x, int y, float angle, int w, int h, float spd, bool isPlayer, int bulletCount)
    : bulletTexture(tex), speed(spd), realX(x) ,realY(y), isPlayerBullet(isPlayer) {
    pos = {x, y, w, h};

    vx = sin(angle) * speed;  // Tính vận tốc theo trục x
    vy = cos(angle) * speed;  // Tính vận tốc theo trục y

    if (fireSound && isPlayerBullet && bulletCount == 1) {
        Mix_PlayChannel(-1, fireSound, 0);
    }
}

void Bullet::update() {
    realX -= vx; // Cập nhật vị trí x dựa trên vận tốc vx
    realY += vy; // Cập nhật vị trí y dựa trên vận tốc vy

    pos.x = static_cast<int>(realX); 
    pos.y = static_cast<int>(realY);
}

void Bullet::setFireSound(Mix_Chunk* sound) {
    fireSound = sound;
}

void Bullet::render(SDL_Renderer* renderer) {
    float angle = atan2(-vy, vx) * 180.0 / M_PI - 90;

    SDL_RenderCopyEx(renderer, bulletTexture, NULL, &pos, angle, NULL, SDL_FLIP_NONE);
}

bool Bullet::isOffScreen(int screenHeight) {
    bool offScreen = pos.y + pos.h < 0 || pos.y > screenHeight;
        return offScreen;
}
