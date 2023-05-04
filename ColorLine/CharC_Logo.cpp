#include "CharC_Logo.h"


CharC_Logo::CharC_Logo()
{
	Transform = { 350, 80, 150, 180 };
    
    colorChangeTimer = 0;
    maxTimeColorChange = 1;
    colorChangeSpeed = 7;
    for (int i = 0; i < 3; i++)
    {
        currentColor[i] = Vector3::Random(30, 255);
        targetColor[i] = Vector3::Random(30, 255);

    }

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
    logoListColorLine[0].SetDir(ColorLine::Horizontal);


    logoListColorLine[1].baseBorder.x = Transform.x;
    logoListColorLine[1].baseBorder.y = Transform.y + w;
    logoListColorLine[1].verticalHeight = Transform.h - 2 * w;
    logoListColorLine[1].SetDir(ColorLine::Vertical);


    logoListColorLine[2].baseBorder.x = Transform.x + w;
    logoListColorLine[2].baseBorder.y = Transform.y + Transform.h - w;
    logoListColorLine[2].horizontalWidth = Transform.w - w;
    logoListColorLine[2].SetDir(ColorLine::Horizontal);




}

void CharC_Logo::Render()
{
    /*SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &Transform);*/

    colorChangeTimer += deltaTime * colorChangeSpeed;


    if (colorChangeTimer >= maxTimeColorChange)
    {
        for (int i = 0; i < 3; i++)
        {
            /*int randColorR = rand() % 225 + 30;
            int randColorG = rand() % 225 + 30;
            int randColorB = rand() % 225 + 30;
            logoListColorLine[i].SetBaseColor(randColorR, randColorG, randColorB);*/
            currentColor[i] = targetColor[i];
            targetColor[i] = Vector3::Random(30, 255);
        }
        colorChangeTimer = 0;
    }

    for (int i = 0; i < 3; i++)
    {
        Vector3 tempVector = Vector3::Lerp(currentColor[i], targetColor[i], colorChangeTimer);
        //tempVector.Print();
        logoListColorLine[i].SetBaseColor(tempVector.x, tempVector.y, tempVector.z);

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