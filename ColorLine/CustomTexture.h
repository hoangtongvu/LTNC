#pragma once
#include "GameplayCtrl.h"


class CustomTexture
{
public:
	string texPath;
	SDL_Rect texRect;
	SDL_Texture* tex;


	CustomTexture(string path, int x, int y);
	~CustomTexture();

	void LoadTexture();
	void RenderTexture();

private:

};


