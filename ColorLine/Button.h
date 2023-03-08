#pragma once
#include "Header.h"
#include "GameplayCtrl.h"
#include "TextFunc.h"

class Button
{
public:
    SDL_Rect baseButton;
    string buttonLabel;
    bool isSelected;
    string buttonSpritePath;


    Button(int x, int y, int w, int h, string label, string spritePath)
    {
        baseButton = { x, y, w, h };
        buttonLabel = label;
        buttonSpritePath = spritePath;
        isSelected = false;
        isPointed = false;
    }
    void RenderButton(TTF_Font* font);
    void DetectMouseClick();
    ~Button();

private:
    bool isPointed;
};
