#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "../headers/common.h"
#include "../headers/enemy.h"
#include "../headers/player.h"
#include "../headers/explosion.h"

using namespace std;

struct EnemyManager {
    vector<Enemy> enemies;                  // Lưu tất cả enemy 
    vector<Bullet> enemyBullets;            // Lưu tất cả đạn của enemy

    Uint32 spawnInterval = 1500;            // Thời gian tạo ra enemy 
    Uint32 lastSpawnTime = 0; 
    float gameSpeed = 1.0f;     
    int hp;    
  
    SDL_Texture* enemyTexture = nullptr;            // Ảnh của enemy
    SDL_Texture* bulletTex = nullptr;               // Ảnh của đạn
    SDL_Renderer* renderer = nullptr;

    EnemyManager(SDL_Renderer* renderer, int hp);
    void update();                              // cập nhật
    void render();            // vẽ
    bool checkCollisions(SDL_Rect &target);         // Kiểm tra va chạm của đạn của địch và người chơi
    void spawnEnemy(SDL_Texture* enemyTexture);             // Sinh ra kẻ địch
    vector<int> checkEnemyHit(vector<Bullet>& playerBullets);      // Kiểm tra va chạm của đạn người chơi và kẻ địch
    bool checkPlayerEnemyCollision(Player& player);         // Kiểm tra va chạm của người chơi và kẻ địch
    void reset();
};


#endif
