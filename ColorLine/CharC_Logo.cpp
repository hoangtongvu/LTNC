#include "CharC_Logo.h"


CharC_Logo::CharC_Logo()
{
	Transform = { 300, 50, 120, 130 };
    /*for (int i = 0; i < 3; i++)
    {
        ColorLine temp;
        logoListColorLine.emplace_back(temp);
    }*/
}


void CharC_Logo::SetTransform()
{
    int w = logoListColorLine[0].baseWidth;

    logoListColorLine[0].baseBorder.x = Transform.x + w;
    logoListColorLine[0].baseBorder.y = Transform.y;
    logoListColorLine[0].horizontalWidth = Transform.w;
    logoListColorLine[0].SetDir(0);


    logoListColorLine[1].baseBorder.x = Transform.x;
    logoListColorLine[1].baseBorder.y = Transform.y + w;
    logoListColorLine[1].verticalHeight = Transform.h;
    logoListColorLine[1].SetDir(1);


    logoListColorLine[2].baseBorder.x = Transform.x + w;
    logoListColorLine[2].baseBorder.y = Transform.y + Transform.h + w;
    logoListColorLine[2].horizontalWidth = Transform.w;
    logoListColorLine[2].SetDir(0);


}

void CharC_Logo::Render()
{
    for (int i = 0; i < 3; i++)
    {
        int randColorR = rand() % 205 + 30;
        int randColorG = rand() % 205 + 30;
        int randColorB = rand() % 205 + 30;
        logoListColorLine[i].SetBaseColor(randColorR, randColorG, randColorB);
        logoListColorLine[i].RenderLine();
    }
}

CharC_Logo::~CharC_Logo()
{
    //logoListColorLine.clear();
}