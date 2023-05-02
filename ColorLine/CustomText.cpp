#include "CustomText.h"


CustomText::CustomText(TTF_Font* _font)
{
	Transform = { 0, 0, 0, 0 };
	color = { 255, 255, 255 };
	font = _font;
	content = "";
}

CustomText::~CustomText()
{
	/*SDL_DestroyTexture(textTex);
	SDL_FreeSurface(textSurface);*/
}


void CustomText::Render()
{
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, content.c_str(), color);;
	SDL_Texture* tempTex = GetTexture(tempSurface);
	SDL_RenderCopy(renderer, tempTex, NULL, &Transform);
	SDL_DestroyTexture(tempTex);
	SDL_FreeSurface(tempSurface);
	cout << TTF_GetError() << endl;


}

void CustomText::SetContent(string s)
{
	content = s;

	SDL_Surface* _textSurface = TTF_RenderText_Solid(font, content.c_str(), color);
	if (_textSurface == NULL)
	{
		cout << "TextSurface is NULL" << endl;
		return;
	}
	
	Transform.w = _textSurface->w;
	Transform.h = _textSurface->h;

	SDL_FreeSurface(_textSurface);
}


SDL_Texture* CustomText::GetTexture(SDL_Surface* tempSurface)
{		
	return SDL_CreateTextureFromSurface(renderer, tempSurface);
}


void CustomText::SetPosition(int x, int y)
{
	Transform.x = x;
	Transform.y = y;
}