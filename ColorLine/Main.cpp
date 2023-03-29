#include "GameplayCtrl.h"





#pragma region FunctionInitialize





#pragma endregion



#pragma region VariableInitialize







#pragma endregion





int main(int argc, char* argv[])
{
    initSDL(window, renderer);
    TTF_Init();
    

    

    int fontSize = 20;
    TTF_Font* pixelFont_Small = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize);
    TTF_Font* pixelFont_Med = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize * 2);


    // Set font color to black
    SDL_Color color = { 0, 0, 0 };


    // INITIALIZE COLOR LINE
    InitListColorLine(colorLineAmount);


    
    Button restartButton(14, 14, 52, 52, "", "RestartButton.png");
    Button returnMenuButton(78, 14, 52, 52, "", "HomeButton.png");

    int startButtonW = 140;
    int startButtonH = 40;
    int menuButtonSpacing = 30;
    Button startGameButton((SCREEN_WIDTH - startButtonW) / 2, (SCREEN_HEIGHT - startButtonH) / 2, startButtonW, startButtonH, "START", "");
    Button exitGameButton((SCREEN_WIDTH - startButtonW) / 2, (SCREEN_HEIGHT - startButtonH) / 2 + startButtonH + menuButtonSpacing, startButtonW, startButtonH, "EXIT", "");

    

    CustomTexture gameplayBgTexture("ColorLine Game UI.png", 0, 0, -1, -1);
    CustomTexture mainMenuTexture("menuBg.png", 0, 0, -1, -1);


    
    Mix_Music* bgMusic = Mix_LoadMUS((musicDir + "Lonesome Traveller.wav").c_str());   
    //Mix_PlayMusic(bgMusic, -1);

    //Mix_Chunk* testSFX = Mix_LoadWAV((sfxDir + "Retro Blop 18.wav").c_str());


    //Mix_Chunk* onClickButtonSFX = Mix_LoadWAV((sfxDir + "Retro Blop 18.wav").c_str());

    
    bool close = false;
    // GAME LOOP _________________________________________________________________
    while (!close)
    {
        srand(time(NULL));
        //Main Menu Controller
        #pragma region MainMenu

        while (!gameStarted)
        {

            //Menu Event Holder
            SDL_Event menuEvent;
            while (SDL_PollEvent(&menuEvent))
            {
                switch (menuEvent.type)
                {
                case SDL_QUIT:
                {
                    gameStarted = true;
                    close = true;
                    break;

                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    switch (menuEvent.button.button)
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
                    mouseX = menuEvent.motion.x;
                    mouseY = menuEvent.motion.y;

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
            startGameButton.RenderButton(pixelFont_Small);
            if (startGameButton.DetectMouseClick())
            {
                gameStarted = true;
                RestartGame();

            }
            
            // Exit game Button
            exitGameButton.RenderButton(pixelFont_Small);
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



        //Gameplay Controller
        #pragma region Gameplay



        //Gameplay Background      
        gameplayBgTexture.RenderTexture();


        // EVENT HOLDER
        SDL_Event event;
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

        Gameplay_Update(pixelFont_Med, pixelFont_Small);

        
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

        #pragma endregion




        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1000 / fps);

    }

    

    


    TTF_CloseFont(pixelFont_Small);
    TTF_CloseFont(pixelFont_Med);
    TTF_Quit();
    quitSDL(window, renderer);


    return 0;
}












