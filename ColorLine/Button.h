#pragma once
#include "GameManager.h"
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
        int thickness = 3;
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