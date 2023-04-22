#include "GameplayCtrl.h"
#include "MainMenuCtrl.h"
#include "Game.h"




#pragma region FunctionInitialize





#pragma endregion



#pragma region VariableInitialize

//Game game;

#pragma endregion



int main(int argc, char* argv[])
{
    initSDL(window, renderer);
    TTF_Init();
    game.LoadComponents();
    
    // INITIALIZE COLOR LINE
    InitListColorLine(colorLineAmount);


    Mix_PlayMusic(bgMusic, -1);
    
    // GAME LOOP _________________________________________________________________
    while (!gameClose)
    {
        srand(time(NULL));
        MainMenu_Update();
        if (gameClose)
        {
            break;
        }
        cout << Mix_GetError();
        
        Gameplay_Update();

    }

    


    //TTF_CloseFont(pixelFont_Small);
    //TTF_CloseFont(pixelFont_Med);
    TTF_Quit();
    quitSDL(window, renderer);


    return 0;
}










