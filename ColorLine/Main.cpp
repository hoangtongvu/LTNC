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
    Game::GetInstance()->Init();
    Game::GetInstance()->LoadComponents();
    //GameLogo logo;
    
    // INITIALIZE COLOR LINE
    Game::GetInstance()->InitListColorLine(colorLineAmount);

    //Play Bg music
    //Mix_PlayMusic(bgMusic, -1);

    // GAME LOOP _________________________________________________________________
    Game::GetInstance()->Update();

    
    TTF_Quit();
    quitSDL(window, renderer);


    return 0;
}










