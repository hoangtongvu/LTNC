#pragma once

#include "GameManager.h"
//#include "GameplayCtrl.h"

class ColorLine
{

public:
#pragma region Variable Initialize
    SDL_Rect baseLine;
    SDL_Rect baseBorder;
    int borderThickness;
    int r, g, b, alpha;
    bool isPointed = false;
    int layer;
    int dir;
    bool isEnabled;

#pragma endregion



    ColorLine();

    ~ColorLine();

    void SetDir(int dirParameter);

    void SetBaseColor(int rPar, int gPar, int bPar, int alphaPar);

    void RenderLine();

    void DetectMouseClick(ColorLine listColorLine[]);
    
  


private:

};



