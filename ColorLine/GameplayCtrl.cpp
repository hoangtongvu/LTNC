#include "GameplayCtrl.h"



#pragma region Variable Definition

SDL_Renderer* renderer;
SDL_Window* window;
const string WINDOW_TITLE = "MUSE DASH";

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


const int gameplayScreen_X = 171;
const int gameplayScreen_Y = 20;
const int gameplayScreen_Width = 1088;
const int gameplayScreen_Height = 679;


int mouseX = 0;
int mouseY = 0;

bool isClicked = false;

int colorLineAmount = 10;
int highestLayer = 0;
int remainingLine = 0;

int maxTimeSecond = 15;
double timeRemainingCounter = maxTimeSecond;
bool stopCounting = false;


bool leveledUp = false;
int level = 0;

bool gameStarted = false;






#pragma endregion





#pragma region WIN LOSE SYSTEM

void WinLoseSystem(TTF_Font* medFont, TTF_Font* smallFont)
{
    if (remainingLine <= 0 && timeRemainingCounter > 0)
    {
        WinGame(medFont, smallFont);
        stopCounting = true;
    }
    else if (timeRemainingCounter <= 0 && remainingLine > 0)
    {
        LoseGame(medFont, smallFont);
        stopCounting = true;
    }

}

void WinGame(TTF_Font* medFont, TTF_Font* smallFont)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect winScreen = { gameplayScreen_X, gameplayScreen_Y, gameplayScreen_Width, gameplayScreen_Height };
    SDL_RenderFillRect(renderer, &winScreen);
    string winMessage = "YOU WIN";
    int textW, textH;
    GetTextWidthHeight(medFont, winMessage, textW, textH);
    StringText(medFont, { 255, 255, 255 }, winMessage, gameplayScreen_X + (gameplayScreen_Width - textW) / 2, gameplayScreen_Y + (gameplayScreen_Height - textH) / 2);

    if (!leveledUp)
    {
        level++;
        leveledUp = true;
    }

    ContinueNextLevel(smallFont);


}

void LoseGame(TTF_Font* medFont, TTF_Font* smallFont)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect loseScreen = { gameplayScreen_X, gameplayScreen_Y, gameplayScreen_Width, gameplayScreen_Height };
    SDL_RenderFillRect(renderer, &loseScreen);
    string loseMessage = "YOU LOSE";
    int textW, textH;
    GetTextWidthHeight(medFont, loseMessage, textW, textH);
    StringText(medFont, { 255, 255, 255 }, loseMessage, gameplayScreen_X + (gameplayScreen_Width - textW) / 2, gameplayScreen_Y + (gameplayScreen_Height - textH) / 2);

}
#pragma endregion



void ContinueNextLevel(TTF_Font* smallFont)
{
    int nextLevelButtonW = 140;
    int nextLevelButtonH = 60;
    Button nextLevelButton(gameplayScreen_X + (gameplayScreen_Width - nextLevelButtonW) / 2, 40 + gameplayScreen_Y + (gameplayScreen_Height - nextLevelButtonH) / 2, nextLevelButtonW, nextLevelButtonH, "NEXT LEVEL", "");
    nextLevelButton.RenderButton(smallFont);

    if (nextLevelButton.DetectMouseClick())
    {
        nextLevelButton.isEnabled = false;
        leveledUp = false;
    }
}






