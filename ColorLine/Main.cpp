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
    game.Init();
    game.LoadComponents();
    
    // INITIALIZE COLOR LINE
    game.InitListColorLine(colorLineAmount);

    //Play Bg music
    //Mix_PlayMusic(bgMusic, -1);
    
    // GAME LOOP _________________________________________________________________
    game.Update();

    
    TTF_Quit();
    quitSDL(window, renderer);


    return 0;
}










