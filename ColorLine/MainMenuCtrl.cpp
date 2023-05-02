#include "MainMenuCtrl.h"



MainMenuCtrl* MainMenuCtrl::instance = NULL;



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
        RenderLogo();
        SetBgBlack();
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
    CustomTexture mainMenuTexture = UIManager::GetInstance()->mainMenuTexture;
    mainMenuTexture.RenderTexture();
}

void MainMenuCtrl::DetectButtonClick()
{
    // Start game Button
    Button startGameButton = UIManager::GetInstance()->menuButtons.newGameButton;
    if (startGameButton.DetectMouseClick())
    {
        level = 0;
        gameStarted = true;
        Game::GetInstance()->RestartGame();

    }


    // Continue game Button
    Button continueGameButton = UIManager::GetInstance()->menuButtons.continueGameButton;
    if (continueGameButton.DetectMouseClick())
    {
        gameStarted = true;
        Game::GetInstance()->RestartGame();
    }
    
    // Exit game Button
    Button exitGameButton = UIManager::GetInstance()->menuButtons.exitGameButton;
    if (exitGameButton.DetectMouseClick())
    {
        gameStarted = true;
        gameClose = true;
    }

}

void MainMenuCtrl::RenderButtons()
{
    MenuButtons menuButtons = UIManager::GetInstance()->menuButtons;
    
    menuButtons.Render();
}

void MainMenuCtrl::SetButtonPosition()
{
    UIManager::GetInstance()->menuButtons.SetPosition();
}

void MainMenuCtrl::RenderLogo()
{
    UIManager::GetInstance()->logo.Render();

    //logo.Render();
}

