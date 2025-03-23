#ifndef BULLET_H
#define BULLET_H

#include "../headers/common.h"
#include <cmath>

struct Bullet {
    SDL_Texture* bulletTexture;  // Texture của viên đạn
    SDL_Rect pos;          // Vị trí và kích thước
    float realY;                // vị trí thật của đạn
    float realX;
    float speed;             // Tốc độ di chuyển
    float vx, vy;
    static Mix_Chunk* fireSound;
    bool isPlayerBullet;

    Bullet(SDL_Texture* tex, int x, int y, float angle, int w, int h, float spd, bool isPlayer);    // khởi tạo
    void update();                  // cập nhật
    static void setFireSound(Mix_Chunk* sound);
    void render(SDL_Renderer* renderer);            // vẽ
    bool isOffScreen(int screenHeight);             // Kiểm tra xem đạn ra khỏi màn hình chưa
    SDL_Rect getPos() const { return pos;}              // trả về hộp của đạn
};

#endif
