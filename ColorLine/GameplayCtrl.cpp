#include "GameplayCtrl.h"


SDL_Renderer* renderer;


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


const int gameplayScreen_X = 175;
const int gameplayScreen_Y = 24;
const int gameplayScreen_Width = 1080;
const int gameplayScreen_Height = 671;


int mouseX = 0;
int mouseY = 0;

bool isClicked = false;

int colorLineAmount = 15;
int highestLayer = 0;
int remainingLine = 0;

int maxTimeSecond = 10;
double timeRemainingCounter = maxTimeSecond;
bool stopCounting = false;

int level = 0;

bool gameStarted = false;

string assetDir = "Assets/";
string spriteDir = assetDir + "Sprites/";
string fontDir = assetDir + "Fonts/";



#pragma region WIN LOSE SYSTEM

void WinLoseSystem(TTF_Font* font)
{
    if (remainingLine <= 0 && timeRemainingCounter > 0)
    {
        WinGame(font);
        stopCounting = true;
    }
    else if (timeRemainingCounter <= 0 && remainingLine > 0)
    {
        LoseGame(font);
        stopCounting = true;
    }

}

void WinGame(TTF_Font* font)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect winScreen = { gameplayScreen_X, gameplayScreen_Y, gameplayScreen_Width, gameplayScreen_Height };
    SDL_RenderFillRect(renderer, &winScreen);
    string winMessage = "YOU WIN";
    int textW, textH;
    GetTextWidthHeight(font, winMessage, textW, textH);
    StringText(font, { 255, 255, 255 }, winMessage, gameplayScreen_X + (gameplayScreen_Width - textW) / 2, gameplayScreen_Y + (gameplayScreen_Height - textH) / 2);


}

void LoseGame(TTF_Font* font)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect loseScreen = { gameplayScreen_X, gameplayScreen_Y, gameplayScreen_Width, gameplayScreen_Height };
    SDL_RenderFillRect(renderer, &loseScreen);
    string loseMessage = "YOU LOSE";
    int textW, textH;
    GetTextWidthHeight(font, loseMessage, textW, textH);
    StringText(font, { 255, 255, 255 }, loseMessage, gameplayScreen_X + (gameplayScreen_Width - textW) / 2, gameplayScreen_Y + (gameplayScreen_Height - textH) / 2);

}
#pragma endregion

