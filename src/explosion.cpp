#include "../headers/explosion.h"

Explosion::Explosion(SDL_Texture* tex1, SDL_Texture* tex2, SDL_Texture* tex3, SDL_Texture* tex4, SDL_Texture* tex5, int x, int y, int size, int delay) 
    : currentFrame(0), frameDelay(delay), frameCounter(0), finished(false) {
    
    textures.push_back(tex1);
    textures.push_back(tex2);
    textures.push_back(tex3);
    textures.push_back(tex4);
    textures.push_back(tex5);

    destRect = {x, y, size, size}; // Kích thước vụ nổ
}

void Explosion::update() {
    if (finished) return;

    frameCounter++;
    if (frameCounter >= frameDelay) {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame >= 5) {
            finished = true;
        }
    }
}


void Explosion::render(SDL_Renderer* renderer) {
    if (!finished) {
        SDL_RenderCopy(renderer, textures[currentFrame], nullptr, &destRect);
    }
}

bool Explosion::isFinished() const {
    return finished;
}
