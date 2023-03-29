#include "ColorLine.h"


ColorLine::ColorLine():
    baseLineTexture("whitePixel.png", 0, 0, -1, -1),
    baseBorderTexture("whitePixel.png", 0, 0, -1, -1)

{
    borderThickness = 4;

    baseBorder.x = 6;
    baseBorder.y = 6;
    baseBorder.w = gameplayScreen_Width;
    baseBorder.h = 43;

    baseLine.x = baseBorder.x + borderThickness;
    baseLine.y = baseBorder.y + borderThickness;
    baseLine.w = baseBorder.w - borderThickness * 2;
    baseLine.h = baseBorder.h - borderThickness * 2;

    r = 0;
    g = 0;
    b = 0;
    alpha = 0;

    layer = 0;
    dir = 0;//horizontal

    isEnabled = true;
 
    fadingTimeLimit = 1;
    fadingTimer = 0;
    fadingSpeed = 2.5;
    //baseLineTexture.Transform(baseLine.x, baseLine.y, baseLine.w, baseLine.h);
    //baseBorderTexture.Transform(baseBorder.x, baseBorder.y, baseBorder.w, baseBorder.h);
    //onClickSFX = Mix_LoadWAV((sfxDir + "Retro Blop 18.wav").c_str());
}



void ColorLine::SetDir(int dirParameter)
{
    dir = dirParameter;
    if (dirParameter == 1)//vertical
    {
        baseBorder.w = baseBorder.h;
        baseBorder.h = gameplayScreen_Height;
        baseBorder.x += gameplayScreen_X + rand() % (gameplayScreen_Width - baseBorder.w - baseBorder.x * 2 + 1);
        baseBorder.y = gameplayScreen_Y;
    }
    else
    {
        baseBorder.y += gameplayScreen_Y + rand() % (gameplayScreen_Height - baseBorder.h - baseBorder.y * 2 + 1);
        baseBorder.x = gameplayScreen_X;
    }
    baseLine.x = baseBorder.x + borderThickness;
    baseLine.y = baseBorder.y + borderThickness;
    baseLine.w = baseBorder.w - borderThickness * 2;
    baseLine.h = baseBorder.h - borderThickness * 2;

    baseLineTexture.Transform(baseLine.x, baseLine.y, baseLine.w, baseLine.h);
    baseBorderTexture.Transform(baseBorder.x, baseBorder.y, baseBorder.w, baseBorder.h);
}

void ColorLine::SetBaseColor(int rPar, int gPar, int bPar, int alphaPar)
{
    r = rPar;
    g = gPar;
    b = bPar;
    alpha = alphaPar;
}

void ColorLine::RenderLine()
{
    int tempAlpha = 200;
    if (IsPointed())
    {
        tempAlpha = 255;
    }
    tempAlpha *= 1.0 - fadingTimer / fadingTimeLimit;
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderFillRect(renderer, &baseBorder);
    float colorScale = 0.75;
    baseBorderTexture.SetColor(r * colorScale, g *colorScale, b * colorScale, tempAlpha);
    baseBorderTexture.RenderTexture();

    //SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    //SDL_RenderFillRect(renderer, &baseLine);
    baseLineTexture.SetColor(r, g, b, tempAlpha);
    baseLineTexture.RenderTexture();
}

void ColorLine::DetectMouseClick()
{
    if (isClicked)
    {
        if (mouseX >= baseBorder.x && mouseY >= baseBorder.y &&
            mouseX <= baseBorder.x + baseBorder.w && mouseY <= baseBorder.y + baseBorder.h)
        {
            //cout << "Highest layer: " << highestLayer << endl;
            //cout << "this line layer: " << layer << endl;
            if (layer == highestLayer)
            {
                PlayOnClickSFX();
                isEnabled = false;  
            }

        }
    }
}

bool ColorLine::IsPointed()
{
    if (mouseX >= baseBorder.x && mouseY >= baseBorder.y &&
        mouseX <= baseBorder.x + baseBorder.w && mouseY <= baseBorder.y + baseBorder.h)
    {
        return true;
    }
    return false;
}


void ColorLine::PlayOnClickSFX()
{
   // Mix_PlayChannel(-1, onClickSFX, 0);
}

ColorLine::~ColorLine()
{
    //Mix_FreeChunk(onClickSFX);
}


void ColorLine::CountFadingTime()
{
    fadingTimer += deltaTime * fadingSpeed;
}
