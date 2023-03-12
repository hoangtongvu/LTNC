#include "GameplayCtrl.h"



#pragma region Variable Definition
vector<ColorLine> listColorLine;


#pragma endregion



void Gameplay_Update(TTF_Font* medFont, TTF_Font* smallFont)
{
    //Count RemainingTime
    CountRemainingLine();
    if (!stopCounting)
    {
        timeRemainingCounter -= deltaTime;
    }



    //Gameplay TextLine
    int y = 200;
    StringText(smallFont, { 0, 0, 0 }, "Remaining Line:", 2, y);
    IntText(smallFont, { 0, 0, 0 }, remainingLine, 2, y + 20);


    int timeLeftText_W, timeLeftText_H;
    int roundedTimeLeftSecond = (int)(round(timeRemainingCounter));
    GetTextWidthHeight(smallFont, to_string(roundedTimeLeftSecond), timeLeftText_W, timeLeftText_H);
    IntText(smallFont, { 255, 255, 255 }, roundedTimeLeftSecond, 21 + (109 - timeLeftText_W) / 2, 427 + (21 - timeLeftText_H) / 2);




    //Render and DetectMouseClick ColorLines
    for (int i = 0; i < listColorLine.size(); i++)
    {
        if (listColorLine[i].isEnabled)
        {
            listColorLine[i].RenderLine();
            listColorLine[i].DetectMouseClick();

        }
    }

    ResizeListColorLine();

    WinLoseSystem(medFont, smallFont);

}


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
        RestartGame(level * colorLineAmount_Base);

    }
}


void ResizeListColorLine()
{
    for (int i = 0; i < listColorLine.size(); i++)
    {
        if (!listColorLine[i].isEnabled)
        {
            //cout << "deleted " << i << endl;
            listColorLine.erase(listColorLine.begin() + i);
            i--;
        }
    }
    if (!listColorLine.empty())
    {
        highestLayer = listColorLine.back().layer;

    }
}


void CountRemainingLine()
{
    remainingLine = listColorLine.size();
}


void RestartGame(int newAmount)
{
    InitListColorLine(newAmount);
    timeRemainingCounter = maxTimeSecond;
    stopCounting = false;
}


void InitListColorLine(int newAmount)
{
    listColorLine.clear();
    colorLineAmount = newAmount;
    srand(time(NULL));
    for (int i = 0; i < newAmount; i++)
    {
        int dir = rand() % 2;
        int randomColor = rand() % 12;
        ColorLine tempColorLine;
        tempColorLine.SetDir(dir);
        tempColorLine.SetBaseColor(simpleColorList[randomColor][0], simpleColorList[randomColor][1], simpleColorList[randomColor][2], 1);
        listColorLine.emplace_back(tempColorLine);
    }


    listColorLine[0].layer = 0;
    int layerCount = 1;

    for (int i = 1; i < newAmount; i++)
    {
        if (listColorLine[i].dir == listColorLine[i].dir)
        {
            if (listColorLine[i].dir == 1 &&
                (listColorLine[i].baseBorder.x + listColorLine[i].baseBorder.w <= listColorLine[i - 1].baseBorder.x ||
                    listColorLine[i - 1].baseBorder.x + listColorLine[i - 1].baseBorder.w <= listColorLine[i].baseBorder.x))//vertical
            {
                listColorLine[i].layer = listColorLine[i - 1].layer;
            }
            else if (listColorLine[i].dir == 0 &&
                (listColorLine[i].baseBorder.y + listColorLine[i].baseBorder.h <= listColorLine[i - 1].baseBorder.y ||
                    listColorLine[i - 1].baseBorder.y + listColorLine[i - 1].baseBorder.h <= listColorLine[i].baseBorder.y))//horizontal
            {
                listColorLine[i].layer = listColorLine[i - 1].layer;
            }
            else
            {
                listColorLine[i].layer = layerCount;
                layerCount++;
            }


        }
        else
        {
            listColorLine[i].layer = layerCount;
            layerCount++;
        }
    }


    highestLayer = layerCount - 1;

}





