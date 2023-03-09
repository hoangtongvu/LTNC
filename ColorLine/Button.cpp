#include "Button.h"


void Button::RenderButton(TTF_Font* font)
{
    if (isEnabled)
    {
        if (!buttonSpritePath.empty())
        {
            SDL_Surface* buttonSurface;
            buttonSurface = IMG_Load((spriteDir + buttonSpritePath).c_str());
            SDL_Texture* buttonTex = SDL_CreateTextureFromSurface(renderer, buttonSurface);

            int r, g, b;
            if (isPointed)
            {
                r = 255;
                g = 255;
                b = 255;
            }
            else
            {
                r = 220;
                g = 220;
                b = 220;
            }
            SDL_SetTextureColorMod(buttonTex, r, g, b);
            isPointed = false;


            SDL_FreeSurface(buttonSurface);
            SDL_RenderCopy(renderer, buttonTex, NULL, &baseButton);
            SDL_DestroyTexture(buttonTex);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
            SDL_RenderFillRect(renderer, &baseButton);

        }

        if (!buttonLabel.empty())
        {
            int textW, textH;
            GetTextWidthHeight(font, buttonLabel, textW, textH);
            StringText(font, { 0, 0, 0 }, buttonLabel, baseButton.x + (baseButton.w - textW) / 2, baseButton.y + (baseButton.h - textH) / 2);

        }

    }
}

bool Button::DetectMouseClick()
{
    if (!isEnabled)
    {
        return false;
    }
    bool buttonClicked = false;
    if (mouseX >= baseButton.x && mouseY >= baseButton.y &&
        mouseX <= baseButton.x + baseButton.w && mouseY <= baseButton.y + baseButton.h)
    {
        isPointed = true;
        if (isClicked)
        {
            buttonClicked = true;
        }
    }
    return buttonClicked;
}



Button::~Button()
{
}