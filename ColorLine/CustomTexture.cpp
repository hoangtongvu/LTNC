#include "CustomTexture.h"


CustomTexture::CustomTexture(string path)
{
	texPath = spriteDir + path;
	texRect.x = 0;
	texRect.y = 0;
}




void CustomTexture::LoadTexture(int w, int h)
{
    SDL_Surface* texSurface;
    texSurface = IMG_Load(texPath.c_str());
    if (texSurface == NULL)
    {
        cout << "ERROR: Can't Load Surface Path: " << texPath << endl;
        return;
    }


    tex = SDL_CreateTextureFromSurface(renderer, texSurface);
    if (tex == NULL)
    {
        cout << "ERROR: Can't Load Texture From Surface: " << texPath << endl;
        return;
    }



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
    if (w != -1)
    {
        texRect.w = w;
    }
    if (h != -1)
    {
        texRect.h = h;
    }
}

void CustomTexture::SetColor(int r, int g, int b, int alpha)
{
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);//This sets the texture in blendmode

    SDL_SetTextureColorMod(tex, r, g, b);
    SDL_SetTextureAlphaMod(tex, alpha); //sets the alpha into the texture
}


void CustomTexture::Destroy()
{
    SDL_DestroyTexture(tex);
}

CustomTexture::~CustomTexture()
{
    //SDL_DestroyTexture(tex);
}
