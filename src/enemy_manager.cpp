#include "../headers/enemy_manager.h"


Uint32 lastSpeedIncreaseTime = 0;

EnemyManager::EnemyManager(SDL_Renderer* renderer) : renderer(renderer) {}

void EnemyManager::update() {
    Uint32 currentTime = SDL_GetTicks();

    // Kiểm tra nếu đã đến thời điểm tăng tốc
    if (currentTime - lastSpeedIncreaseTime >= speedIncreaseInterval) {
        lastSpeedIncreaseTime = currentTime;
        gameSpeed += 0.05f;  
        for(auto& enemy : enemies){
            enemy.speed += 0.05f;
        }
    }

    // Sinh enemy dựa trên tốc độ
    if (currentTime - lastSpawnTime >= spawnInterval / gameSpeed) {
        lastSpawnTime = currentTime;
        spawnEnemy(enemyTexture);
    }

    for (auto& enemy : enemies) {
        enemy.update();
        enemy.shoot(enemyBullets, bulletTex); // Truyền danh sách đạn chung
    }
    for (auto& bullet : enemyBullets){
        bullet.update();
    }

    // Cập nhật và xóa đạn enemy nếu cần
    enemyBullets.erase(remove_if(enemyBullets.begin(), enemyBullets.end(),
        [](Bullet& b) { return b.isOffScreen(SCREEN_HEIGHT); }), enemyBullets.end());

    // Xóa enemy đã bị tiêu diệt
    enemies.erase(remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) { return e.isDestroyed(); }), enemies.end());
}

void EnemyManager::render() {
    for (auto& enemy : enemies) {
        enemy.render(renderer);
    }
    for (auto& bullet : enemyBullets){
        bullet.render(renderer);
    }
}

void EnemyManager::spawnEnemy(SDL_Texture* enemyTexture) {
    enemies.emplace_back(enemyTexture, 1.0f); // Thêm enemy mới vào danh sách
}

bool EnemyManager::checkCollisions(SDL_Rect& target) {
    bool targetDestroyed = false;

    enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(),
        [&](Bullet& bullet) {
            if (checkCollision(bullet.getPos(), target)) {
                targetDestroyed = true;
                return true; // Xóa đạn khi va chạm
            }
            return false;
        }),
        enemyBullets.end());

    return targetDestroyed;
}


vector<int> EnemyManager::checkEnemyHit(vector<Bullet>& playerBullets) {
    int enemyDestroyed = 0;
    int _x = 0, _y = 0;

    playerBullets.erase(remove_if(playerBullets.begin(), playerBullets.end(), 
        [&](Bullet& bullet) {
            for (auto it = enemies.begin(); it != enemies.end(); ++it) {
                if (checkCollision(bullet.getPos(), it->getPos())) {
                    enemyDestroyed = 1;
                    _x = it->pos.x;
                    _y = it->pos.y;

                    enemies.erase(it); // Xóa enemy ngay lập tức
                    return true; // Xóa đạn của player
                }
            }
            return false;
        }), playerBullets.end());

    return {enemyDestroyed, _x, _y};
}


bool EnemyManager::checkPlayerEnemyCollision(Player& player) {
    bool collisionHappened = false;

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [&](Enemy& enemy) {
            if (checkCollision(enemy.getPos(), player.pos)) {
                player.setDestroyed();  // Đánh dấu player bị tiêu diệt
                collisionHappened = true;
                return true;  // Xóa enemy
            }
            return false;
        }), enemies.end());

    return collisionHappened;
}


