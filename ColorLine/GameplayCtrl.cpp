#include "GameplayCtrl.h"



#pragma region Variable Definition
vector<ColorLine> listColorLine;


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
        //RestartGame()
    }
}




void ResizeListColorLine()
{
    for (int i = 0; i < listColorLine.size(); i++)
    {
        if (!listColorLine[i].isEnabled)
        {
            cout << "deleted " << i << endl;
            listColorLine.erase(listColorLine.begin() + i);
            i--;
        }
    }
    if (!listColorLine.empty())
    {
        highestLayer = listColorLine.back().layer;

    }
}






