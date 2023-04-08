#include "BloomEffect.h"



BloomEffect::BloomEffect(SDL_Rect _Transform, int _r, int _g, int _b, double _intensity) :
	whitePixelTex("whitePixel.png", 0, 0)
{
	whitePixelTex.LoadTexture(-1, -1);
	Transform = _Transform;
	r = _r; 
	g = _g; 
	b = _b;
	intensity = _intensity;
}

void BloomEffect::Render()
{
	int increasedSizePerTime = 6;
	for (int i = 0; i <= 10; i++)
	{
		SDL_Rect rect;
		rect.w = Transform.w + i * increasedSizePerTime;
		rect.h = Transform.h + i * increasedSizePerTime;
		rect.x = Transform.x - i * increasedSizePerTime / 2;
		rect.y = Transform.y - i * increasedSizePerTime / 2;

		int alpha = 255 - 255 / 10 * i;
		whitePixelTex.Transform(rect.x, rect.y, rect.w, rect.h);
		whitePixelTex.SetColor(r, g, b, alpha);
		whitePixelTex.RenderTexture();
	}
}

void BloomEffect::SetColor(int rPar, int gPar, int bPar)
{
	r = rPar;
	g = gPar;
	b = bPar;
}

BloomEffect::~BloomEffect()
{
}