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
    
    //TEST SAVE GAME
    //GameSave save;
    gameSave.Load(saveFileName);

    

    //ofstream o_saveFile("Player data/save.txt");
   /* if (o_saveFile)
    {
        o_saveFile << 30;
    }*/

    //o_saveFile.close();


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










