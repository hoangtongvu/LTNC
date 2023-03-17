#include "ColorLine.h"


ColorLine::ColorLine()
{
    borderThickness = 3;


    baseBorder.x = 6;
    baseBorder.y = 6;
    baseBorder.w = gameplayScreen_Width;
    baseBorder.h = 40;

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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &baseBorder);

    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &baseLine);
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



                /*highestLayer = listColorLine[0].layer;
                for (int i = 1; i < colorLineAmount; i++)
                {
                    if (highestLayer < listColorLine[i].layer && listColorLine[i].isEnabled)
                    {
                        highestLayer = listColorLine[i].layer;
                    }
                }*/
                //cout << "clicked";
            }

        }
    }
}


void ColorLine::PlayOnClickSFX()
{
   // Mix_PlayChannel(-1, onClickSFX, 0);
}

ColorLine::~ColorLine()
{
    //Mix_FreeChunk(onClickSFX);
}
