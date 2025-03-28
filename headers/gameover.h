#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "../headers/common.h"

using namespace std;

struct GameOver
{
	SDL_Renderer* renderer;

	SDL_Texture* texture;
	SDL_Texture* textTexture;
	SDL_Rect pos;
	SDL_Rect textPos;
	TTF_Font* font;


	GameOver(SDL_Renderer* renderer);
	void your_score(const int& highScore, int& score);
	void new_high_score(const int& highScore);
	void restart();
	void render();
};


#endif // GAMEOVER_H
