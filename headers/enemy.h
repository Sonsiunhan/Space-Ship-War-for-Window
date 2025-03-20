#ifndef ENEMY_H
#define ENEMY_H

#include "../headers/common.h"
#include "../headers/bullet.h"

using namespace std;

struct Enemy {
    SDL_Texture* texture;       // Hình ảnh của enemy 
    SDL_Rect pos;               // Hộp của enemy 
    float speed;                // Tốc độ của enemy 
    float realY;                // Vị trí thật
    bool destroyed = false;         // Kiểm tra đã bị tiêu diệt chưa
    Uint32 lastShootTime;           // Thời gian cũ đã tạo ra 

    Enemy(SDL_Texture* tex, float speed);       // Khởi tạo
    void update();                              // Cập nhật 
    void render(SDL_Renderer* renderer);                // Vẽ
    void shoot(vector<Bullet>& enemyBullets, SDL_Texture* bulletTex);
    SDL_Rect getPos() const { return pos; }             // Trả về giá trị vị trí
    void setDestroyed() { destroyed = true; } // Đánh dấu enemy bị tiêu diệt       
    bool isDestroyed() const { return destroyed; }
};

#endif
