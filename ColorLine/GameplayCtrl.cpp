#include "GameplayCtrl.h"



#pragma region Variable Definition
vector<ColorLine> listColorLine;
vector<ColorLine> queueListFadedColorLine;


//TTF_Font* test = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), 20);

//GlobalGame globalGame;

#pragma endregion



void Gameplay_Update(TTF_Font* medFont, TTF_Font* smallFont)
{
    //Count Remaining
    CountTimeLeft();
    CountRemainingLine();




    //Gameplay TextLine
    int y = 200;
    StringText(smallFont, { 0, 0, 0 }, "Remaining:", 2, y);
    IntText(smallFont, { 0, 0, 0 }, remainingLine, 2, y + 20);
    
    
    StringText(smallFont, { 0, 0, 0 }, "Level:", 2, y + 50);
    IntText(smallFont, { 0, 0, 0 }, level, 2, y + 70);


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

    for (int i = 0; i < queueListFadedColorLine.size(); i++)
    {
        queueListFadedColorLine[i].RenderLine();
        queueListFadedColorLine[i].CountFadingTime();
        if (queueListFadedColorLine[i].fadingTimer >= queueListFadedColorLine[i].fadingTimeLimit)
        {
            queueListFadedColorLine.erase(queueListFadedColorLine.begin() + i);
            i--;
        }
    }



    ResizeListColorLine();

    WinLoseSystem(medFont, smallFont);
    cout << queueListFadedColorLine.size() << endl;
}


#pragma region WIN LOSE SYSTEM

void WinLoseSystem(TTF_Font* medFont, TTF_Font* smallFont)
{
    if (remainingLine <= 0 && timeRemainingCounter > 0)
    {
        WinGame(medFont, smallFont);
    }
    else if (timeRemainingCounter <= 0 && remainingLine > 0)
    {
        LoseGame(medFont, smallFont);
    }

}

void WinGame(TTF_Font* medFont, TTF_Font* smallFont)
{
    stopCounting = true;
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
    stopCounting = true;
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
        RestartGame();

    }
}


void ResizeListColorLine()
{
    for (int i = 0; i < listColorLine.size(); i++)
    {
        if (!listColorLine[i].isEnabled)
        {
            //cout << "deleted " << i << endl;
            queueListFadedColorLine.emplace_back(listColorLine[i]);
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


void RestartGame()
{
    long newAmount = (long)round((long)level * level * 0.15 * 12 ) + colorLineAmount_Base; 
    InitListColorLine(newAmount);
    maxTimeSecond = maxTimeSecond_Base + (int)round(level * level * 0.13 * 12);
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
        if (i % 2 == 0)
        {
            dir = 0;
        }
        else
        {
            dir = 1;
        }
        int randomColor = rand() % 12;
        int randColorR = rand() % 205 + 30;
        int randColorG = rand() % 205 + 30;
        int randColorB = rand() % 205 + 30;


        ColorLine tempColorLine;
        tempColorLine.SetDir(dir);
        //tempColorLine.SetBaseColor(simpleColorList[randomColor][0] + randColorRange, simpleColorList[randomColor][1] + randColorRange, simpleColorList[randomColor][2] + randColorRange, 1);
        tempColorLine.SetBaseColor(randColorR, randColorG, randColorB, 1);
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


void CountTimeLeft()
{
    if (!stopCounting)
    {
        timeRemainingCounter -= deltaTime;
    }
}


