#pragma once
#include "SDL_ttf.h"
#include <string>
#include "fish.h"

using namespace std;

class base_text
{
protected:
	SDL_Renderer* renderer = nullptr;
	TTF_Font* gFont;
	SDL_Rect pos;
	SDL_Color textColor = { 0, 0, 0 };
public:
	virtual void show(string TEXT, int x, int y, int size) = 0;
};

class text : public base_text
{
public:
	text() {};
	text(SDL_Renderer* base_renderer)
	{
		renderer = base_renderer;
	}
	void show(string TEXT, int x, int y, int size)
	{
		gFont = TTF_OpenFont("2.ttf", size);
		SDL_Surface* textSurface = nullptr;
		textSurface = TTF_RenderUTF8_Solid(gFont, TEXT.c_str(), textColor);
		SDL_Texture* mTexture;
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
		int iW, iH;
		SDL_QueryTexture(mTexture, NULL, NULL, &iW, &iH);
		pos.x = x;
		pos.y = y;
		pos.w = iW;
		pos.h = iH;
		SDL_SetRenderTarget(renderer, mTexture);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderCopy(renderer, mTexture, NULL, &pos);
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		TTF_CloseFont(gFont);
	}
};

class menu_text : public base_text
{
private:
		SDL_Rect button;
public:
	menu_text(SDL_Renderer* base_renderer) 
	{
		renderer = base_renderer;
	}
	bool click(int x, int y)
	{
		if (x >= button.x && x <= button.x + button.w && y >= button.y && y <= button.y + button.h)
			return 1;
		else
			return 0;
	}
	void show(string TEXT, int x, int y, int size)
	{
		gFont = TTF_OpenFont("2.ttf", size);
		SDL_Surface* textSurface = nullptr;
		textSurface = TTF_RenderUTF8_Solid(gFont, TEXT.c_str(), textColor);
		SDL_Texture* mTexture;
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
		int iW, iH;
		SDL_QueryTexture(mTexture, NULL, NULL, &iW, &iH);
		pos.x = x;
		pos.y = y;
		pos.w = iW;
		pos.h = iH;
		button.x = x - 6;
		button.y = y;
		button.w = iW + 12;
		button.h = iH + 8;
		SDL_SetRenderTarget(renderer, mTexture);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &button);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderDrawRect(renderer, &button);
		SDL_RenderCopy(renderer, mTexture, NULL, &pos);
		TTF_CloseFont(gFont);
	}
};