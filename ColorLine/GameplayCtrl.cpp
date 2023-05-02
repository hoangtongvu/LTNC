#include "GameplayCtrl.h"



#pragma region Variable Definition


GameplayCtrl* GameplayCtrl::instance = NULL;

vector<ColorLine> queueListFadedColorLine;



int spaceBetween = SCREEN_WIDTH - gameplayScreen_X - gameplayScreen_Width;
int thickness = 5;
int leftPanel_X = spaceBetween;
int leftPanel_Y = spaceBetween;
int leftPanel_W = gameplayScreen_X - 2 * spaceBetween;
int leftPanel_H = gameplayScreen_Height;


#pragma endregion


GameplayCtrl::GameplayCtrl()
{

}

GameplayCtrl::~GameplayCtrl()
{
}


void GameplayCtrl::Update()
{
    GameplayEventHolder();
    CountTimeLeft();
    CountRemainingLine();
    GetHighestPointedLayer();
    RenderGameplayTextLine();
    RenderAndDetectMouseClickColorLine();
    TEST_RenderGameplayOverLay();
    RenderFadingLine();
    ResizeListColorLine();
    WinLoseSystem();
    DetectButtonClick();
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

void GameplayCtrl::WinLoseSystem()
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

void GameplayCtrl::WinGame()
{
    stopCounting = true;

    WinLoseWindow winWindow(winMessage, UIManager::GetInstance()->nextLevelButton);
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

void GameplayCtrl::LoseGame()
{
    stopCounting = true;

    WinLoseWindow loseWindow(loseMessage, UIManager::GetInstance()->restartButton);
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


void GameplayCtrl::ContinueNextLevel()
{
    Button nextLevelButton = UIManager::GetInstance()->nextLevelButton;
    nextLevelButton.RenderButton(pixelFont_Small);

    if (nextLevelButton.DetectMouseClick())
    {
        
        level++;
        gameSave.Write(saveFileName);
        nextLevelButton.isEnabled = false;
        Game::GetInstance()->RestartGame();

    }
}

void GameplayCtrl::ResizeListColorLine()
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

void GameplayCtrl::CountRemainingLine()
{
    remainingLine = listColorLine.size();
}

void GameplayCtrl::CountTimeLeft()
{
    if (!stopCounting)
    {
        timeRemainingCounter -= deltaTime;
    }
}

void GameplayCtrl::GetHighestPointedLayer()
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

void GameplayCtrl::GameplayEventHolder()
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

void GameplayCtrl::RenderGameplayTextLine()
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
    remainingLineWindow.label.SetContent("Line");
    remainingLineWindow.text.SetContent(to_string(remainingLine));
    remainingLineWindow.Render();
    
    
    LabelAndTextWindow levelWindow;
    levelWindow.Transform = { timeLeftText_X, y + timeLeftText_H * 2 + topBottomSpacing, timeLeftText_W, timeLeftText_H * 2 };
    levelWindow.label.SetContent("Level");
    levelWindow.text.SetContent(to_string(level));
    levelWindow.Render();




    int roundedTimeLeftSecond = (int)(round(timeRemainingCounter));

    GameTimer timer;
    timer.Transform = { timeLeftText_X, timeLeftText_Y, timeLeftText_W, timeLeftText_H };
    timer.SetTime(roundedTimeLeftSecond);
    timer.Render();


}

void GameplayCtrl::DetectButtonClick()
{
    int buttonLeftRightSpacing = 10;
    int buttonTopBottomSpacing = 10;
    int buttonH = 40;

    //Restart Button
    Button restartButton = UIManager::GetInstance()->restartButton;
    restartButton.baseButton = { leftPanel_X + buttonLeftRightSpacing, leftPanel_Y + buttonTopBottomSpacing, leftPanel_W - 2 * buttonLeftRightSpacing, buttonH };
    restartButton.RenderButton(pixelFont_Small);
    if (restartButton.DetectMouseClick())
    {
        Game::GetInstance()->RestartGame();

    }

    //ReturnMenu Button
    Button returnMenuButton = UIManager::GetInstance()->returnMenuButton;
    returnMenuButton.baseButton = { leftPanel_X + buttonLeftRightSpacing, leftPanel_Y + 2 * buttonTopBottomSpacing + buttonH, leftPanel_W - 2 * buttonLeftRightSpacing, buttonH };
    returnMenuButton.RenderButton(pixelFont_Small);
    if (returnMenuButton.DetectMouseClick())
    {
        gameStarted = false;
    }

}

void GameplayCtrl::RenderAndDetectMouseClickColorLine()
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

void GameplayCtrl::RenderFadingLine()
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

void GameplayCtrl::TEST_RenderGameplayOverLay()
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


