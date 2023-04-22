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
	int colorIntensity = r + g + b;

	float increasedSizePerTime = 0.5;
	for (int i = 0; i <= colorIntensity / 50; i++)
	{
		SDL_Rect rect;
		rect.w = Transform.w + i * i * increasedSizePerTime;
		rect.h = Transform.h + i * i * increasedSizePerTime;
		rect.x = Transform.x - i * i * increasedSizePerTime / 2;
		rect.y = Transform.y - i * i * increasedSizePerTime / 2;

		int alpha = 200 - 200 / 10 * i * i * increasedSizePerTime;
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