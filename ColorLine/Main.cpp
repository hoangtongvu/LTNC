#include "GameplayCtrl.h"
#include "MainMenuCtrl.h"
#include "Game.h"
#include "GameSave.h"


#pragma region FunctionInitialize


#pragma endregion


#pragma region VariableInitialize


#pragma endregion



int main(int argc, char* argv[])
{
    initSDL(window, renderer);
    TTF_Init();
    game.LoadComponents();
    
    // INITIALIZE COLOR LINE
    InitListColorLine(colorLineAmount);

    //Play Bg music
    //Mix_PlayMusic(bgMusic, -1);
    



    // GAME LOOP _________________________________________________________________
    while (!gameClose)
    {
        srand(time(NULL));
        mainMenuCtrl.Update();
        if (gameClose)
        {
            break;
        }
        
        gameplayCtrl.Update();

    }


    
    TTF_Quit();
    quitSDL(window, renderer);


    return 0;
}










