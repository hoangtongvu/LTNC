#include "GameplayCtrl.h"



#pragma region Variable Definition
vector<ColorLine> listColorLine_1;


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






//
//void InitListColorLine(ColorLine listColorLine[], int simpleColorList[][3], int& amountVariable, int newAmount, int& highestLayer)
//{
//    delete[] listColorLine;
//    listColorLine = new ColorLine[newAmount];
//    srand(time(NULL));
//    for (int i = 0; i < newAmount; i++)
//    {
//        int dir = rand() % 2;
//        int randomColor = rand() % 12;
//        listColorLine[i].SetDir(dir);
//        listColorLine[i].SetBaseColor(simpleColorList[randomColor][0], simpleColorList[randomColor][1], simpleColorList[randomColor][2], 1);
//    }
//
//
//    listColorLine[0].layer = 0;
//    int layerCount = 1;
//    for (int i = 1; i < newAmount; i++)
//    {
//        if (listColorLine[i].dir == listColorLine[i].dir)
//        {
//            if (listColorLine[i].dir == 1 &&
//                (listColorLine[i].baseBorder.x + listColorLine[i].baseBorder.w <= listColorLine[i - 1].baseBorder.x ||
//                    listColorLine[i - 1].baseBorder.x + listColorLine[i - 1].baseBorder.w <= listColorLine[i].baseBorder.x))//vertical
//            {
//                listColorLine[i].layer = listColorLine[i - 1].layer;
//            }
//            else if (listColorLine[i].dir == 0 &&
//                (listColorLine[i].baseBorder.y + listColorLine[i].baseBorder.h <= listColorLine[i - 1].baseBorder.y ||
//                    listColorLine[i - 1].baseBorder.y + listColorLine[i - 1].baseBorder.h <= listColorLine[i].baseBorder.y))//horizontal
//            {
//                listColorLine[i].layer = listColorLine[i - 1].layer;
//            }
//            else
//            {
//                listColorLine[i].layer = layerCount;
//                layerCount++;
//            }
//
//
//        }
//        else
//        {
//            listColorLine[i].layer = layerCount;
//            layerCount++;
//        }
//    }
//
//
//    highestLayer = layerCount - 1;
//    amountVariable = newAmount;
//
//}
//
//void RestartGame(ColorLine oldListColorLine[], int simpleColorList[][3], int& oldAmount, int newAmount, int& highestLayer)
//{
//    InitListColorLine(oldListColorLine, simpleColorList, oldAmount, newAmount, highestLayer);
//    timeRemainingCounter = maxTimeSecond;
//    stopCounting = false;
//}




