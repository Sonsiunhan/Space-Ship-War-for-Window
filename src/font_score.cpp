#include "../headers/font_score.h"

FontScore::FontScore(SDL_Renderer* renderer, TTF_Font* font, int fontSize, SDL_Color color)
    : renderer(renderer), color(color), textTexture(nullptr), score(0), font(font) {}

FontScore::~FontScore() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    TTF_CloseFont(font);
}

void FontScore::setScore(int newScore) {
    score = newScore;

    // Xóa texture cũ nếu có
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    // Chuyển số điểm thành chuỗi
    std::string scoreText = "Score: " + std::to_string(score);

    // Tạo surface từ font
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    if (!textSurface) {
        SDL_Log("Failed to render text: %s", TTF_GetError());
        return;
    }

    // Tạo texture từ surface
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = {0, 0, textSurface->w, textSurface->h}; // Đặt vị trí ở góc trên bên trái

    SDL_FreeSurface(textSurface);
}

void FontScore::render() {
    if (textTexture) {
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    }
}
