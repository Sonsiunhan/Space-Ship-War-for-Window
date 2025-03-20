#include "../headers/high_score.h"

HighScore::HighScore(SDL_Renderer* renderer) : renderer(renderer) {}

int HighScore::loadHighScore(const string& path) {
    ifstream file(path);
    int highScore = 0;
    if (file >> highScore) {
        return highScore;
    }

    return 0; // Nếu file không tồn tại hoặc lỗi, trả về 0
}

void HighScore::saveHighScore(const string& path, int score) {
    ofstream file(path);
    if (file) {
        file << score;
    }
}

void HighScore::CreateTex(int& highScore){
    string scoreText = "High Score: " + to_string(highScore);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), white);
    if (!textSurface) {
        SDL_Log("Failed to render text: %s", TTF_GetError());
        return;
    }

    // Tạo texture từ surface
    tex = SDL_CreateTextureFromSurface(renderer, textSurface);
    pos = {0, 30, textSurface->w, textSurface->h}; // Đặt vị trí ở góc trên bên trái

    SDL_FreeSurface(textSurface);

}

void HighScore::render(SDL_Renderer* renderer){

    SDL_RenderCopy(renderer, tex, nullptr, &pos);
}