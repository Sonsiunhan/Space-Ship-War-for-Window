#include "../headers/background.h"
#include "../headers/common.h"
#include "../headers/player.h"
#include "../headers/bullet.h"
#include "../headers/enemy.h"
#include "../headers/enemy_manager.h"
#include "../headers/font_score.h"
#include "../headers/high_score.h"
#include "../headers/explosion.h"
#include "../headers/menu.h"
#include "../headers/item.h"

using namespace std;

const int FPS = 60;
const float frameDelay = 1000 / FPS; // Khoảng thời gian mỗi frame

Uint32 frameStart;
int frameTime;

void ene(EnemyManager& enemy_manager, SDL_Renderer* renderer, Player& son, GameAssets assets, int& score, Explosion& explosion){
    enemy_manager.update();
    enemy_manager.render();

    vector<int> tmp = enemy_manager.checkEnemyHit(son.bullets);
    if (tmp[0] != 0) {
        score += 100;
        Explosion _explosion(
            assets.explosions[0],
            assets.explosions[1],
            assets.explosions[2],
            assets.explosions[3],
            assets.explosions[4],
            tmp[1], tmp[2], 64, 5
        );
        explosion = _explosion;
    }

    if(explosion.destRect.x >= 0){
        explosion.update();
        explosion.render(renderer);
    }
}


int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    GameAssets assets;                  // Tài nguyên game 
    GameState state;

    if (!init(window, renderer, assets)) 
        return 1;          // Kiểm tra khởi tạo của bị lỗi không
    if(!loadGameAssets(renderer, assets))                   // Kiểm tra tài nguyên game có lỗi không
        return 1;

    // while(true){
        Menu menu(renderer);
        SDL_Event event;
        int showMenu = 1;

        while (showMenu == 1) {
            frameStart = SDL_GetTicks();
            showMenu = menu.check(event);
            if(showMenu == 2)
                break;
            else if(showMenu == 0)
                return 0;
            menu.render();

            frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < frameDelay) {
                SDL_Delay(frameDelay - frameTime); // Đợi đến khi đủ thời gian của 1 frame
            }
        }

        Background background;          // Khai báo background
        background.initBackground(renderer, assets.backgroundTexture);          // Khởi tạo

        Player son;             // Khởi tạo người chơi
        son.init(renderer, assets.playerTexture, assets.bulletTexture, assets.turboTexture);        // Nhập dữ liệu vào 

        EnemyManager enemy_manager(renderer, 1);             // Khởi tạo quản lí kẻ địch
        enemy_manager.enemyTexture = assets.enemyTexture;       // Nhập vào ảnh của kẻ địch
        enemy_manager.bulletTex = assets.enemyBulletTexture;         // Nhập vào ảnh của đạn kẻ địch

        EnemyManager enemy_manager_2(renderer, 2);
        enemy_manager_2.enemyTexture = assets.enemyTexture_2;
        enemy_manager_2.bulletTex = assets.enemyBulletTexture;

        FontScore font_score(renderer, assets.font, 24, white);         // Số điểm của người chơi
        int score = 0;

        HighScore HiSc(renderer);
        HiSc.font = assets.font_high;
        int highScore = HiSc.loadHighScore(assets.high_score_path);

        Mix_Chunk* bulletSound = Mix_LoadWAV("../assets/scifi-gun-shoot-1-266417.wav");
        Bullet::setFireSound(bulletSound);

        Explosion explosion(
            assets.explosions[0],
            assets.explosions[1],
            assets.explosions[2],
            assets.explosions[3],
            assets.explosions[4],
            -1, -1, 0, 0
        );

        Item item(renderer, assets.itemTexture);
        bool alive = true;                  
        int cnt = 0;
        while (state.isRunning && alive) {
            frameStart = SDL_GetTicks(); // Lấy thời gian bắt đầu frame
            handleEvents(state, event);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            background.render(renderer);
            background.update();

            font_score.setScore(score);
            font_score.render();
            
            if(cnt == 0){
                HiSc.CreateTex(highScore);
            }
            if(score > highScore){
                HiSc.CreateTex(score);
                highScore = score;
            }
            HiSc.render(renderer);

            if(alive == true){
                son.handleInput(event);
                son.update();
                son.render(renderer);
            }


            ene(enemy_manager, renderer, son, assets, score, explosion);
            ene(enemy_manager_2, renderer, son, assets, score, explosion);

            item.update();
            item.render(renderer);
            son.checkCollisionWithItem(item);
            if(enemy_manager.checkCollisions(son.pos) || enemy_manager.checkPlayerEnemyCollision(son) ||
               enemy_manager_2.checkCollisions(son.pos) || enemy_manager_2.checkPlayerEnemyCollision(son)){
                alive = 0;
            }

            cnt = 1;
            SDL_RenderPresent(renderer);

            // Giới hạn FPS
            frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < frameDelay) {
                SDL_Delay(frameDelay - frameTime); // Đợi đến khi đủ thời gian của 1 frame
            }
        }

        HiSc.saveHighScore(assets.high_score_path, highScore);
        enemy_manager.gameSpeed = 1.0f;
        enemy_manager_2.gameSpeed = 1.0f;

    // }
    cleanUp(window, renderer, assets);

    return 0;
}