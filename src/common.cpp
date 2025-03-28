#include "../headers/common.h"

bool init(SDL_Window*& window, SDL_Renderer*& renderer, GameAssets& assets) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return false;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return false;
    if (TTF_Init() == -1) return false;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return false;

    window = SDL_CreateWindow("Space Ship War", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    assets.backgroundTexture;

    return true;
}

bool loadGameAssets(SDL_Renderer* renderer, GameAssets& assets) {
    assets.playerTexture = IMG_LoadTexture(renderer, "../assets/player/ship_4.png");
    assets.enemyTexture = IMG_LoadTexture(renderer, "../assets/enemies/ship_1.png");
    assets.enemyTexture_2 = IMG_LoadTexture(renderer, "../assets/enemies/ship_3.png");
    assets.bulletTexture = IMG_LoadTexture(renderer, "../assets/bullet/shoot.png");
    assets.turboTexture = IMG_LoadTexture(renderer, "../assets/player/turbo_blue.png");
    assets.enemyBulletTexture = IMG_LoadTexture(renderer, "../assets/bullet/laser-bolts.png");
    assets.high_score_path = "../assets/high_score.txt";
    assets.itemTexture = IMG_LoadTexture(renderer, "../assets/item_1.png");

    vector<string> backgroundPaths = {
        "../assets/background/Starry background  - Layer 01 - Solid colour.png",
        "../assets/background/Starry background  - Layer 02 - Shadows.png",
        "../assets/background/Starry background  - Layer 03 - Stars.png",
    };
    for (const auto& path : backgroundPaths) {
        SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
        if (!texture) {
            SDL_Log("Load img failed: %s", SDL_GetError());
            return false;
        }
        assets.backgroundTexture.push_back(texture);
    }
    
    vector<string> explosionPaths = {
        "../assets/explosion/destroy.png",
        "../assets/explosion/destroy2.png",
        "../assets/explosion/destroy3.png",
        "../assets/explosion/destroy4.png",
        "../assets/explosion/destroy5.png"
    };

    for (const auto& path : explosionPaths) {
        SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
        if (!texture) {
            SDL_Log("Load img failed: %s", SDL_GetError());
            return false;
        }
        assets.explosions.push_back(texture);
    }

    assets.font = TTF_OpenFont("../assets/ProtestGuerrilla-Regular.ttf", 20);
    if (!assets.font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }
    
    assets.font_high = TTF_OpenFont("../assets/ProtestGuerrilla-Regular.ttf", 20);
    if (!assets.font_high){
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }
    
    return true;
}

void handleEvents(bool& isRunning, SDL_Event &event,GameState& gameState) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        if(gameState == MENU && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN){
            gameState = PLAYING;
        }

        if(gameState == GAMEOVER && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r){
            gameState = MENU;
        }
    }
}

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}


void cleanUp(SDL_Window* window, SDL_Renderer* renderer, GameAssets& assets) {
    // Hủy kết cấu hình ảnh
    for(auto tex : assets.backgroundTexture){
        SDL_DestroyTexture(tex);
    }
    SDL_DestroyTexture(assets.playerTexture);
    SDL_DestroyTexture(assets.bulletTexture);
    SDL_DestroyTexture(assets.turboTexture);
    SDL_DestroyTexture(assets.enemyTexture);
    SDL_DestroyTexture(assets.enemyTexture_2);
    SDL_DestroyTexture(assets.enemyBulletTexture);
    

    // Hủy phông chữ
    TTF_CloseFont(assets.font);
    TTF_CloseFont(assets.font_high);
    assets.font = nullptr;
    assets.font_high = nullptr;


    // Hủy renderer và window
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    // Dừng SDL Mixer, TTF và SDL
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


