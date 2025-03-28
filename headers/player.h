#ifndef PLAYER_H
#define PLAYER_H

#include "../headers/common.h"
#include "../headers/bullet.h"
#include "../headers/item.h"
#include <cmath>

using namespace std;
struct Player {
    SDL_Texture* texture = nullptr;                 // Ảnh của người chơi
    SDL_Texture* turboTexture = nullptr;            // Ảnh của động cơ 
    SDL_Rect pos;                                   // Hộp của người chơi
    SDL_Rect turboPos;                              // Hộp của động cơ 
    vector<Bullet> bullets;                         // Đạn của người choi
    SDL_Texture* bulletTexture = nullptr;           // Ảnh đạn của người chơi
    bool destroyed = false;                         // Kiểm tra người chơi đã bị tiêu diệt chưa
    float bulletSpeed = 5.0f;
    float shootTime = 300;
    int level = 1;

    Player();              
    void init(SDL_Renderer* renderer, SDL_Texture* playerTexture, SDL_Texture* bulletTexture, SDL_Texture* _bulletTexture); // Hàm khởi tạo
    void handleInput(SDL_Event& event);             // Cách di chuyển
    void update();                                  // Cập nhật
    void render(SDL_Renderer* renderer);            // vẽ
    void shoot(SDL_Texture* bulletTexture);         // Người chơi bắn dndaj
    void checkCollisionWithItem(Item& item);

    void setDestroyed() { destroyed = true; }       // Đánh dấu bị tiêu diệt
    bool isDestroyed() const { return destroyed; }
    void reset();
};

#endif
