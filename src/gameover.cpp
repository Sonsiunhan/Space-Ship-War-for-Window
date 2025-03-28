#include "../headers/gameover.h"

GameOver::GameOver(SDL_Renderer* renderer) : renderer(renderer) {
	texture = IMG_LoadTexture(renderer, "../assets/background/gameover.png");
	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	pos = {0, 0, w, h};

	font = TTF_OpenFont("../assets/ProtestGuerrilla-Regular.ttf", 30);

	const char* text = "Press 'R' to restart";
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, white);
	textTexture = SDL_CreateTextureFromSurface(renderer, surface);
	int _w = surface -> w, _h = surface -> h;
	textPos = {(SCREEN_WIDTH - _w) / 2, SCREEN_HEIGHT - _h, _w, _h};
}

void GameOver::your_score(const int& highScore, int& score){
	string text = "High Score: " + to_string(highScore);
	string text2 = "Your Score: " + to_string(score);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), white);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	int w1 = surface -> w, h1 = surface -> h;
	SDL_Rect textPos = {(SCREEN_WIDTH - w1) / 2, 450, w1, h1};
	SDL_FreeSurface(surface);

	SDL_Surface* surface2 = TTF_RenderText_Solid(font, text2.c_str(), white);
	SDL_Texture* tex2 = SDL_CreateTextureFromSurface(renderer, surface2);
	int w2 = surface2 -> w, h2 = surface2 -> h;
	SDL_Rect textPos2 = {(SCREEN_WIDTH - w2) / 2, 500, w2, h2};
	SDL_FreeSurface(surface2);

	SDL_RenderCopy(renderer, tex, nullptr, &textPos);
	SDL_RenderCopy(renderer, tex2, nullptr, &textPos2);
}

void GameOver::new_high_score(const int& highScore){
	string text = "New High Score: " + to_string(highScore);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), white);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	int w = surface -> w, h = surface -> h;
	SDL_Rect textPos = {(SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2, w, h};
	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, tex, nullptr, &textPos);
}

void GameOver::restart(){
	static int alpha = 0, deltaAlpha = 5;
	static Uint32 lastTime = 0;
	Uint32 currentTime = SDL_GetTicks();

	SDL_SetTextureAlphaMod(textTexture, alpha);

	if(currentTime - lastTime >= 16){
		alpha += deltaAlpha;
		if(alpha <= 0 || alpha >= 255){
			deltaAlpha = - deltaAlpha;
		}
		lastTime = currentTime;
	}

	if(textTexture == nullptr)
		cout<< 1;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textPos);
}

void GameOver::render(){
	SDL_RenderCopy(renderer, texture, nullptr, &pos);
}
