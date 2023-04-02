#include "GameplayCtrl.h"



#pragma region Variable Definition
vector<ColorLine> listColorLine;
vector<ColorLine> queueListFadedColorLine;

CustomTexture gameplayBgTexture("ColorLine Game UI.png", 0, 0);


//Button restartButton(14, 14, 52, 52, "", "RestartButton.png");



#pragma endregion



void Gameplay_Update()
{

    //Gameplay Background      
    gameplayBgTexture.RenderTexture();

    /*if (!Mix_PlayingMusic())
    {
        Mix_PlayMusic(bgMusic, -1);
        cout << "Playing BG Music" << endl;
    }*/

    
    //cout << Mix_GetError() << endl;
    
    //Count Remaining
    CountTimeLeft();
    CountRemainingLine();



    //Gameplay TextLine
    int y = 200;
    StringText(pixelFont_Small, { 0, 0, 0 }, "Remaining:", 2, y);
    IntText(pixelFont_Small, { 0, 0, 0 }, remainingLine, 2, y + 20);
    
    StringText(pixelFont_Small, { 0, 0, 0 }, "Level:", 2, y + 50);
    IntText(pixelFont_Small, { 0, 0, 0 }, level, 2, y + 70);

    int timeLeftText_W, timeLeftText_H;
    int roundedTimeLeftSecond = (int)(round(timeRemainingCounter));
    GetTextWidthHeight(pixelFont_Small, to_string(roundedTimeLeftSecond), timeLeftText_W, timeLeftText_H);
    IntText(pixelFont_Small, { 255, 255, 255 }, roundedTimeLeftSecond, 21 + (109 - timeLeftText_W) / 2, 427 + (21 - timeLeftText_H) / 2);



    //Get Highest Pointed Layer
    for (int i = listColorLine.size() - 1; i >= 0; i--)
    {
        if (listColorLine[i].IsPointed())
        {
            highestPointedLayer = listColorLine[i].layer;
            break;
        }
    }

    //Render and DetectMouseClick ColorLines
    for (int i = 0; i < listColorLine.size(); i++)
    {
        if (listColorLine[i].isEnabled)
        {
            
            listColorLine[i].RenderLine();
            if (listColorLine[i].DetectMouseClick() && listColorLine[i].layer == highestLayer)
            {
                listColorLine[i].isEnabled = false;
                
                Mix_PlayChannel(-1, onClickButtonSFX, 0);
                
            }
            

        }
    }

    //Render FadingLine && CountFadingTime
    for (int i = 0; i < queueListFadedColorLine.size(); i++)
    {
        queueListFadedColorLine[i].RenderLine();
        queueListFadedColorLine[i].CountFadingTime();
        float timer = queueListFadedColorLine[i].fadingTimer;
        if (timer >= queueListFadedColorLine[i].fadingTimeLimit)
        {
            queueListFadedColorLine.erase(queueListFadedColorLine.begin() + i);
            i--;
        }
    }

    
    ResizeListColorLine();

    WinLoseSystem();
    
}


#pragma region WIN LOSE SYSTEM

void WinLoseSystem()
{
    if (remainingLine <= 0 && timeRemainingCounter > 0)
    {
        WinGame();
    }
    else if (timeRemainingCounter <= 0 && remainingLine > 0)
    {
        LoseGame();
    }

}

void WinGame()
{
    stopCounting = true;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect winScreen = { gameplayScreen_X, gameplayScreen_Y, gameplayScreen_Width, gameplayScreen_Height };
    SDL_RenderFillRect(renderer, &winScreen);
    string winMessage = "YOU WIN";
    int textW, textH;
    GetTextWidthHeight(pixelFont_Med, winMessage, textW, textH);
    StringText(pixelFont_Med, { 255, 255, 255 }, winMessage, gameplayScreen_X + (gameplayScreen_Width - textW) / 2, gameplayScreen_Y + (gameplayScreen_Height - textH) / 2);

    if (!leveledUp)
    {
        level++;
        leveledUp = true;
    }

    ContinueNextLevel();


}

void LoseGame()
{
    stopCounting = true;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect loseScreen = { gameplayScreen_X, gameplayScreen_Y, gameplayScreen_Width, gameplayScreen_Height };
    SDL_RenderFillRect(renderer, &loseScreen);
    string loseMessage = "YOU LOSE";
    int textW, textH;
    GetTextWidthHeight(pixelFont_Med, loseMessage, textW, textH);
    StringText(pixelFont_Med, { 255, 255, 255 }, loseMessage, gameplayScreen_X + (gameplayScreen_Width - textW) / 2, gameplayScreen_Y + (gameplayScreen_Height - textH) / 2);

}
#pragma endregion



void ContinueNextLevel()
{
    int nextLevelButtonW = 140;
    int nextLevelButtonH = 60;
    Button nextLevelButton(gameplayScreen_X + (gameplayScreen_Width - nextLevelButtonW) / 2, 40 + gameplayScreen_Y + (gameplayScreen_Height - nextLevelButtonH) / 2, nextLevelButtonW, nextLevelButtonH, "NEXT LEVEL", "");
    nextLevelButton.RenderButton(pixelFont_Small);

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


