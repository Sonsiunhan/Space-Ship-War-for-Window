#include "../headers/menu.h"

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), selectedOption(0) {
    TTF_Init();
    font = TTF_OpenFont("../assets/font/ProtestGuerrilla-Regular.ttf", 20); // Thay bằng font của bạn
    intro = IMG_LoadTexture(renderer, "../assets/background/intro.png");
}

Menu::~Menu() {
    TTF_CloseFont(font);
    TTF_Quit();
}

void Menu::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    const char* text = "Press Enter to Start";
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, white);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    int w, h;
    SDL_QueryTexture(intro, nullptr, nullptr, &w, &h);
    SDL_Rect destRect = {0, 0, w, h};

    SDL_RenderCopy(renderer, intro, nullptr, &destRect);
    alpha_mod(renderer, tex);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
    SDL_RenderPresent(renderer);
}

int Menu::check(SDL_Event& e) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return 0;
        } 
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
            return 2; // Thoát menu và vào game
        }
    }
    return 1;
}

void Menu::alpha_mod(SDL_Renderer* renderer, SDL_Texture* texture){
    static int alpha = 0, deltaAlpha = 5;   // Độ đậm và giá trị thay đổi của độ đậm
    static Uint32 lastTime = 0;             // Thời gian đã được lưu trước đó 
    Uint32 currentTime = SDL_GetTicks();    // Lấy thời gian hiện tại
    SDL_SetTextureAlphaMod(texture, alpha);     // Set độ đậm
    
    if(currentTime - lastTime >= 16){
        alpha += deltaAlpha;        
        if(alpha <= 0 || alpha >= 255){
            deltaAlpha = - deltaAlpha;
        }
        lastTime = currentTime;
    }

    int text_intro_width, text_intro_height;
    SDL_QueryTexture(texture, NULL, NULL, &text_intro_width, &text_intro_height);
    SDL_Rect rect_intro = {(SCREEN_WIDTH - text_intro_width) / 2, SCREEN_HEIGHT - text_intro_height - 20, text_intro_width, text_intro_height};
    SDL_RenderCopy(renderer, texture, NULL, &rect_intro);
}