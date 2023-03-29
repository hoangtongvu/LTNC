#include "CustomTexture.h"


CustomTexture::CustomTexture(string path, int x, int y, int w, int h)
{
	texPath = spriteDir + path;
	texRect.x = x;
	texRect.y = y;
    LoadTexture(w, h);
}




void CustomTexture::LoadTexture(int w, int h)
{
    SDL_Surface* texSurface;
    texSurface = IMG_Load(texPath.c_str());
    tex = SDL_CreateTextureFromSurface(renderer, texSurface);

    if (w == -1)
    {
        w = texSurface->w;
    }
    if (h == -1)
    {
        h = texSurface->h;
    }


    texRect.w = w;
    texRect.h = h;
    SDL_FreeSurface(texSurface);
}

void CustomTexture::RenderTexture()
{
    SDL_RenderCopy(renderer, tex, NULL, &texRect);
}



void CustomTexture::Transform(int x, int y, int w, int h)
{
    texRect.x = x;
    texRect.y = y;
    texRect.w = w;
    texRect.h = h;
}

void CustomTexture::SetColor(int r, int g, int b, int alpha)
{
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);//This sets the texture in blendmode

    SDL_SetTextureColorMod(tex, r, g, b);
    SDL_SetTextureAlphaMod(tex, alpha); //sets the alpha into the texture
}


CustomTexture::~CustomTexture()
{
}
