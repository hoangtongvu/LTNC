#include "GameplayCtrl.h"
#include "Game.h"



#pragma region FunctionInitialize





#pragma endregion



#pragma region VariableInitialize

Game game;

#pragma endregion



int main(int argc, char* argv[])
{
    initSDL(window, renderer);
    TTF_Init();
    
    game.LoadComponents();
    

    // INITIALIZE COLOR LINE
    InitListColorLine(colorLineAmount);


    Button restartButton(14, 14, 52, 52, "", "RestartButton.png");
    Button returnMenuButton(78, 14, 52, 52, "", "HomeButton.png");

    int startButtonW = 200;
    int startButtonH = 60;
    int menuButtonSpacing = 50;
    Button startGameButton((SCREEN_WIDTH - startButtonW) / 2, (SCREEN_HEIGHT - startButtonH) / 2, startButtonW, startButtonH, "START", "");
    Button exitGameButton((SCREEN_WIDTH - startButtonW) / 2, (SCREEN_HEIGHT - startButtonH) / 2 + startButtonH + menuButtonSpacing, startButtonW, startButtonH, "EXIT", "");

    

    CustomTexture mainMenuTexture("menuBg.png", 0, 0);
    mainMenuTexture.LoadTexture(-1, -1);

    Mix_PlayMusic(bgMusic, -1);
    
    bool close = false;
    // GAME LOOP _________________________________________________________________
    while (!close)
    {
        srand(time(NULL));



        //Main Menu Controller__________________________________________________________________________________________________
        #pragma region MainMenu

        while (!gameStarted)
        {

            //Menu Event Holder
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                {
                    gameStarted = true;
                    close = true;
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


            mainMenuTexture.RenderTexture();


            // Start game Button
            startGameButton.RenderButton(pixelFont_Med);
            if (startGameButton.DetectMouseClick())
            {
                gameStarted = true;
                RestartGame();

            }
            
            // Exit game Button
            exitGameButton.RenderButton(pixelFont_Med);
            if (exitGameButton.DetectMouseClick())
            {
                gameStarted = true;
                close = true;
            }




            isClicked = false;

            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            SDL_Delay(1000 / fps);
        }
        if (close)
        {
            break;
        }


        #pragma endregion



        //Gameplay Controller___________________________________________________________________________________________________
        #pragma region Gameplay


        // EVENT HOLDER
        while (SDL_PollEvent(&event))
        {
            switch (event.type) 
            {
            case SDL_QUIT:
            {
                close = true;
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

        Gameplay_Update();

        
        //Restart Button
        restartButton.RenderButton(pixelFont_Small);
        if (restartButton.DetectMouseClick())
        {
            RestartGame();
            
        }
        
        //ReturnMenu Button
        returnMenuButton.RenderButton(pixelFont_Small);
        if (returnMenuButton.DetectMouseClick())
        {
            gameStarted = false;
        }


        //Reset mouseClick
        isClicked = false;

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1000 / fps);

        #pragma endregion





    }

    

    


    //TTF_CloseFont(pixelFont_Small);
    //TTF_CloseFont(pixelFont_Med);
    TTF_Quit();
    quitSDL(window, renderer);


    return 0;
}










