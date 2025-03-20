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

using namespace std;

int main(int argc, char* argv[]) {

    while(true){
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        GameAssets assets;                  // Tài nguyên game 
        GameState state;

        if (!init(window, renderer, assets)) return 1;          // Kiểm tra khởi tạo của bị lỗi không

        if(!loadGameAssets(renderer, assets))                   // Kiểm tra tài nguyên game có lỗi không
            return 1;
        Menu menu(renderer);
        SDL_Event event;
        int showMenu = 1;

        while (showMenu == 1) {
            showMenu = menu.check(event);
            if(showMenu == 2)
                break;
            else if(showMenu == 0)
                return 0;
            menu.render();
            SDL_Delay(100);
        }

        Background background;          // Khai báo background
        background.initBackground(renderer, assets.backgroundTexture);          // Khởi tạo

        Player son;             // Khởi tạo người chơi
        son.init(renderer, assets.playerTexture, assets.bulletTexture, assets.turboTexture);        // Nhập dữ liệu vào 

        EnemyManager enemy_manager(renderer);             // Khởi tạo quản lí kẻ địch
        enemy_manager.enemyTexture = assets.enemyTexture;       // Nhập vào ảnh của kẻ địch
        enemy_manager.bulletTex = assets.enemyBulletTexture;         // Nhập vào ảnh của đạn kẻ địch

        FontScore font_score(renderer, assets.font, 24, white);         // Số điểm của người chơi
        int score = 0;

        HighScore HiSc(renderer);
        HiSc.font = assets.font_high;
        int highScore = HiSc.loadHighScore(assets.high_score_path);

        Mix_Chunk* bulletSound = Mix_LoadWAV("../assets/fire_sound/scifi-gun-shoot-1-266417.wav");
        Bullet::setFireSound(bulletSound);

        Explosion explosion(
            assets.explosions[0],
            assets.explosions[1],
            assets.explosions[2],
            assets.explosions[3],
            assets.explosions[4],
            -1, -1, 0, 0
        );

        bool alive = true;                  
        int cnt = 0;
        while (state.isRunning) {
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

            enemy_manager.update();
            enemy_manager.render();

            if(enemy_manager.checkCollisions(son.pos) || enemy_manager.checkPlayerEnemyCollision(son)){
                alive = 0;
                break;
            }

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

            cnt = 1;
            SDL_RenderPresent(renderer);
        }

        HiSc.saveHighScore(assets.high_score_path, highScore);
        cleanUp(window, renderer, assets);
    }

    return 0;
}