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
    fadingT = 0;
    fadingSpeed = 2.5;

    lightenColorScale = 0.25;
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

    int tempAlpha = 150;
    float darkenBorderColorScale = 0.75;
    float borderColorScale = 0;
    float baseLineColorScale = 0;
    if (IsPointed() && highestPointedLayer == layer)
    {
        tempAlpha = 230;

        borderColorScale = lightenColorScale;
        baseLineColorScale = lightenColorScale;
    }
    tempAlpha *= 1.0 - fadingTimer / fadingTimeLimit;
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderFillRect(renderer, &baseBorder);
    

    baseBorderTexture.SetColor(r * darkenBorderColorScale + (255 - r * darkenBorderColorScale) * borderColorScale, g * darkenBorderColorScale + (255 - g * darkenBorderColorScale) * borderColorScale, b * darkenBorderColorScale + (255 - b * darkenBorderColorScale) * borderColorScale, tempAlpha);
    baseBorderTexture.RenderTexture();

    //SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    //SDL_RenderFillRect(renderer, &baseLine);
    baseLineTexture.SetColor(r + (255 - r) * baseLineColorScale, g + (255 - g) * baseLineColorScale, b + (255 - b) * baseLineColorScale, tempAlpha);
    baseLineTexture.RenderTexture();
}

bool ColorLine::DetectMouseClick()
{
    if (isClicked)
    {
        if (mouseX >= baseBorder.x && mouseY >= baseBorder.y &&
            mouseX <= baseBorder.x + baseBorder.w && mouseY <= baseBorder.y + baseBorder.h)
        {
            //cout << "Highest layer: " << highestLayer << endl;
            //cout << "this line layer: " << layer << endl;
            return true;
            /*if (layer == highestLayer)
            {
                PlayOnClickSFX();
                isEnabled = false;  
            }*/

        }
    }
    return false;
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

void ColorLine::CountFadingTime()
{
    fadingT += deltaTime;
    fadingTimer += fadingT * fadingT * fadingSpeed;
}


ColorLine::~ColorLine()
{
   
}




