#pragma once
#include "GameManager.h"


class CustomWindow
{
public:
	SDL_Rect Transform;
	int r, g, b;
	SDL_Color borderColor;
	CustomWindow();
	~CustomWindow();
	virtual void Render();
	virtual void RenderBackground();
	virtual void RenderBorder();



private:

};




