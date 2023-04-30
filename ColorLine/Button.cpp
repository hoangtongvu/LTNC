#include "Button.h"


void Button::RenderButton(TTF_Font* font)
{
    if (!isEnabled) return;
    
    if (!buttonSpritePath.empty())
    {
        SDL_Surface* buttonSurface;
        buttonSurface = IMG_Load((spriteDir + buttonSpritePath).c_str());
        SDL_Texture* buttonTex = SDL_CreateTextureFromSurface(renderer, buttonSurface);

        int r, g, b;
        if (isPointed())
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


        SDL_FreeSurface(buttonSurface);
        SDL_RenderCopy(renderer, buttonTex, NULL, &baseButton);
        SDL_DestroyTexture(buttonTex);
    }
    else
    {
        Uint8 r, g, b;
        r = 120;
        g = 120;
        b = 120;
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            
        if (isPointed())
        {
            r = 255;
            g = 255;
            b = 255;
        }
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);   
        SDL_RenderDrawRect(renderer, &baseButton);
            
            
        if (!label.empty())
        {
            buttonLabel.font = font;
            buttonLabel.SetContent(label);
            int textW, textH;
            textW = buttonLabel.Transform.w;
            textH = buttonLabel.Transform.h;
            buttonLabel.SetPosition(baseButton.x + (baseButton.w - textW) / 2, baseButton.y + (baseButton.h - textH) / 2);
            buttonLabel.Render();
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
        if (isClicked)
        {
            buttonClicked = true;
            //cout << buttonLabel << endl;    
        }
    }
    return buttonClicked;
}


bool Button::isPointed()
{
    if (!isEnabled)
    {
        return false;
    }
    bool pointedByMouse = false;
    if (mouseX >= baseButton.x && mouseY >= baseButton.y &&
        mouseX <= baseButton.x + baseButton.w && mouseY <= baseButton.y + baseButton.h)
    {
        pointedByMouse = true;
        
    }
    return pointedByMouse;
}




Button::~Button()
{
}