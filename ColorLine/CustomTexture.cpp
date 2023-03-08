#include "CustomTexture.h"


CustomTexture::CustomTexture(string path, int x, int y)
{
	texPath = spriteDir + path;
	texRect.x = x;
	texRect.y = y;
    LoadTexture();
}

CustomTexture::~CustomTexture()
{
}


void CustomTexture::LoadTexture()
{
    SDL_Surface* texSurface;
    texSurface = IMG_Load(texPath.c_str());
    tex = SDL_CreateTextureFromSurface(renderer, texSurface);
    texRect.w = texSurface->w;
    texRect.h = texSurface->h;
    SDL_FreeSurface(texSurface);
}

void CustomTexture::RenderTexture()
{
    SDL_RenderCopy(renderer, tex, NULL, &texRect);
}