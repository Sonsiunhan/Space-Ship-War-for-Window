#include "../headers/player.h"

Player::Player() {
    pos = {0, 0, 0, 0}; // Kích thước mặc định của máy bay
}

void Player::init(SDL_Renderer* renderer, SDL_Texture* playerTexture, SDL_Texture* _bulletTexture, SDL_Texture* _turboTexture) {
    texture = playerTexture;
    bulletTexture = _bulletTexture;
    turboTexture = _turboTexture;
    int texW, texH;
    SDL_QueryTexture(playerTexture, nullptr, nullptr, &texW, &texH);

    pos = {(SCREEN_WIDTH - texW) / 2, SCREEN_HEIGHT - texH, texW, texH};
    turboPos = {(SCREEN_WIDTH - texW) / 2, SCREEN_HEIGHT - texH - 10, 10, 15};
    
    // Ẩn con trỏ chuột
    SDL_ShowCursor(SDL_DISABLE);
}

void Player::handleInput(SDL_Event& event) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    pos.x = mouseX - pos.w / 2;
    pos.y = mouseY - pos.h / 2;
    turboPos.x = pos.x + pos.w / 2 - turboPos.w / 2;
    turboPos.y = pos.y + pos.h;
}


void Player::update() {
    // Giới hạn máy bay không ra khỏi màn hình
    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;
    if (pos.x + pos.w > SCREEN_WIDTH) pos.x = SCREEN_WIDTH - pos.w;
    if (pos.y + pos.h > SCREEN_HEIGHT) pos.y = SCREEN_HEIGHT - pos.h;

    turboPos.x = pos.x + pos.w / 2 - turboPos.w / 2;
    turboPos.y = pos.y + pos.h;

    // Giảm thời gian chờ giữa các lần bắn
    static Uint32 lastShootTime = 0;
    Uint32 currentTime = SDL_GetTicks(); // Lấy thời gian hiện tại

    if (currentTime - lastShootTime >= shootTime) { // Bắn
        shoot(bulletTexture);
        lastShootTime = currentTime; // Cập nhật thời điểm bắn gần nhất
    }

    for (auto& bullet : bullets) {
        bullet.update();
    }

    // Xóa đạn nếu nó ra khỏi màn hình
    bullets.erase(remove_if(bullets.begin(), bullets.end(),
                 [](Bullet& b) { return b.isOffScreen(SCREEN_HEIGHT); }), bullets.end());
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &pos);
    SDL_RenderCopy(renderer, turboTexture, nullptr, &turboPos);
    for (auto& bullet : bullets) {
        bullet.render(renderer);
    }
}

void Player::shoot(SDL_Texture* bulletTexture) {
    if(level == 1)
	   bullets.emplace_back(bulletTexture, pos.x + pos.w / 2 - 5, pos.y, 0, 10, 20, - bulletSpeed, true);
    else if(level == 2){
        bullets.emplace_back(bulletTexture, pos.x + pos.w / 2, pos.y, 0, 10, 20, - bulletSpeed, true);
        bullets.emplace_back(bulletTexture, pos.x + pos.w / 2 - 10, pos.y, 0, 10, 20, - bulletSpeed, true);
    }
     else if (level == 3) {
        bullets.emplace_back(bulletTexture, pos.x + pos.w / 2 - 5, pos.y, 0, 10, 20, - bulletSpeed, true); // Thẳng
        bullets.emplace_back(bulletTexture, pos.x + pos.w / 2 - 15, pos.y, -  M_PI / 6, 10, 20, - bulletSpeed, true); // Chéo trái
        bullets.emplace_back(bulletTexture, pos.x + pos.w / 2 + 5, pos.y, M_PI / 6, 10, 20, - bulletSpeed, true); // Chéo phải
    }
}

void Player::checkCollisionWithItem(Item& item) {
    if (!item.active) 
        return;  // Nếu item không hoạt động, bỏ qua

    SDL_Rect itemRect = item.destRect;  // Lấy hitbox của item

    if (SDL_HasIntersection(&pos, &itemRect)) {  
        bulletSpeed *= 1.5f;  // Tăng tốc độ đạn lên 1.5 lần
        item.active = false;  // Ẩn item đi sau khi va chạm
        shootTime *= 0.9f;

        if(level != 3 && bulletSpeed > 30.0f){
            bulletSpeed = 5.0f;
            level++;
        }
        if(level >= 3)
            level = 3;
    }
}
