#include "CharC_Logo.h"


CharC_Logo::CharC_Logo()
{
	Transform = { 350, 80, 150, 180 };
    
    colorChangeTimer = 0;
    maxTimeColorChange = 0.1;

    for (int i = 0; i < 3; i++)
    {
        ColorLine temp;
        logoListColorLine.emplace_back(temp);
    }
}


void CharC_Logo::SetTransform()
{
    int w = logoListColorLine[0].baseWidth;

    logoListColorLine[0].baseBorder.x = Transform.x + w;
    logoListColorLine[0].baseBorder.y = Transform.y;
    logoListColorLine[0].horizontalWidth = Transform.w - w;
    logoListColorLine[0].SetDir(0);


    logoListColorLine[1].baseBorder.x = Transform.x;
    logoListColorLine[1].baseBorder.y = Transform.y + w;
    logoListColorLine[1].verticalHeight = Transform.h - 2 * w;
    logoListColorLine[1].SetDir(1);


    logoListColorLine[2].baseBorder.x = Transform.x + w;
    logoListColorLine[2].baseBorder.y = Transform.y + Transform.h - w;
    logoListColorLine[2].horizontalWidth = Transform.w - w;
    logoListColorLine[2].SetDir(0);




}

void CharC_Logo::Render()
{
    /*SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &Transform);*/

    colorChangeTimer += deltaTime;

    if (colorChangeTimer >= maxTimeColorChange)
    {
        for (int i = 0; i < 3; i++)
        {
            int randColorR = rand() % 225 + 30;
            int randColorG = rand() % 225 + 30;
            int randColorB = rand() % 225 + 30;
            logoListColorLine[i].SetBaseColor(randColorR, randColorG, randColorB);
        }
        
        colorChangeTimer = 0;
    }
    
    for (int i = 0; i < 3; i++)
    {
        logoListColorLine[i].RenderLine();

    }



}

CharC_Logo::~CharC_Logo()
{
    for (int i = 0; i < 3; i++)
    {
        logoListColorLine[i].OnDestroy();
    }
}