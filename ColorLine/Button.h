#pragma once
#include "Header.h"
#include "GameplayCtrl.h"
#include "TextFunc.h"

class Button
{
public:
    SDL_Rect baseButton;
    string buttonLabel;
    string buttonSpritePath;
    bool isEnabled;


    Button(int x, int y, int w, int h, string label, string spritePath)
    {
        baseButton = { x, y, w, h };
        buttonLabel = label;
        buttonSpritePath = spritePath;
        isEnabled = true;
    }
    void RenderButton(TTF_Font* font);
    bool DetectMouseClick();
    bool isPointed();
    ~Button();

private:

};
