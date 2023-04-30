#pragma once
#include "GameManager.h"



class CustomText
{
public:
	SDL_Rect Transform;
	TTF_Font* font;
	SDL_Color color;
	string content;
	CustomText(TTF_Font* _font);
	~CustomText();

	void Render();
	void SetContent(string s);
	void SetPosition(int x, int y);

private:
	SDL_Surface* textSurface;
	SDL_Texture* textTex;

};


