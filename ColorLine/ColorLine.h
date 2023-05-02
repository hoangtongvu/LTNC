#pragma once

#include "GameManager.h"
#include "CustomTexture.h"
#include "BloomEffect.h"

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
    enum Direction
    {
        Horizontal,
        Vertical
    };
    int dir;
    bool isEnabled;
    

    int verticalHeight;
    int horizontalWidth;
    int baseWidth;


    float fadingTimeLimit;
    float fadingTimer;
    float fadingT;
    float fadingSpeed;
    

    

    //BloomEffect pointedBloom;

#pragma endregion


    ColorLine();
    ~ColorLine();
    void SetDir(int dirParameter);
    void SetBaseColor(int rPar, int gPar, int bPar);
    void RenderLine();
    bool DetectMouseClick();
    bool IsPointed();
    void CountFadingTime();
    void SetTransform();
    void OnDestroy();


private:
    CustomTexture baseLineTexture;
    CustomTexture baseBorderTexture;

    float pointedLightenColorScale;
    float pointedLightenColorScaleSpeed;
    float pointedLightenColorScale_Max;
    float pointedLightenColorScale_Min;

    float onClickLightenColorScale;


    int baseAlpha;
    int pointedAlpha;
};



