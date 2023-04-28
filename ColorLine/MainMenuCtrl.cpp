#include "MainMenuCtrl.h"


MainMenuCtrl mainMenuCtrl;

MainMenuCtrl::MainMenuCtrl()
{
    
}

MainMenuCtrl::~MainMenuCtrl()
{
}



void MainMenuCtrl::Update()
{
    while (!gameStarted)
    {
        
        EventHolder();
        //RenderMainMenuTexture();
        SetButtonPosition();
        RenderButtons();
        DetectButtonClick();
        ResetMouseClick();
        SetBgBlack();
        RenderLogo();
        SDL_Render();
          
    }
}


void MainMenuCtrl::EventHolder()
{
    //Menu Event Holder
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        {
            gameStarted = true;
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

                break;
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

void MainMenuCtrl::RenderMainMenuTexture()
{
    CustomTexture mainMenuTexture = uiManager.mainMenuTexture;
    mainMenuTexture.RenderTexture();
}

void MainMenuCtrl::DetectButtonClick()
{
    // Start game Button
    Button startGameButton = uiManager.menuButtons.newGameButton;
    if (startGameButton.DetectMouseClick())
    {
        level = 0;
        gameStarted = true;
        game.RestartGame();

    }


    // Continue game Button
    Button continueGameButton = uiManager.menuButtons.continueGameButton;
    if (continueGameButton.DetectMouseClick())
    {
        gameStarted = true;
        game.RestartGame();
    }
    
    // Exit game Button
    Button exitGameButton = uiManager.menuButtons.exitGameButton;
    if (exitGameButton.DetectMouseClick())
    {
        gameStarted = true;
        gameClose = true;
    }

}

void MainMenuCtrl::RenderButtons()
{
    MenuButtons menuButtons = uiManager.menuButtons;
    menuButtons.Render();
}

void MainMenuCtrl::SetButtonPosition()
{
    uiManager.menuButtons.SetPosition();
}

void MainMenuCtrl::RenderLogo()
{
    CharC_Logo logo;
    logo.SetTransform();
    logo.Render();
}

