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
#include "../headers/gameover.h"

using namespace std;

const int FPS = 60;
const float frameDelay = 1000 / FPS; // Khoảng thời gian mỗi frame

Uint32 frameStart;
int frameTime;

GameState gameState = MENU;   
bool isRunning = true;

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

void resetGame(Player& son, EnemyManager& enemy_manager, EnemyManager& enemy_manager_2, Item& item){
    son.reset();
    enemy_manager.reset();
    enemy_manager_2.reset();
    item.reset();
}

int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    GameAssets assets;                  // Tài nguyên game 

    if (!init(window, renderer, assets)) 
        return 1;          // Kiểm tra khởi tạo của bị lỗi không
    if(!loadGameAssets(renderer, assets))                   // Kiểm tra tài nguyên game có lỗi không
        return 1;

    Menu menu(renderer);

    Background background;          // Khai báo background
    background.initBackground(renderer, assets.backgroundTexture);          // Khởi tạo
    
    Player son;             // Khởi tạo người chơi
    son.init(renderer, assets.playerTexture, assets.bulletTexture, assets.turboTexture);        // Nhập dữ liệu vào 

    EnemyManager enemy_manager(renderer, 1);             // Khởi tạo quản lí kẻ địch
    EnemyManager enemy_manager_2(renderer, 2); 

    enemy_manager.enemyTexture = assets.enemyTexture;       // Nhập vào ảnh của kẻ địch
    enemy_manager.bulletTex = assets.enemyBulletTexture;         // Nhập vào ảnh của đạn kẻ địch

    enemy_manager_2.enemyTexture = assets.enemyTexture_2;
    enemy_manager_2.bulletTex = assets.enemyBulletTexture;

    FontScore font_score(renderer, assets.font, 24, white);         // Số điểm của người chơi

    int score = 0;

    HighScore HiSc(renderer);
    HiSc.font = assets.font_high;
    int highScore = HiSc.loadHighScore(assets.high_score_path);
    HiSc.CreateTex(highScore);

    GameOver game_over(renderer);

    Mix_Chunk* bulletSound = Mix_LoadWAV("../assets/shoot.wav");
    Bullet::setFireSound(bulletSound);

    Explosion explosion(
        assets.explosions[0],
        assets.explosions[1],
        assets.explosions[2],
        assets.explosions[3],
        assets.explosions[4],
        -1, -1, 0, 0
    );

    SDL_Event event;
    Item item(renderer, assets.itemTexture);
                 
    bool newHigh = false;
    while (isRunning) {
        frameStart = SDL_GetTicks(); // Lấy thời gian bắt đầu frame
        handleEvents(isRunning, event, gameState);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (gameState){
            case MENU:
                menu.render();
                score = 0;
                newHigh = false;
                break;

            case PLAYING:{
                SDL_ShowCursor(SDL_DISABLE);
                background.render(renderer);
                background.update();

                font_score.setScore(score);
                font_score.render();
                
                if(score > highScore){
                    HiSc.CreateTex(score);
                    highScore = score;
                    newHigh = true;
                }
                HiSc.render(renderer);

                son.handleInput(event);
                son.update();
                son.render(renderer);

                ene(enemy_manager, renderer, son, assets, score, explosion);
                ene(enemy_manager_2, renderer, son, assets, score, explosion);

                item.update();
                item.render(renderer);
                son.checkCollisionWithItem(item);
                if(enemy_manager.checkCollisions(son.pos) || enemy_manager.checkPlayerEnemyCollision(son) ||
                    enemy_manager_2.checkCollisions(son.pos) || enemy_manager_2.checkPlayerEnemyCollision(son)){
                    gameState = GAMEOVER;
                }
                break;
            }
            case GAMEOVER:
                game_over.render();
                game_over.restart();

                if(!newHigh){
                    game_over.your_score(highScore, score);
                }
                else
                    game_over.new_high_score(highScore);

                HiSc.saveHighScore(assets.high_score_path, highScore);
                resetGame(son, enemy_manager, enemy_manager_2, item);
                SDL_ShowCursor(SDL_ENABLE);
                break;

        }
        
        SDL_RenderPresent(renderer);

        // Giới hạn FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime); // Đợi đến khi đủ thời gian của 1 frame
        }
    }

    cleanUp(window, renderer, assets);

    return 0;
}