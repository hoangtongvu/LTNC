#pragma once

#include "GameManager.h"
//#include "GameplayCtrl.h"
#include "CustomTexture.h"

class ColorLine
{

public:
#pragma region Variable Initialize
    SDL_Rect baseLine;
    SDL_Rect baseBorder;
    //Mix_Chunk* onClickSFX;
    int borderThickness;
    int r, g, b, alpha;
    int layer;
    int dir;
    bool isEnabled;
    CustomTexture baseLineTexture;
    CustomTexture baseBorderTexture;

    float fadingTimeLimit;
    float fadingTimer;
    float fadingSpeed;

#pragma endregion



    ColorLine();
    ~ColorLine();

    void SetDir(int dirParameter);

    void SetBaseColor(int rPar, int gPar, int bPar, int alphaPar);

    void RenderLine();

    void DetectMouseClick();
    
    void PlayOnClickSFX();

    bool IsPointed();

    void CountFadingTime();



private:

};



