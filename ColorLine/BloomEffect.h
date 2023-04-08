#pragma once
#include "GameManager.h"
#include "CustomTexture.h";

class BloomEffect
{
public:
	SDL_Rect Transform;
	int r, g, b;
	CustomTexture whitePixelTex;

	double intensity;
	BloomEffect(SDL_Rect _Transform, int r, int g, int b, double _intensity);
	void Render();
	void SetColor(int rPar, int gPar, int bPar);
	~BloomEffect();

private:

};



