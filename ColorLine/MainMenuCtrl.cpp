#include "MainMenuCtrl.h"

void MainMenu_Update()
{
    while (!gameStarted)
    {
        
        MainMenuEventHolder();
        //RenderMainMenuTexture();
        MainMenuDetectButtonClick();
        ResetMouseClick();
        SetBgBlack();
        SDL_Render();
          
    }
}


void MainMenuEventHolder()
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

void RenderMainMenuTexture()
{
    CustomTexture mainMenuTexture = uiManager.mainMenuTexture;
    mainMenuTexture.RenderTexture();
}

void MainMenuDetectButtonClick()
{
    // Start game Button
    Button startGameButton = uiManager.startGameButton;
    string s;
    if (level == 0)
    {
        s = "NEW GAME";
    }
    else
    {
        s = "CONTINUE";
    }
    startGameButton.buttonLabel = s;
    startGameButton.RenderButton(pixelFont_Med);
    if (startGameButton.DetectMouseClick())
    {
        gameStarted = true;
        RestartGame();

    }
    
    // Exit game Button
    Button exitGameButton = uiManager.exitGameButton;
    exitGameButton.RenderButton(pixelFont_Med);
    if (exitGameButton.DetectMouseClick())
    {
        gameStarted = true;
        gameClose = true;
    }

}
