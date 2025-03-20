#include "../headers/background.h"

void Background::initBackground(SDL_Renderer* renderer, const vector<SDL_Texture*>& bgTextures) {
    textures = bgTextures;
    int texture_width, texture_height;
    SDL_QueryTexture(textures[0], NULL, NULL, &texture_width, &texture_height); // Lấy giá trị
    float texture_width_new = SCREEN_WIDTH, texture_height_new = (float)SCREEN_WIDTH * texture_height / texture_width;
    h = (int)texture_height_new;
    w = (int)texture_width_new;
}


void Background::update() {
    for (size_t i = 0; i < pos.size(); ++i) {
        pos[i] += scrollSpeed[i]; // Di chuyển xuống

        // Nếu layer đã đi qua màn hình, đưa nó lên lại phía trên
        if (pos[i] >= SCREEN_HEIGHT) {
            pos[i] = pos[i] - h;
        }
    }
}


void Background::render(SDL_Renderer* renderer) {
    for (size_t i = 0; i < pos.size(); ++i) {

        // Vẽ hình ảnh đầu tiên
        SDL_Rect destRect1 = {0, (int)pos[i], SCREEN_WIDTH, (int)h};
        SDL_RenderCopy(renderer, textures[i], NULL, &destRect1);

        // Vẽ hình ảnh thứ hai để đảm bảo không có khoảng trống
        SDL_Rect destRect2 = {0, (int)pos[i] - (int)h, SCREEN_WIDTH, (int)h};
        SDL_RenderCopy(renderer, textures[i], NULL, &destRect2);
    }
}
