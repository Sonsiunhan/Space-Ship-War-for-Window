#include "../headers/enemy.h"
#include <ctime>
#include <windows.h>

Enemy::Enemy(SDL_Texture* tex, float speed)
    : texture(tex), speed(speed), lastShootTime(0) {
    LARGE_INTEGER li;
QueryPerformanceCounter(&li);
srand(static_cast<unsigned int>(li.QuadPart));
    SDL_QueryTexture(tex, nullptr, nullptr, &pos.w, &pos.h);

    pos.x = rand() % (SCREEN_WIDTH - pos.w);
    pos.y = -pos.h;
    realY = pos.y;
}

void Enemy::update() {
    realY += speed;
    pos.y = static_cast<int>(realY);
}


void Enemy::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &pos);
}

void Enemy::shoot(vector<Bullet>& enemyBullets, SDL_Texture* bulletTex) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastShootTime + 2000) { // Chờ 1 giây giữa mỗi lần bắn
        lastShootTime = currentTime;
        int bullet_w;
        SDL_QueryTexture(bulletTex, nullptr, nullptr, &bullet_w, nullptr);

        enemyBullets.emplace_back(bulletTex, pos.x + pos.w / 2 - bullet_w / 2, pos.y + pos.h, 10, 20, -0.1f, false);
    }
}
