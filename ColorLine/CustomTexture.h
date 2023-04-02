#pragma once
//#include "GameplayCtrl.h"
#include "GameManager.h"


class CustomTexture
{
public:
	string texPath;
	SDL_Rect texRect;
	SDL_Texture* tex;


	CustomTexture(string path, int x, int y);
	~CustomTexture();

	
	void LoadTexture(int w, int h);
	void RenderTexture();
	void Transform(int x, int y, int w, int h);
	void SetColor(int r, int g, int b, int alpha);

private:

};


