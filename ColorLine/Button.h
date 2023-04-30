#pragma once
#include "GameManager.h"
#include "CustomText.h"

class Button
{
public:
    SDL_Rect baseButton;
    string label;
    CustomText buttonLabel;
    string buttonSpritePath;
    bool isEnabled;


    Button(int x, int y, int w, int h, string _label, string spritePath) :
        buttonLabel(pixelFont_Small)
    {
        int thickness = 3;
        baseButton = { x, y, w, h };
        //buttonLabel.SetContent(label);
        label = _label;
        buttonSpritePath = spritePath;
        isEnabled = true;
    }
    void RenderButton(TTF_Font* font);
    bool DetectMouseClick();
    bool isPointed();
    


    ~Button();

private:

};
