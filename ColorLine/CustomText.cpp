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
	SetContent(content);
	if (textTex != NULL)
	{
		SDL_RenderCopy(renderer, textTex, NULL, &Transform);
		SDL_DestroyTexture(textTex);
	}
	else
	{
		cout << "NULL" << endl;
	}


}

void CustomText::SetContent(string s)
{
	content = s;

	textSurface = TTF_RenderText_Solid(font, content.c_str(), color);
	if (textSurface == NULL)
	{
		cout << "TextSurface is NULL" << endl;
		return;
	}
	if (textTex != NULL)
	{
		SDL_DestroyTexture(textTex);

	}
	else
	{
		//cout << "NULL" << endl;
	}
	textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
	
	Transform.w = textSurface->w;
	Transform.h = textSurface->h;
	SDL_FreeSurface(textSurface);
	//cout << TTF_GetError() << endl;

}

void CustomText::SetPosition(int x, int y)
{
	Transform.x = x;
	Transform.y = y;
}