#pragma once
#include "Header.h"
#include "GameplayCtrl.h"
#include "TextFunc.h"

class Button
{
public:
    SDL_Rect baseButton;
    //Mix_Chunk* onClickSFX;
    string buttonLabel;
    string buttonSpritePath;
    bool isEnabled;

    



    Button(int x, int y, int w, int h, string label, string spritePath)
    {
        
        baseButton = { x, y, w, h };
        buttonLabel = label;
        buttonSpritePath = spritePath;
        isEnabled = true;
        //onClickSFX = Mix_LoadWAV((sfxDir + "Retro Blop 18.wav").c_str());
    }
    void RenderButton(TTF_Font* font);
    bool DetectMouseClick();
    bool isPointed();
    void PlayOnClickSFX();


    ~Button();

private:

};
