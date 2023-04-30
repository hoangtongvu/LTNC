#include "CustomText.h"


CustomText::CustomText(TTF_Font* _font)
{
	Transform = { 0, 0, 0, 0 };
	color = { 255, 255, 255 };
	font = _font;
	content = "";
	textSurface = NULL;
	textTex = NULL;
}

CustomText::~CustomText()
{
}


void CustomText::Render()
{
	/*if (textSurface == NULL)
	{
		return;
	}*/
	SDL_RenderCopy(renderer, textTex, NULL, &Transform);
	SDL_DestroyTexture(textTex);
	SDL_FreeSurface(textSurface);
}

void CustomText::SetContent(string s)
{
	content = s;
	textSurface = TTF_RenderText_Solid(font, content.c_str(), color);
	cout << TTF_GetError();
	if (textSurface == NULL)
	{
		return;
	}
	textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
	
	Transform.w = textSurface->w;
	Transform.h = textSurface->h;
}

void CustomText::SetPosition(int x, int y)
{
	Transform.x = x;
	Transform.y = y;
}