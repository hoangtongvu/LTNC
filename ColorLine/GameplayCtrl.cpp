#include "GameplayCtrl.h"



#pragma region Variable Definition
vector<ColorLine> listColorLine;
vector<ColorLine> queueListFadedColorLine;

string winMessage = "YOU WIN";
string loseMessage = "YOU LOSE";



int spaceBetween = SCREEN_WIDTH - gameplayScreen_X - gameplayScreen_Width;
int thickness = 5;
int leftPanel_X = spaceBetween;
int leftPanel_Y = spaceBetween;
int leftPanel_W = gameplayScreen_X - 2 * spaceBetween;
int leftPanel_H = gameplayScreen_Height;


#pragma endregion



void Gameplay_Update()
{
    GameplayEventHolder();
    //RenderGameplayBgTexture();
    CountTimeLeft();
    CountRemainingLine();
    GetHighestPointedLayer();
    RenderGameplayTextLine();
    RenderAndDetectMouseClickColorLine();
    TEST_RenderGameplayOverLay();
    RenderFadingLine();
    ResizeListColorLine();
    WinLoseSystem();
    GameplayDetectButtonClick();
    ResetMouseClick();

    SetBgBlack();
    SDL_Render();

 
    /*if (!Mix_PlayingMusic())
    {
        Mix_PlayMusic(bgMusic, -1);
        cout << "Playing BG Music" << endl;
    }*/
    //cout << Mix_GetError() << endl;
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

    WinLoseWindow winWindow(winMessage, uiManager.nextLevelButton);
    winWindow.r = 0;
    winWindow.g = 255;
    winWindow.b = 0;

    int w = 500;
    int h = 300;
    SDL_Rect winScreen = { gameplayScreen_X + (gameplayScreen_Width - w) / 2, gameplayScreen_Y + (gameplayScreen_Height - h) / 2, w, h };

    winWindow.Transform = winScreen;
    winWindow.Render();
    
    

    ContinueNextLevel();

    

}

void LoseGame()
{
    stopCounting = true;

    WinLoseWindow loseWindow(loseMessage, uiManager.restartButton);
    loseWindow.r = 255;
    loseWindow.g = 0;
    loseWindow.b = 0;

    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int w = 500;
    int h = 300;
    SDL_Rect loseScreen = { gameplayScreen_X + (gameplayScreen_Width - w) / 2, gameplayScreen_Y + (gameplayScreen_Height - h) / 2, w, h };
    loseWindow.Transform = loseScreen;
    loseWindow.Render();

    //SDL_RenderFillRect(renderer, &loseScreen);
    /*int textW, textH;
    GetTextWidthHeight(pixelFont_Med, loseMessage, textW, textH);
    Text(pixelFont_Med, { 255, 255, 255 }, loseMessage, gameplayScreen_X + (gameplayScreen_Width - textW) / 2, gameplayScreen_Y + (gameplayScreen_Height - textH) / 2);*/

}
#pragma endregion


void ContinueNextLevel()
{
    Button nextLevelButton = uiManager.nextLevelButton;
    nextLevelButton.RenderButton(pixelFont_Small);

    if (nextLevelButton.DetectMouseClick())
    {
        
        level++;
        gameSave.Write(saveFileName);
        nextLevelButton.isEnabled = false;
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
    long long int newAmount = (long)round((long)level * level * 0.15 * 12 ) + colorLineAmount_Base; 
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

void GetHighestPointedLayer()
{
    for (int i = listColorLine.size() - 1; i >= 0; i--)
    {
        if (listColorLine[i].IsPointed())
        {
            highestPointedLayer = listColorLine[i].layer;
            break;
        }
    }
}

void GameplayEventHolder()
{
    // EVENT HOLDER
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        {
            gameClose = true;
            break;

        }
        case SDL_MOUSEBUTTONDOWN:
        {
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
            {
                isClicked = true;
            }
            default:
                break;
            }
        }
        case SDL_MOUSEMOTION:
        {
            mouseX = event.motion.x;
            mouseY = event.motion.y;

            std::stringstream ss;
            ss << "X: " << mouseX << " Y: " << mouseY;

            SDL_SetWindowTitle(window, ss.str().c_str());
            break;

        }
        default:
            break;

        }

    }

}

void RenderGameplayBgTexture()
{
    //Gameplay Background  
    //CustomTexture gameplayBgTexture = uiManager.gameplayBgTexture;
    //gameplayBgTexture.RenderTexture();
}

void RenderGameplayTextLine()
{
    int leftRightSpacing = 10;
    int topBottomSpacing = 10;

    int timeLeftText_W = leftPanel_W - 2 * leftRightSpacing;
    int timeLeftText_H = 40;
    int timeLeftText_X = leftPanel_X + leftRightSpacing;
    int timeLeftText_Y = 427;

    //Gameplay TextLine
    SDL_Color textColor = { 255, 255, 255 };
    int y = 200;
    

    LabelAndTextWindow remainingLineWindow;
    remainingLineWindow.Transform = { timeLeftText_X, y, timeLeftText_W, timeLeftText_H * 2 };
    remainingLineWindow.label = "Line";
    remainingLineWindow.text = to_string(remainingLine);
    remainingLineWindow.Render();
    
    
    LabelAndTextWindow levelWindow;
    levelWindow.Transform = { timeLeftText_X, y + timeLeftText_H * 2 + topBottomSpacing, timeLeftText_W, timeLeftText_H * 2 };
    levelWindow.label = "Level";
    levelWindow.text = to_string(level);
    levelWindow.Render();


    /*Text(pixelFont_Small, textColor, "Level:", 2, y + 50);
    Text(pixelFont_Small, textColor, to_string(level), 2, y + 70);*/

    int roundedTimeLeftSecond = (int)(round(timeRemainingCounter));

    GameTimer timer;
    timer.Transform = { timeLeftText_X, timeLeftText_Y, timeLeftText_W, timeLeftText_H };
    timer.SetTime(roundedTimeLeftSecond);
    timer.Render();


}

void GameplayDetectButtonClick()
{
    int buttonLeftRightSpacing = 10;
    int buttonTopBottomSpacing = 10;
    int buttonH = 40;

    //Restart Button
    Button restartButton = uiManager.restartButton;
    restartButton.baseButton = { leftPanel_X + buttonLeftRightSpacing, leftPanel_Y + buttonTopBottomSpacing, leftPanel_W - 2 * buttonLeftRightSpacing, buttonH };
    restartButton.RenderButton(pixelFont_Small);
    if (restartButton.DetectMouseClick())
    {
        RestartGame();

    }

    //ReturnMenu Button
    Button returnMenuButton = uiManager.returnMenuButton;
    returnMenuButton.baseButton = { leftPanel_X + buttonLeftRightSpacing, leftPanel_Y + 2 * buttonTopBottomSpacing + buttonH, leftPanel_W - 2 * buttonLeftRightSpacing, buttonH };
    returnMenuButton.RenderButton(pixelFont_Small);
    if (returnMenuButton.DetectMouseClick())
    {
        gameStarted = false;
    }

}

void RenderAndDetectMouseClickColorLine()
{
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
}

void RenderFadingLine()
{
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

}

void TEST_RenderGameplayOverLay()
{
    
    //Gameplay Background  
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect gameplayRect = { gameplayScreen_X, gameplayScreen_Y, gameplayScreen_Width, gameplayScreen_Height };
    SDL_RenderDrawRect(renderer, &gameplayRect);
    gameplayRect = { gameplayScreen_X - thickness, gameplayScreen_Y - thickness, gameplayScreen_Width + thickness * 2, gameplayScreen_Height + thickness * 2 };
    SDL_RenderDrawRect(renderer, &gameplayRect);

    

    SDL_Rect leftPanelRect = { leftPanel_X, leftPanel_Y, leftPanel_W, leftPanel_H };
    SDL_RenderDrawRect(renderer, &leftPanelRect);
    leftPanelRect = { leftPanel_X - thickness, leftPanel_Y - thickness, leftPanel_W + thickness * 2, leftPanel_H + thickness * 2 };
    SDL_RenderDrawRect(renderer, &leftPanelRect);

}

